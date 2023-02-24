{
  "title": "Dialectical Progress in Programming",
  "date": "05/27/2017"
}
---

The notion of progress in programming is -- as in anything else -- debatable and
hard to define. For various reasons that are besides the point of this essay I
believe that we're indeed making progress in the art of programming (otherwise
what's the point in getting up in the <s>morning</s> afternoon and going to the
office?).

But how does progress happen in programming? Sometimes it looks like it's an
arbitrary walk in the space of possible languages, frameworks and
architectures. I'd like to propose an answer: _programming progresses
in [dialectical](https://en.wikipedia.org/wiki/Dialectic) fashion_. Meaning what usually follows the current best
practices and technologies is an opposite in many ways. However, this is usually
followed by a _synthesis_ of these two opposites. In other words, a compromise
or a _best of both worlds_.

We can think of this as a [_thesis, antithesis, synthesis_](https://en.wikipedia.org/wiki/Thesis,_antithesis,_synthesis):

>(1) a beginning proposition called a thesis, (2) a negation of that thesis
 called the antithesis, and (3) a synthesis whereby the two conflicting ideas
 are reconciled to form a new proposition.

Let's look at some examples.

### Languages: industrial strength vs developer friendliness

1. Thesis: __industrial strength programming languages__. Languages like Java
and C++ are type-safe, efficient and work well with large systems. But they're
also hard, boring, noisy, and take a long time to compile.

2. Antithesis: __developer friendly languages__. Languages like JavaScript,
Python, and Ruby are dynamically typed so the syntax is clean and less
noisy. They're interpreted so there is no compiler to wait for. And they're fun
and arguably more productive to work with.

3. Synthesis: __developer friendly and suitable for large scale
programming__. Languages like Go, Rust, and TypeScript are both type-safe,
efficient and work well at large scales.

### Web rendering: server-rendered vs client-rendered pages

1. Thesis: __server-rendered pages__. Languages and frameworks powering Web 2.0
like PHP and Ruby on Rails can get you to market quickly, with predictable
performance, and works well with the rest of the web infrastructure (links,
search engines etc).

2. Antithesis: __client-side rendered pages__. Frameworks like Backbone, React,
and Angular can create delightful user experiences. But they break the web's
protocol (hypertext over TCP) and can be slow to boot up.

3. Synthesis: __universal rendering__. Frameworks like [Next.js](https://github.com/zeit/next.js/) bring us the best
of both worlds: a great user experience, great initial render time, and great
support for search engines and other web infrastructure.

### Mobile apps: native vs web

1. Thesis: __web applications__. Web 2.0 unleashed the power of the internet and
brought us amazing applications like social networking and YouTube. But
when mobile came around, using web tech to build mobile apps created monstrosities
like the first Facebook HTML5 app.

2. Antithesis: __native applications__. Native applications brought much better
user-experience with gesture support, smooth scrolling, and access to APIs
like location and notifications. However, a lot of progress that we made in
engineering (e.g. continuous deployment, cross-platform development) or in application distribution (just
visit a URL) had to be thrown away.

3. Synthesis: __progressive web apps and web tech adapted to native__. PWAs
and frameworks like React Native bring us the best of both worlds. Access to
native (or native-like) APIs and a great user experience but also cross-platform
development, continues deployment and better application distribution
strategies.

### Conclusion

This framework of thinking about progress in programming seems to apply to a lot
of what I see happening in programming. There are ongoing developments that I
look forward to seeing the synthesis of:

- __Web development build tools__: we started out writing and loading scripts
  in the browser verbatim but applications getting more complicated lead
  us to build better languages and frameworks which lead us to
  introduce ever more complicated build-steps to our web developement and
  deployment pipelines. However, with browser vendors moving faster on supporting
  language features and with framework authors acknowledging the problem I think
  we're going to see a synthesis soon.
- __IDEs__: when I first started programming it seemed unquestionable that you
  needed to use an IDE. However, they were slow and bloated. And with the shift
  towards more dynamic languages there was also a shift towards pure text
  editors like Textmate and Sublime and a return to Vim and Emacs. However,
  with editors like Atom that has a richer-than-ever plugin ecosystems it seems
  like we're headed in a synthesis direction where we use lightweight editors
  while plugging in static analysis, autocompletion, and other automation tools.

There are a lot more industry trends that can be described and understood using
the dialectical framework of progress. I'd be curious to hear your thoughts
on this and if you think if this framework applies to trends in your programming
community. I'm best reachable on [twitter](https://twitter.com/amasad). Thanks for reading.
