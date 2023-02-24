---
title: History++ - A Better Way to Do Versioning
author: Giuseppe Burtini
date: 2022-09-15
cover: images/history2-release/history-diff-compare.png
categories: eng,product
---

Have you ever had to start over on a piece of code because you overwrote something by accident? Made an edit, replaced it, and then wished you could go back?

Programmers have tools like `git` and the undo/redo stack to help them deal with challenges like this. Replit, of course, supports these things.

But, we think there's a better way. Over the last week, we rolled out the new history UI to general availability. Here's what it looks like:

<video src="/images/history2-release/history-story.mp4" class="css-3qjkrt" autoplay muted playsinline loop controls></video>

## The Basics
First, a bit of background. Whenever you make changes to your code, we add the [_operational transformations_](https://en.wikipedia.org/wiki/Operational_transformation) (OTs) to a log of activity for that file. OTs are part of our multiplayer infrastructure, they effectively store the "intended change" every time you edit a file. We use this for reconciling potential conflicts when many users edit a file simultaneously.

It turns out, this makes for a pretty cool approach to versioning and history. You don't have to do anything to benefit from it (it is happening anyway) and it produces a high-fidelity take on the historical states of your file, with no real mental overhead.

![A pointer to the "Repl history" link in the workspace](images/history2-release/history-how-to-get-there.png)


## The Utility

With version control system based history, like `git`, you have to make an active decision to create a commit, so your intermediary states get lost. Worse, for many users, the concepts and interface are difficult. We love `git`, but it is just a piece of the puzzle.

Here, you can browse a file's history, exploring it with the same interface that you normally use, seeing every change that has been made to it, and non-destructively restore to any specific version. We aimed for this to be lightweight, low-risk, and easy to use: a complement to the tools you are already using.

![A screenshot of the new history tool, showing a unit test suite written in JavaScript](images/history2-release/history-new-2.png)

Once you've found a version you think is relevant or interesting, you can toggle on compare mode to see a side-by-side diff. You can also select and copy some subset of the version or click restore to bring your file back to where it used to be.

![A screenshot of a side-by-side diff-view](images/history2-release/history-diff-compare.png)

## The Fun

One really cool way we've been seeing people use this is to use the playback feature -- which lets you watch your file's history like it is a movie -- to make videos of their programming sessions. 

We're going to do more to support sharing and social integration of these sessions going forward, but for now, it is already a really cool way to retroactively decide to share how you were thinking.

Some other neat upgrades:

- **Dark mode**: Old history didn't support dark mode. Sorry. New history does though!
- **Mobile support**: Maybe you noticed that old history was real awkward on small screens? Mobile now gets first class history support!
- **General polish**: You can browse the file tree like you would in the rest of your Repl, interact with a particular version like it is your regular code: copy-and-paste, compare, restore, and more.