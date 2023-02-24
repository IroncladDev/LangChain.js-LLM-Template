{
  "title": "Overcoming Intuition in Programming",
  "date": "01/03/2016",
  "hidden": false
}
---

In a [series of experiments](http://faculty.chicagobooth.edu/nicholas.epley/alteretal.pdf),
researchers set out to discover the relationship between difficulty or
"disfluency" and cognition. They presented the same test to two groups, one in
an easy to read (intuitive) format and the other in a difficult (disfluent)
format. And in all the experiments they carried out, the disfluency group scored
substantially higher. The theory behind this is that people will default to
relying on the automatic, effortless, and primitive system for reasoning. But if
things are counter-intuitive or harder to understand we switch to the deeper,
deliberate and analytical mode of thinking.


I've been thinking about how this translates to programming. Programming is an
intellectually challenging task, but luckily we invent tools to make it
manageable. I find that up to a certain point, the intuitive and easy properties
of a given language, framework, or library might start to have negative
effects. From personal experience and from mentoring beginners I noticed that
when using tools that allow us to reason within our intuition, anytime we're
faced with some difficulty we feel that we've done something wrong. And although
we might have the necessary skills to overcome the difficulty, we often start
questioning and revising our work. Asking questions about best practices
relative to the framework instead of programming our way out. The quintessential
example of this is the Stack overflow questions for _"how do I use jQuery to do
X?"_ or the answers _"use jQuery [plugin] to do X"_ where X could be anything from
basic arithmetic to websockets.

### The framework negative space

When using a framework, a certain class of problems are made easy to
solve. Programming feels intuitive if we stay within that space created by the framework. We
may refer to this as the __framework intuitive space__. On the other hand we may refer to the
rest of the space that framework doesn't solve or have an opinion on
as the __framework negative space__. The negative space
is not necessarily a defect of the framework, it's just not in the space the
framework was built to solve. However, having put the programmer in the intuitive space for a
long stretch of time, it makes it feel out of place when finding oneself in the
negative space.

When the beginner programmer find themselves in the negative space, they often
look to the library authors to put them back in the intuitive space. That's why
for any popular framework you find that there is an entire ecosystem of plugins
and addons that extends the framework's intuitive space to cover an increasingly
growing surface area. It doesn't seem to be inherently wrong if it makes
programmers more productive. However, it may have unintended negative consequences:

1. Increased reliance from the programmer on the ecosystem's library authors
2. Offloading of architectural decisions to the libraries all the while
incurring technical debt
3. Enabling the false belief that programming should always feel intuitive

### The developer and library author codependency

I should start by saying that this is technically a false dichotomy. All programmers
take on both those roles in any programming session. You maybe coding the product
business logic and switch to building a general purpose abstraction to help you
in multiple places in your codebase. However, I've noticed that in open-source, people tend
to act in a manner that makes this dichotomy seem true.

The easiest way I've found to succeed in open source is to pave the negative
framework space to become an intuitive space. In other words, writing the
plugins and extensions. As a framework becomes more popular, a growing number of
developers (usually beginners) will start complaining about how it's hard to do
X in this framework (and as we've seen X might be totally unrelated). Now, as in
the business world, open-source is extremely competitive and as soon as there
is an opening to solve a perceived problem for a lot of people, many would rise
up to the occasion. This becomes an enabler to the false belief that a
programmer can spend all of their time programming in the intuitive space.

### Conclusion

I think fixing this problem ultimately comes down to education. Very early on
when someone is learning programming our culture tend to emphasize an obsession with
tooling. I get a lot of questions from aspiring programmers on what's the best
tool or languages to learn. It's almost always a premature question to ask. I
used to come up with answers like "depending on what you're building" or "pick a
beginner friendly community" or "invest in a growing language". I
think all of these are good answers, but it doesn't really matter that early on
in a programmer's learning journey. It's all the same when you're
essentially learning how to compute. Furthermore, these sort of answers enable
the culture of tooling obsession.

Code reuse, libraries, sharing, and open-source are very important to software
engineering, but we should be careful to not enable the belief that programming
should be as easy as gluing things together. In fact, these days I'm often
skeptical when things feel a little bit too easy. If programming was as easy as
this then it would've already been automated away.
