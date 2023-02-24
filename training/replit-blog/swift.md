---
title: A Swift REPL
author: Amjad Masad
date: 2016-06-14T07:00:00.000Z
categories: product
---

In this age of containers it's much easier to run arbitrary code
in the cloud. The harder parts are scaling the service, making it reliable, and
—as in this case— creating cool and useful experiences. When we looked at
existing Swift REPL implementations on the web we found that none
delivered a stateful and interactive environment. Just an editor with a run
button.[](preview end)

As for us, as much as possible, we try to create an environment similar to
the original inspiration for our website: DrScheme (now [DrRacket](https://racket-lang.org)).

![racket](https://i.imgur.com/dQZ0Jxk.png)

![repl.it](https://i.imgur.com/xRLWGYy.png)

_(I cheated a little bit to make them seem more similar by using repl.it's
preferences (⋮) to make the environment stacked as opposed to the default which is side-by-side)_

You code in the editor, hit run, and the
interpreter will run your code, and then drop you in the console to interact with
the resulting environment. The next time you hit run your code will be evaluated in a fresh
environment.

Today we're excited to announce the beta release for our Swift REPL that we're
hoping will work in the same way we outlined above.

![swift](https://i.imgur.com/JthbWsS.gif)

Try it here: [repl.it/languages/swift](https://repl.it/languages/swift)

Execute your code, and then you get to interact with it in the console. Call
functions you defined, change variables, and do as you please. Next time you
hit run you're loaded with a fresh environment.

We hope you find this useful. Let us know what you think and follow us on [twitter](https://twitter.com/replit)!