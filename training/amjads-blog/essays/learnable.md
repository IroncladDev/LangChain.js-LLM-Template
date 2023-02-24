{
  "title": "Implementing Bret Victor's Learnable Programming",
  "date": "01/10/2014",
  "hidden": "true"
}
---

A few days ago I [released debug.js](http://amasad.me/2014/01/06/building-an-in-browser-javascript-vm-and-debugger-using-generators/) and I breifly touched on the educational applications of the library. This morning, I had a couple of hours before going to work so I decided to implement the “Make flow visible” example from Bret Victor’s [‘Learnable Programming’ paper](http://worrydream.com/LearnableProgramming/) (Feel free to change the code):

<iframe width="130%" height="300px" src="https://amasad.github.io/learnable-programming-demo/" style="margin-left: -15%; border: 1px solid #EBF2F6;"></iframe>

[_premalink_](https://amasad.github.io/learnable-programming-demo/)

Here is how it’s done:

1. Given a program, step through it once using [debug.js](https://github.com/amasad/debugjs) to get the execution flow info
2. Plot the execution flow using [d3](http://d3js.org/)
3. Whenever the user scrubs through the plot, rerun the steps up to the step index that the user has the pointer over.
4. Repeat from 1 when the editor code change

The entire thing is ~250 LOCs and is [up on Github](https://github.com/amasad/learnable-programming-demo).
