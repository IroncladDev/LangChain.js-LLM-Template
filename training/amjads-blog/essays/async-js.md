{
  "title": "Easier Concurrent Programming in JavaScript with Async Functions",
  "date": "10/31/2015"
}
---

We're about to introduce async functions internally at Facebook so
I'm taking the time to  reflect on how this could be a great win for building
reliable software.

When I joined the company, I worked on a team tasked with improving
photo upload reliability on the site. We were failing 1 out of 10
people that tried to upload a photo album. Which translates to
millions of people having terrible experiences on daily basis. One of the first
things that we struggled with was understanding the ordering of
operations. The system was made up of multiple components (Flash for
image re-sizing, UIs, Controllers, Servers) that had to asynchronously
communicate via JS and was all done in callbacks. This made debugging
really hard. Sometimes callbacks will get lost and never get called,
at times they will be called multiple times, sometimes errors will
occur after the callback is called and never gets reported. Not to
mention all the horrible race conditions that we saw. And this is not something
that is limited to Facebook, or that can only happen at our scale. I
was in similar situations at small startups too. This can happen in
any sizable (potentially distributed) system written in JavaScript
using callbacks.

When I first started learning JavaScript, one of things people praised
it for was: "easy concurrent programming". The argument goes "it's a
single-threaded process with a strict run-to-completion programming
model and that means you can't have race conditions". Turns out that
can't be further from the truth. The definition of race conditions is
not tied to multithreading. It is simply when you have a system that
is dependent on the sequence of events from multiple components and
then the components behave in an unintended way. Which brings me to the
point of this post. I want to show that using async functions (or
generally co-routines) you can write programs that makes the expected
ordering of events explicit and makes it easier to recover from
failures in subcomponents.

I will illustrate this by going through an example of building a
vending machine. Everything in the vending machine costs 1 cent, but
the machine can take in any coin that is worth any arbitrary number of
cents. A sample run of this machine:

 * Insert a quarter
 * Select an item
 * Dispense the item
 * Return 24 cents change

Here is my initial implementation:

* A `VendingMachine` class with two public methods
* `coin(value)` inputs a coin with a given value in cents to the machine
* `select(item)` inputs an item selection to the machine
* Two subcomponents `itemDispenser` and `change` resoponsible for
dispensing the items and returning the change respectively

```javascript
class VendingMachine {
  coin(value) {
    this.cents = value;
  }

  select(item) {
    this.itemDispenser.dispense(item, () => {
      this.change.return(this.cents - 1);
    });
  }
}
```

Simple enough. But of course it's missing a few things. First of
all there is no error handling:

* What if the `itemDispenser` failed? We should of course return all the money.
* What if the `change` component failed? We should get into broken
state so we don't accept any more coins until someone fixes the
machine.

Let's add error handling and a broken state.

```javascript
class VendingMachine {
  coin(value) {
    if (this.broken){
      console.error('Out of order');
      return;
    }

    this.cents = value;
  }

  select(item) {
    let change = this.cents - 1;
    this.itemDispenser.dispense(item, e => {
      if (e) {
        console.error(e.message);
        // Failed to dispense item, return all the money.
        change = this.cents;
      }

      this.change.return(change, e => {
        if (e) {
          this.broken = true;
        }
      })
    });
  }
}
```

Now that we can handle errors from the machine components. What if the
outside world behaved in an unintended way? In other words, what
if someone selected an item without paying? What if someone inserted
two coins without selecting an item? Ideally we'd have input queuing,
but let's keep it simple for now.

```javascript
class VendingMachine {
  coin(value) {
    if (this.broken){
      console.error('Out of order');
      return;
    }

    if (this.cents) {
      console.error('Processing existing order');
      return;
    }

    this.cents = value;
  }

  select(item) {
    if (!this.cents) {
      console.error('Please insert a coin');
      return;
    }

    let change = this.cents - 1;
    this.itemDispenser.dispense(item, e => {
      if (e) {
        console.error(e.message);
        // Failed to dispense item, return all the money.
        change = this.cents;
      }

      this.change.return(change, e => {
        if (e) {
          this.broken = true;
        }
        this.cents = 0;
      })
    });
  }
}
```

Can you spot the potential race condition?
What if you inserted a coin, selected an item, then before the machine
gets a chance to dispense the item and return the change you selected
another item? We should make sure `this.cents` is updated right after
the selection.

