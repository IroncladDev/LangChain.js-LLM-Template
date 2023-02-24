{
  "title": "Building an In-Browser JavaScript VM and Debugger Using Generators",
  "date": "01/06/2014"
}
---

### tl;dr

I built a JavaScript VM and debugger in JavaScript. Checkout the example in the [demo app](http://debugjs.com/#example) and the [source code](https://github.com/amasad/debugjs). Read on for a dive into the technical details.

Update: [I implemented one of the examples from Bret Victor's Learnable Programming](/2014/01/10/implementing-bret-victors-learnable-programming-has-never-been-easier/) using debug.js.

### Introduction

#### Motivation

For the past few years I've been working on creating tools to help people learn programming on the web. I've worked on [repl.it](http://repl.it) and open sourced the underlying technology which powered a [few](https://www.udacity.com/) [learn](http://www.codecademy.com/) to [code](http://www.learnstreet.com/) websites and until recently lead product engineering at Codecademy. Through all that, one thing I really wanted to see are the tools to make it possible to visualize code execution and step through code in the browser. To catch glimpse of what an ideal interactive learning environment would be you should check out [Learnable Programming](http://worrydream.com/LearnableProgramming/) by Bret Victor.

In addition to the educational benefits of such a tool, if matured it could be also useful for code instrumentation, web IDEs, and creating a foundation for writing other VMs on top of JavaScript (having the pausable machine state let’s you not worry about the non-blocking environment).

Ever since I've read about the [ES6 Generators](http://wiki.ecmascript.org/doku.php?id=harmony:generators) proposal, I've been toying with this idea in my head but it wasn't a real possibility until [Ben Newman’s](https://twitter.com/benjamn) [Regenerator](http://facebook.github.io/regenerator/) brought generators to the browser.

#### Goals

* JS VM capable of running ES5 code
* VM should be pausable on any instruction
* Ability to create a feature complete JS debugger on top of the VM
* Mainly targeting browsers but should work in Node.js for development

### Generators

_if you're familiar with generators, feel free to skip this section or read [this](http://tobyho.com/2013/06/16/what-are-generators/) instead for a more comprehensive introduction_

Generators are part of the ES6 proposals and is making it's way slowly into production environments. Generators gives us a new type of functions where we can step in and out of a function while sending  and receiving values to and from it.

The following example should illustrate the fundamentals of generators:

```javascript
function* genFn() {
  var x = yield 2;
  yield x;
  return 'done';
}

var gen = genFn()
console.log(gen.next());  // {value: 2, done: false}
console.log(gen.next(1)); // {value: 1, done: false}
console.log(gen.next());  // {value: "done", done: true}
```

_Notice the * at the end of the `function` keyword, that's all you need to create a generator._

### Overview

Having the unique ability of suspending execution of a function and resuming at a later point in time, generators gives us the basic building block for creating a VM that can step through instructions and pause at any point. To achieve that, every function in the system must be transformed into a generator that yields to the machine before every instruction execution. This may sound similar to [Continuation Passing Style](http://en.wikipedia.org/wiki/Continuation-passing_style) with a trampoline, however, the main difference is that the call stack information in CPS is held in the lexical scope whereas in this method we need to take full control of the call stack. I'm not a compiler nor a PLT expert so I'm not really sure if this method has a name or if it has been tried before, if you do please let me know.

We want the host JavaScript environment to take on as much of the responsibility of running code as possible. Beyond generator function transformation we have to do a few other things which I'll outline here and get into each later.

* Control the call stack
* Handle errors and error propagation
* Control timers in the system (setTimeout, setInterval etc)
* Workaround native APIs that expect function arguments (callbacks and not generators)
* Write a debugger module

### Code Transformation

In order to control the execution flow we need to yield back to the machine after each instruction execution. To do so, we take each instruction in our program and insert a `yield` expression before it. I chose to define an instruction (or a step) as a single JavaScript statement.

For example:

```javascript
var foo = 1;
if (bar === foo) {
  foo = 2;
}
```

 After the transformation:

```javascript
function* __top() {
  yield {step};
  var foo = 1;
  yield {step};
  if (bar === foo) {
    yield {step};
    foo = 2;
  }
}
```

In addition to the basic instruction transformation we need to add information about each function in our program that would be useful when building the debugger. We call this, a stack frame and it includes the following data about our function:

* name
* filename
* scope: an array of variable names and their occurrences in the function.
* eval function: this gives access to the function's closure to do things like watch expressions and eval code in that scope.

Finally, function calls are a bit trickier than regular instructions since we need to capture the call stack and play nicely with native and library function calls. On compile time, at the function call site, we don't know whether a function call is referencing a generator function (a function within our ecosystem) or a function object. If it was the former, we need to add it to our call stack and step into executing the function instructions, as for the latter we simply need to get a value out of it. We solve the issue by wrapping all function calls in a thunk and yield it back to the machine to make that decisions on runtime (where we have more information).

“Thunk” is a fancy word for something JavaScript programmers do all the time -- create a closure that delays the computation of a piece of code. To illustrate:

```javascript
foo();
```

Becomes:

```javascript
yield __thunk(function *thunk() {
  return foo();
}, this, arguments);
```

A more complex call expression would also work:

```javascript
for (var i = foo(), b = bar(); i < 50; i++);
```

Becomes:

```javascript
for (var i = yield __thunk(function* thunk() {
  return foo();
}, this, arguments), b = yield __thunk(function* thunk() {
  return bar();
}, this, arguments); i < 50; i++);
```

`this` and `arguments` are passed down so we can create the correct scope when invoking the thunk.

### VM

#### Stepping and The Call Stack

Our machine's main responsibility is to invoke, push, and pop functions off the call stack. It starts out with a halted (or idle state) until we eval a string of code which is transformed and converted into a top-level generator. Then, we can call `step` on the machine and expect it to run the next instruction in our code via the generator `next()` method. If that instruction returns a thunk, we evaluate it and if it returns a generator we push it onto our call stack and any further steps will be invoked on it. When our current peek generator is done stepping we take the last value and pass it back into the next generator on our call stack. The passing is also done via the generator `.next` function which accepts an argument to be sent into the generator function.

### Errors

When invoking an instruction, there is a possibility it could throw an error. The way we deal with that is we try/catch every instruction invocation and if we get an error we pass it up the call stack incase one of the caller functions have try/catch statement waiting for us.

```javascript
Runner.prototype.$propError = function (e) {
  while (this.stack.length) {
    this.gen = this.stack.pop();
    try {
      this.gen.throw(e);
      return;
    } catch (e2) {
      e = e2;
    }
  }
  throw e;
};
```

#### Timers

One of our goals is to be able to pause our machine at an point in time and for as much time as needed. Because of that we run into the problem of not being able to rely on the host JavaScript environment for controlling timers. e.g. we have a `setInterval` running with a second in between and we decided to pause the machine for 10 seconds, when we resume we shouldn't expect 10 back-to-back timers to trigger. The machine time should only be running when:

1. We are executing instruction code.
2. We are in idle state (the call stack has unwinded and the machine is in a halted state).

We use a priority queue to store our timers and have a tick method that checks if there are any timers that should fire at that point in time. We rely on the host `setImmediate` or `setTimeout(tick, 0)` to provide us with our tick function.

When a timer fires the machine simply triggers `timer` event and clients could react by running or stepping through the timer (thus creating a new call stack). This is very similar to JavaScript event loops but very specific to timers.

#### Native APIs

We can't expect every API our code touches to understand how we do things using generators so the machine provides a way to wrap callbacks and yield them back to the machine to further step through them. However, a problem arises when we consider synchronous APIs that expect callbacks, for example `Array.forEach` will call the callback continuously until the iteration finishes and that's a problem because we expect to be able to pause any execution indefinitely. For that reason, we can't rely on the host environment native APIs to do the same thing. Luckily, this turns out not to be very hard to solve. All it took is taking the popular [es5-shim](https://github.com/es-shims/es5-shim) library and running our transformation on it so it become generator friendly.

#### Events

Much like the the Native API problem, events expects event listeners made of functions, but this is a much simpler problem because this is an asynchronous API and all we have to do is wrap our listeners with a function wrapper that would trigger our machine whenever it's called.

#### Debugger

After creating the VM, writing the debugger was fun and relatively straightforward. The only issue I ran into is handling all the thunk garbage we have in our call stack because we treated them just like any function call to make the machine simpler.

Features:

* Breakpoints
* Debugger statements
* Step in, out, and over any statement
* Get scope variables and values
* Get call stack
* Eval in scope: whenever you on a breakpoint you can evaluate in that scope

Check it out [here](http://debugjs.com).
#### Current status

The project is still in early development stages. I’ve only been working on it for about two weeks. In terms of correctness, I’m sure the VM can run most of the ES5 spec. One thing that came to mind while writing this post is that getters and setters are definitely broken at the moment.

The VM is currently very slow, especially the code transformation bit but there are a few quick wins to be had there to get it to an OK speed.

I also realize that the generator transformation is just an intermediate step to the transformation that Regenerator does to be able to step in and out of functions freely. Therefore we could get rid of that step and transform directly to the state machine.
