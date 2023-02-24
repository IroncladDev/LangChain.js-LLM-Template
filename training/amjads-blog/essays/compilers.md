{
  "title": "Why Learn Compilers",
  "date": "12/29/2021"
}
---

A sufficient understanding of computers is impossible without learning how compilers and their parts work. It is like stepping into the computer's mind and seeing how it feels from the inside. Compilers are also some of the most satisfying programs to write. Finally, learning compiler technology can open new artistic avenues for you, and provide a skill bordering on a superpower.

## A most fun sandbox

Because the most basic compiler architecture is standard, you have limited boundaries and degrees of freedom when designing one. This might sound restricting, but actually, it's freeing because you get to play in a predictable sandbox. 

And because compilers are largely deterministic closed-system problems -- for each input, there is one and only output -- it makes it really fun to iterate on a program without having to worry about external dependencies or a complicated setup. This lends itself nicely to test-driven development -- you can unit-test the component parts and write end-to-end tests for the compiler as a whole.

Writing the test & debugging framework around compilers can also be really fun. To test a parser, for example, you need to run assertions on massive syntax trees, and you need to output helpful failure messages. You can go as far as writing a Domain-Specific testing language to make testing more pleasant.

## A most magical flow experience

The most fun I had coding was when I led the JavaScript infrastructure team at Facebook. We were tasked with replacing [JSTransform](https://github.com/facebookarchive/jstransform), a string-manipulation-based JavaScript transpiler. Honestly, it's amazing it worked at all, but it didn't work very well. I resided in NYC but went up to our office in Cambridge to work with one other engineer there. However, I ended up mainly working alone, coming in every day for two weeks and writing code for 10 hours a day. I was in a state of flow.

The leading expert on "flow," Csikszentmihályi, identified that for a human to enter a this state, they need to be able to get direct and immediate feedback, for the problem to be well-defined, to have a balance between one's ability level and the challenge, and have a sense of control over the situation. I can't think of a better programming task that hits all those points than writing a compiler.

## Useful skills

I joined Yahoo! for my first job out of college, who'd just acquired a company in my hometown. As part of the acquisition, we were tasked with moving to the Yahoo! stack, and they were adamant about us using YUI instead of jQuery. The task fell on my lap, which felt like a crushing mountain of repetitive work. 

Like any good (read: lazy) programmer, I decided to automate the task. The task was more intricate than simply a massive search and replace because you had to deal with many variations of names, formatting, and patterns. I'd been learning about compilers and ASTs, and I figured this was an excellent time to deploy my newfound skills. 

First, I backfilled into YUI some jQuery-like to make the transition easier. Then I wrote a transformer that took in jQuery code and automatically translated the calls into YUI code. 

A many-month project turned into a week project. My colleagues were dumbfounded when they saw the volume of patches flying out of my desk. This is the kind of leverage that compiler technology can give you. 

## Do it for the art 

What do compilers have to do with art? Surprisingly I've found them a great source of inspiration for art projects. 

When you look at a program in your editor, you're often able to deduce what the program does from its shape or [pattern](https://www.dreamsongs.com/Files/PatternsOfSoftware.pdf). Programs have a visual identity; many are beautiful. So if they have a form, wouldn't it make sense to also have a sound? 

So how do you make code audible? One way, I thought, is to make running a program sound like something. It wasn't clear how I would do that. A more straightforward idea was to give the syntax tree sound. What does a code block sound like? A statement? A conditional? 

I decided to map the sounds from an 808 drum machine to AST node types. Take a listen [here](http://soundofjs.com/), and if you listen to enough programs, I believe you'll be able to identify them in the same way we recognize the shape of a program. You can also toy with the mappings themselves and make them sound differently. 

![soundofjs.com screenshot](/public/images/soundofjs.png)

Another art project that I had the pleasure to play a [small part](https://github.com/nasser/---/commits?author=amasad) in was [Qalb](https://www.albawaba.com/editorchoice/alb-arabic-computer-programming-language-understands-calligraphy-861614), the Arabic programming language. The most fun aspect of the project was not the language or the tooling to which I contributed, but it was the fact that Ramzi, the artist behind the project, showed that you could print programs as Arabic calligraphy tiles.

![qalb program](/public/images/qalb.png)

Finally, I can't talk about compiler art without mentioning [DOMQL](https://amasad.github.io/DOMQL/), a satrical project that add a SQL-like language to the browser and claims it's a better frontend programming experience than JavaScript.

## A better coding UX

In my [Computers Doing The Right Thing essay](https://amasad.me/right), I talked about how we can build more delightful software by detecting user intent. I gave the example of deducing the software packages the programmer wanted to install by from the code, and installing them for the user. This is of course, done by parsing import statements in the respective language. The code for this is open-source -- here is, for example, the [Go-based JavaScript parser for that](https://github.com/replit/upm/blob/715e4d1bd301b66b209a6c5cf1345f59aaa0799a/internal/backends/nodejs/grab.go#L91-L216).

![upm in action](https://amasad.me/public/images/import.gif)

To build delightful coding experiences, it helps to master parsers.I'm incredibly excited about the work we're doing with our live game programming environment: Kaboomjs.

<blockquote class="twitter-tweet"><p lang="en" dir="ltr">Preview of upcoming creative coding magic (and like everything we do, multiplayer). <a href="https://t.co/7i4KakNpeW">pic.twitter.com/7i4KakNpeW</a></p>&mdash; Amjad Masad ⠕ (@amasad) <a href="https://twitter.com/amasad/status/1474455969685901312?ref_src=twsrc%5Etfw">December 24, 2021</a></blockquote> <script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>


## What Is It Like to Be a Compiler?

As a programmer, you spend much of your day conversing with your compiler. If you're not happy at work, there's a good chance it's because you have a bad relationship with your compiler. Maybe it's too slow, taking you out of the flow state. Perhaps it's giving you inscrutable errors. Or maybe the language has undefined edge-cases, and you don't know what kind of code the compiler is emitting. 

All those are reasons to get in and understand how compilers work. Once you do, you'll have a whole new appreciation of programming and how languages are constructed. You'll be able to reason about your programs in new ways, and you can predict how it could go wrong. 

I hope this inspires you to design a toy programming language or compiler. Last year, at Replit, we ran a [massive programming language jam](https://blog.replit.com/pljamresults), and it turned out to be one of the funniest hackathons we ran. It introduced many people to the joy of language design and compiler construction, and I hope to repeat this again in the future. 