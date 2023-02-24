{
  "title": "On VMs in JavaScript",
  "date": "07/17/2012",
  "author": "Amjad Masad"
}
---

There are many challenges in implementing a language VM in JavaScript. Amongst those is the fact that your VM will be forced to live in a non-blocking environment, whereas most language interpreters are designed to be able to block in some cases. This forces JavaScript programs to be structured differently. Programs run shortly registering callbacks for events and yielding to the event loop that will dispatch the callback when the event is fired. While many enjoy this style of programming, there are others that think there is a better way:

* [TameJS](http://tamejs.org/)
* [Narrative JavaScript](http://www.neilmix.com/narrativejs/doc/index.html)
* [jwacs](http://chumsley.org/jwacs/)
and the list goes on...

### In the VM

You maybe asking yourself what kind of asynchronous operations would an interpreter need to do in the first place. Good question! It's always good practice to put computationally heavy programs in Web Workers and that include VMs which makes interactions with the UI thread asynchronous, which for the most part, is ok, except to when it comes to user input. Most would expect it to be blocking. Also having the ability to pause and resume execution at any point in time would open the opportunity to create debugging tools like a stepping debugger.

One thing you can and many already do is **design your VM with a yield state**. But that doesn't really apply when implementing an X-to-JavaScript compiler or when compiling interpreters from other languages to JavaScript or when writing simple interpreters without really implementing a full blown VM.

### Case study: BF Interpreter

For the following section I will use a [brainfuck](http://en.wikipedia.org/wiki/Brainfuck) interpreter to illustrate the problem and part of the solution.

#### BF Interpreter
The function `bf` takes a string made of characters representing a BF program and runs it. You do not need to know what all the operations in the BF interpreter are but note that the input command `,` asks for user input.

    // Adapted from http://code.google.com/p/jslibs/wiki/JavascriptTips
    function bf (code) {
      var codeLength = code.length

        // Code pointer
        , cp = 0

        // Data pointer
        , dp = 0

        // Tape.
        , m = []

    // Loop start and end positions.
        , loopIn = {}
        , loopOut = {}

    // Match [].
        , stack = [];

      // Register loop jumps
      for (var cp = 0; cp < codeLength; cp++) {
        if (code[cp] == '[')
          stack(cp);
        else if (code[cp] == ']')
          loopOut[loopIn[cp] = stack()] = cp;
      }

    // Execute.
      for (var cp = 0; cp < codeLength; cp++) {
        switch(code[cp]) {
          case '>':
            dp++;
            break;
          case '<':
            dp--;
            break;
          case '+':
            m[dp] = ((m[dp]||0)+1)&255;
            break;
          case '-':
            m[dp] = ((m[dp]||0)-1)&255;
            break;
          case '.':
            console.log(String.fromCharCode(m[dp]));
            break;
          case ',':
            m[dp] = prompt('input').charCodeAt(0)||0;
            break;
          case '[':
            m[dp]||(cp=loopOut[cp]);
            break;
          case ']':
            cp = loopIn[cp]-1;
            break;
        }
      }
    }

Now the above is a **synchronous** BF interpreter written in JavaScript and it uses `prompt` for input (`,`) which is the browser's native blocking stdin. Loading it in the main browser UI thread would work, however, running large BF programs would cause it to block and hang your tab or browser. Loading it in a Web Worker would not work either because Workers do **not** have access to the `window` obect.

#### CPS'ed BF interpreter

We can try fixing the interpreter by making the input operation a non-blocking call that takes a callback to continue the program after input was recieved from the user from the UI thread, via the Web Worker message API. let us assume this has been already implemented for us and we can use: `console.input`.

You would quickly notice that having an asynchrounous operation is infectious and it would force us to restructure our program into a [CPS](http://en.wikipedia.org/wiki/Continuation-passing_style) style.

_Note that This could be further simplified but it's left to demonstrate the point._

    function bf (code) {
      var codeLength = code.length
        , i = 0, cp = 0, dp = 0
        , loopIn = {}, loopOut = {}, m = {}
        , stack = [];

      for (var cp = 0; cp < codeLength ; cp++) {
        if (code[cp] == '[')
          stack.push(cp);
        else if (code[cp] == ']')
          loopOut[loopIn[cp] = stack.pop()] = cp;
      }

      var ops = {
        '>': function (cont) {
          dp++;
          cont();
        }
      , '<': function (cont) {
          dp--;
          cont();
        }
      , '+': function (cont) {
          m[dp] = ((m[dp]||0)+1)&255;
          cont();
        }
      , '-': function (cont) {
          m[dp] = ((m[dp]||0)-1)&255;
          cont();
        }
      , '.': function (cont) {
          console.log(String.fromCharCode(m[dp]));
          cont();
        }
      , ',': function (cont) {
          console.input(function (data) {
            m[dp] = data.charCodeAt(0) || 0;
            cont();
          });
        }
      , '[': function (cont) {
          m[dp]||(cp=loopOut[cp]);
          cont();
        }
      , ']': function (cont) {
          cp = loopIn[cp]-1;
          cont();
        }
      };

      function noop () {}

      function runNext () {
        cp++;
        if (cp < codeLength) {
          (ops[code[cp]] || noop)(runNext);
        }
      }
      cp = -1;
      runNext();
    }

Notice how every function in the system receives a callback function which is responsible for continuing the program. The callback maybe called with values that would've rather been return values. In our case, there exist no need for return values because state is encapsulated within the `bf` function closure.

By doing so **We eliminated the need for a JavaScript runtime call stack**, as each function would be responsible for continuing the execution of the program. Which means each function has the power and ability to stop the execution (maybe wait for an event to happen) and continue at a later time. Which I think is freeing.

#### Blow it up

Even-though we don't need an actual call stack anymore because every function call in our program is the last statement in it's caller function that would be responsible for continuing it's program after it finishes executing. However we are still bound to the runtime's call stack, that would be exhausted as soon as we try to run a non-trivial BF program.

Luckily in functional programming there is a technique called trampolining that would help minimize the call stack size needed to run programs written in CPS. It works by having a loop that is responsible for calling the program's functions that would in turn return a continuation function to be executed by the same loop.

    function bf (code) {
      var codeLength = code.length
        , i = 0, cp = 0, dp = 0
        , loopIn = {}, loopOut = {}, m = {}
        , stack = [];

      for (cp = 0; cp < codeLength ; cp++)
        if (code[cp] == '[') stack.push(cp);
        else if (code[cp] == ']') loopOut[loopIn[cp] = stack.pop()] = cp;

      var ops = {
        '>': function () {
          dp++;
          return runNext;
        }
      , '<': function () {
          dp--;
          return runNext;
        }
      , '+': function () {
          m[dp] = ((m[dp]||0)+1)&255;
          return runNext;
        }
      , '-': function () {
          m[dp] = ((m[dp]||0)-1)&255;
          return runNext;
        }
      , '.': function () {
          console.log(String.fromCharCode(m[dp]));
          return runNext;
        }
      , ',': function () {
          return function () {
            console.input(function (data) {
              m[dp] = data.charCodeAt(0) || 0;
              run(runNext);
            });
          };
        }
      , '[': function () {
          m[dp]||(cp=loopOut[cp]);
          return runNext;
        }
      , ']': function () {
          cp = loopIn[cp]-1;
          return runNext;
        }
      };

      function noop () {}

      function runNext () {
        cp++;
        if (cp < codeLength)
          return (ops[code[cp]] || noop)();
      }

      function run (cont) {
        // Trampoline.
        while (typeof cont === 'function') {
          cont = cont();
        }
      }

      cp = -1;
      run(runNext);
    }


#### A glimpse into the future

Things should not be this hard. JavaScript must grow as a language to allow constructs that makes it easier to write asynchronous programs. In addition to the web finally realizing the dream of being the application platform, JavaScript also plays a strong role in evented-io server programming which had proven to be quite efficient.

Let us take a look at using [generators](http://wiki.ecmascript.org/doku.php?id=harmony:generators) to emulate coroutines that will land in the next version of JavaScript, ES Harmony. The following example is written using the excellent [task.js](http://taskjs.org/) library:

    function bf (code) {

      // Create a task that could yield.
      task.spawn(function () {
        var codeLength = code.length
          , i = 0, cp = 0, dp = 0
          , loopIn = {}, loopOut = {}, m = {}
          , stack = [];

        for ( var cp = 0; cp < codeLength ; cp++ )
          if ( code[cp] == '[' )
            stack.push(cp);
          else if ( code[cp] == ']' )
            loopOut[loopIn[cp] = stack.pop()] = cp;

        for (var cp = 0; cp < codeLength && i < 100000; cp++, i++) {
          switch(code[cp]) {
            case '>':
              dp++;
              break;
            case '<':
              dp--;
              break;
            case '+':
              m[dp] = ((m[dp]||0)+1)&255;
              break;
            case '-':
              m[dp] = ((m[dp]||0)-1)&255;
              break;
            case '.':
              console.log(String.fromCharCode(m[dp]));
              break;

            // Yield to the event loop until we get the user input.
            case ',':
              m[dp] = yield console.input();
              break;
            case '[':
              m[dp]||(cp=loopOut[cp]);
              break;
            case ']':
              cp = loopIn[cp]-1;
              break;
          }
        }
     });
    }

What's more, ES Harmony will also include tail call optimization.

### A Shameless Hack

To get input on the emscripten compiled languages on our [repl.it](http://repl.it) project we considered using a CPS code transformer like the above-mentioned list but the approach failed for the following reasons:

1. Compiling language interpreters to JS using [emscripten](https://github.com/kripken/emscripten/wiki) generates [lots of JavaScript](https://raw.github.com/replit/empythoned/master/dist/python.opt.js) which when ran against these compilers takes forever.
2. JavaScript is not [tail call optimized](http://en.wikipedia.org/wiki/Tail_call); and this is bad because compiling to CPS means functions would be used for control flow, a whole lot of them. However I think some transformers do use clever tricks to minimize call stack.
3. Performance hit which is for the most part from the cost of creating and invoking a lot of functions.
4. Adding an additional compile step makes it even harder to debug.

So we took the easy way out and hacked the hell out of it. After thinking for a while about the problem of what in essence is resource sharing across threads which is prohibited in browsers for the added complexity and the security concerns of the web. I had a crazy idea of using the Web SQL Database to share data between the Worker and the UI thread since it has a synchronous worker API. While I'm sure this hack doesn't make threads share memory but is fast enough for stdin. The busy loop count (100000000 in the code below) is tuned and maybe tuned further to get faster results.

When the language interpreter in a Web Worker hits an input operation it will stop execution, ask the main thread for input via a message, and busy loop while polling for changes in a Web Database table:

    var DB = self.openDatabaseSync('replit_input', '1.0', 'Emscripted input', 1024);
    var input = function () {
      self.postMessage('stdin');
      var t = null;
      DB.transaction(function (tx) {t=tx});
      var i, res;
      while (!(res = t.executeSql('SELECT * FROM input').rows).length) {
        for (i = 0; i < 100000000; i++);
      }
      t.executeSql('DELETE FROM input');
      return res.item(0).text;
    };


And in the UI thread:

    worker.addEventListener('message', function (e) {
      if (e.data === 'stdin') {
        console.input(function (data) {
          DB.transaction(function () {
            tx.executeSql('INSERT INTO input (text) VALUES (' + data + ')', []);
          });
        });
      } else {
        // Do other stuff
      }
    }, false);

The Web SQL Database spec is deprecated for the IndexedDB which has not fully landed in browsers yet but this approach, in theory, should work with it.

### Why all this?

I ran into these issues during my work on [repl.it](http://repl.it) last year. And my recent on and off work on allowing debugging JavaScript in the browser at [codecademy](http://codecademy.com).
