{
  "title": "John Carmack on Idea Generation",
  "date": "03/09/2016"
}
---

Last year at an internal talk at Facebook I was fortunate to see [John
Carmack](https://en.wikipedia.org/wiki/John_Carmack) speak about his idea generation system. At first I was disappointed
because I was expecting one of Carmack's famous technical talks where he spends hours talking
non-stop about programming languages, game development, large scale software
engineering and many other interesting technical topics.

Instead, he opened with talking about -- what is now a Silicon Valley cliche --
how ideas are overrated and execution is everything. Of course, cliches are
sometimes cliches because they're true. However, things took an interesting turn
when he mentioned the "Antifragile" concept.

## Antifragile

A phenomena discovered by Nicholas Nassim Talib that describes things that are
the opposite of fragile. We don't currently have a word to describe this in
English. You might think that words like "robust" or "resilient" come close
but actually those words describe systems that don't break under stress, but
what about things that benefits from stress?

To me, this was one of those questions that you realize is simple but
you're surprised that it hasn't entered your consciousness until this day.

Here is the description from the [Antifragile book](http://www.amazon.com/gp/product/B0083DJWGO/ref=dp-kindle-redirect?ie=UTF8&btkr=1):

>Just as human bones get stronger when subjected to stress and tension, and rumors or riots intensify when someone tries to repress them, many things in life benefit from stress, disorder, volatility, and turmoil. What Taleb has identified and calls “antifragile” is that category of things that not only gain from chaos but need it in order to survive and flourish.

After picking up this book and reading it, I was not only able to relate this
back to Carmack's idea system (more on this later) but saw the world in a slightly different
way. To give only one example, I see large open source software as antifragile. The
more stress people put the software under the better it becomes. The more
people use it in unanticipated ways and the more code path combinations are
exercised then the more bugs are found and fixed. In contrast, proprietary
software is usually used in controlled environments all the while building up
fragility for a major catastrophic event waiting to happen (see [Black Swan
Theory](https://en.wikipedia.org/wiki/Black_swan_theory)).

## Antifragile Idea Generation

In programming and many other creative jobs you get many ideas in any single
day, but you can only implement a fraction of them. The fraction you haven't
implemented you might start obsessing about. Everyone has their pet ideas that
they go around discussing. The more time this idea spends in your head the less
critically you think of it. Now, when the time comes to
actually try implementing it, if it fails you're left discouraged, embarrassed and might even
quit the project you're working on.

This is obviously a fragile system. You start neutral, get a small high when you
first get the idea, and then it starts building up fragility while in your head. If and when it fails it's
catastrophic on your productivity.

So what does an antifragile system for generating ideas look like? First let's
lay out some criteria:

1. Antifragile systems are -- by definition -- able get the upside but are not
affected by the downside. That means, we need to be able to get the initial idea
high and the motivation that comes with it.
2. Failure events must end up making our system stronger. Meaning when an idea
fails it needs to make the overall system better.

Here is what Carmack thinks an antifragile system might look like:

1. You are working on a problem and you get an idea and with it the initial idea
high
2. You should instantly try to defeat your idea -- think of all the ways it
could not work, test it out, put it under stress
3. If the idea survive the brutal scrutiny then it has legs for further
investigations or implementation
4. If the idea is implemented and it works then that's great
5. If the idea fails the scrutiny or implementation you can quickly move on to
the next idea without feeling the lows because you haven't
obsessed or talked about it i.e. it's not your pet idea.

Carmack describes how this becomes like a game -- as soon as you get an idea you
try to defeat it. You'll be able to generate more ideas because you freed up
mental space. Furthermore, your existing ideas will
even be stronger because they survived heavy scrutiny.

## In Practice

I've been using this at work and in my personal life for a few months now and I
recommend it to everyone. I end up prototyping a lot more and going through many
iterations of ideas. And that reminded me of my early days of programming. Because I
didn't know what was possible or not, I had to vet all my ideas by
coding them up. I went through multiple VB projects in any single day.

At work, we're now focused on JavaScript and web performance, and found this an
indispensable tool for this type of work. Optimization work (after crushing the
low-hanging fruit) is often counter-intuitive and many ideas that sound great in
theory end up tanking in practice. So to make progress we need to have a lot of
ideas and try many of them. And this gave me great framework to approach this with.
