# Debugging

Repls that are written in the following languages can use a built-in, multiplayer debugger:

- C/C++
- Java
- JavaScript (Node.js)
- Python
- With more coming soon (through [Nix](/programming-ide/getting-started-nix)).

To get started with the debugger, click on the Debugger icon on the sidebar:

![Debugger panel](https://replit-docs-images.util.repl.co/images/animations/open-debugger.gif)

Now you can start adding [breakpoints](https://en.wikipedia.org/wiki/Breakpoint) to your repl: breakpoints are lines of the code where the program will be paused during execution while debugging. Breakpoints don't affect the program when run normally. When the program is paused, the Debugger sidebar will show the values of all variables, avoiding the need for adding print / log statements.

When the program is paused, the other buttons will be enabled:

- "Next Step" will advance the program to the next possible line where the program can be stopped inside your source code. For instance, if the current line is calling a function, "Next Step" will go inside the function. If it is the last line in a function, "Next Step" will return to where that function was called.
- "Next Breakpoint" will advance the program to the next breakpoint, or until the program finishes if there are no more breakpoints after the current one.
- "Stop" terminates the debugging session and kills the process that is being debugged.

## Multiplayer features

When debugging a program in a repl, all participants will see all the actions that any other participant does. This means that the debugging experience will be shared by all the participants in a repl. This includes:

- The breakpoints.
- The place / time where the program is paused.
- The contents of the variables.
- The output of the console.

## Adding support for other languages through Nix

Coming soon!