```javascript
class VendingMachine {
  coin(value) {
    if (this.broken){
      console.error('Out of order');
      return;
    }

    if (this.cents) {
      console.error('Processing existing order');
      return;
    }

    this.cents = value;
  }

  select(item) {
    if (!this.cents) {
      console.error('Please insert a coin');
      return;
    }

    let change = this.cents - 1;
    // Immediately update to avoid race conditions
    this.cents = 0;

    this.itemDispenser.dispense(item, e => {
      if (e) {
        console.error(e.message);
        // Failed to dispense item, return all the money.
        change += 1;
      }

      this.change.return(change, e => {
        if (e) {
          this.broken = true;
        }
        this.cents = 0;
      })
    });
  }
}
```

But wait, are we really done? What if you inserted a coin, selected an
item, and then immediatly inserted another coin? That coin is then
lost in limbo. We should gaurd the entire the process with another
state variable. But the problem is that every time we add a state
variable it makes the program harder to understand and
test, and presents more race hazards. Who would've thought a program
with two input events can be so complex to build reliabily. I'll spare
you anymore inspection and iteration and directly jump to what
any sensible programmer would do when presented with this
challenge: build a state machine.

```javascript
class VendingMachine {
  constructor() {
    this.state = IDLE;
    this.queue = [];
  }

  coin(coin) {
    if (this.state === BROKEN) {
      return console.error('Machine broken');
    }

    this.queue.push(coin);
    this.dispatch();
  }

  dispatch() {
    if (this.state !== IDLE) {
      return;
    }

    this.cents = this.queue.shift();
    this.state = WAIT_FOR_SELECT;
  }

  break(err) {
   console.error(err.message);
   this.state = BROKEN;
  }

  select(item) {
    if (this.state === IDLE) {
      return console.error('Please insert coin');
    }

    if (this.sate !== WAIT_FOR_SELECT) {
      return console.error('Processing existing order');
    }

    let change = this.cents - 1;
    this.itemDespenser.despense(item, err => {
      if (err) {
        console.error('Error dispensing item');
        change += 1;
        return;
      }

      this.change.return(change, err => {
        if (err) {
          this.break(err);
          return;
        }
        this.state = IDLE;
        this.dispatch();
      });
    });
  }
}
```

I think I got it right. But who knows, you wouldn't know by reading
the program, you'd need to write a lot of unit tests to convince
yourself that it works. And then write some pseudocode in comments to
explain what you intended to do here for future programmers. But even
then there is room for failure. One of the subcomponents can call our
callback multiple times causing all kind of failures to happen.

Now that we've explored how hard building something -- that is
conceptually easy -- using callbacks can be. Let's try with a
better concurrency primitive, namely async functions.

_If you're not familiar with async functions, [read this intro
first](https://jakearchibald.com/2014/es7-async-functions/)._

Here's how we'll structure our code for the `async` version:

* We'll be using a data-structure called `PromiseQueue` (it's really
simple and can be implemented in ~20 lines of code)
* A `PromiseQueue` has two methods `put` and `get`. `get` would return
a promise that can only be resolved once we put something into the queue
* We'll be using two promise queues, one for the coins and one for the
items
* We'll have a main run loop that will run indefinitely or until the
machine breaks

```javascript
class VendingMachine {
  constructor() {
    this.coins = new PromiseQueue();
    this.items = new PromiseQueue();
    this.brokenErr = e;
    this.run().catch(e => this.brokenErr = e);
  }

  coin(coin) {
    if (this.brokenErr) {
      return console.error('Machine broken', this.brokenErr);
    }
    this.coins.put(coin);
  }

  select(item) {
    if (this.brokenErr) {
      return console.error('Machine broken', this.brokenErr);
    }
    this.items.put(item);
  }

  async run(item) {
    while (1) {
      let cents = await this.coins.get();
      let item = await this.items.get();
      let change = cents - 1;

      try {
        await this.itemDispenser.dispense(item);
      } catch (e) {
        console.error('Error dispensing item');
        change = cents;
      }

      try {
        await this.change.return(change);
      } catch (e) {
        console.error('Error returning change');
        throw e;
      }
    }
  }
}
```

Look how beautiful this is. Everything you need to know about the program you'll know by
reading the `run` function. A single function that reads exactly like
how we described the machine should work. We are even using elementary
control flow, like try/catch, and while loops! What's more, the entire state
of the machine are basically local variables. That leaves less room
for races to happen. Which brings me to the conclusion:

> [Co-routines are to state machines what recursion is to stacks](http://eli.thegreenplace.net/2009/08/29/co-routines-as-an-alternative-to-state-machines/)

Co-routines are the generalized form of async functions. Where async
functions can only pause execution while waiting on a promise,
co-routines allow
multiple entry points for functions to suspend and resume
execution. [ES6
generator
functions](http://tobyho.com/2013/06/16/what-are-generators/) are an
example of a generalized co-routines. So, similar to how recursion
can help process nested data-structures without using explicit stacks,
co-routines helps solve problems involving state without using explicit state machines.
