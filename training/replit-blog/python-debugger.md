---
title: Introducing Step Debugging for Python
author: Amjad Masad
date: 2016-11-28T08:00:00.000Z
categories: product
---

## Debug your Python3 programs from your browser

At Repl.it, our goal is to make programming more accessible, and as part of this
we aim to provide the full power of popular programming environments with no
setup time. And I don't think it's an understatement to say that debugging is
the majority of what we, as programmers, do. [](preview end)

That's why today we're making it possible to step-debug through your Python 3
code right from the browser. We've built a new debug pane that makes it easy
step in, out, over, and resume your code. All the common operations a typical
debugger would do.

![debugger](https://i.imgur.com/oerWaQR.gif)

To get started:

* write your code
* click the "debug" button on the top right corner of the editor
* a debug pane will pop-up underneath the console
* this allows you step through your code

Note that this is still in Beta and we have a lot we want to improve on it. The
obvious thing that we'll be adding shortly is support for breakpoints. But
that's not all, we want this to be on parity with the best debuggers in
industry:

1. Add breakpoint support.
2. Add a scope pane to see what variables are in scope and what are their values.
3. Evaluate expressions in context.
4. Add watch expressions.

Give it a spin on this recursive [factorial program](https://repl.it/E9oT).

Let us know if you hit any bugs or if you have any feature requests. Happy debugging!

p.s. [we're hiring!](/site/jobs)

_Thanks to [Thomas Ballinger](https://twitter.com/ballingt) for his help in designing and implementing the
remote Python debugger service._