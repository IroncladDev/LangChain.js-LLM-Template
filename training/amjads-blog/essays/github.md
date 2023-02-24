{
  "title": "Github and Open-source Is a Boon for the Underprivileged",
  "image": "https://cdn-images-1.medium.com/max/1600/1*lBVMxcsvMHSkghlAo1-5GQ.png",
  "date": "06/09/2018"
}
---

I was born to immigrant parents. My mother's family left Algeria looking for
a better life in Syria and then Jordan (where I was born). On my father's side,
his family fled the war in Palestine to Syria and then settled in Jordan. My father's family was so poor that he had to sleep with ten
other children in the same room (his brothers and his brothers'
children). Luckily, Palestinians, for whatever reason, valued education above
everything else, so they made sure to save up to send my father to Turkey
(because there were no universities in Jordan at the time) to study to
become an engineer.

When my father came back to Jordan, he worked for the government as an engineer. There, he
faced discrimination because government jobs were typically reserved for
natives. Despite all this, he rose in the ranks for years until he became the
city manager of Amman, the capital of Jordan. My father's journey taught me
that as someone who's underprivileged or discriminated against you need to work
ten times harder than the next person to get ahead. You need to leverage
whatever tool you have to signal that you're great at your job. For him, it was his reputation. In a country ravaged by corruption my
father had a reputation for being so straight it baffled people (but it also
meant that we wouldn't get to see any of that corruption money, and we had to
grow up on a measly government salary).

Which brings me to the recent debate in the developer community on using GitHub
as a résumé. While I try to stay away from debating hot topics because it takes time to form an informed opinion, this was a subject that's near
and dear to my heart, so I had to write about it.

It all started with this tweet claiming that GitHub is the only way that
employers can validate talent.

<blockquote class="twitter-tweet" data-lang="en"><p lang="en" dir="ltr">10/ GitHub is the de facto source for validating top talent the world over.<br><br>Résumé or CV? <br><br>Please.<br><br>Show me your GitHub profile, commits you&#39;ve landed, projects you&#39;ve forked, code you&#39;ve released.</p>&mdash; Joe McCann (@joemccann) <a href="https://twitter.com/joemccann/status/1004798006485573632?ref_src=twsrc%5Etfw">June 7, 2018</a></blockquote>

While I disagree with this statement, I found myself also disagreeing with
people on the other side of the debate which, in my opinion, are also staking
out an extreme position. They're [saying](https://twitter.com/EricaJoy/status/1004849360625168384) that GitHub is not only a "useless
signal" but is also discriminatory by nature. (I found
myself agreeing more with moderate positions like Kim's
[here](https://twitter.com/KimCrayton1/status/1005098820731097088) saying that basically, employers are shooting
themselves in the foot by excluding people with no GitHub profiles).

Starting with the assumption that employers would want to hire the best candidates for
the job[1], we can observe that they're
merely trying to navigate the problem of "adverse selection," which occurs in any
market where there exists an asymmetry of information. Because candidates can deceptively
spruce up
their resumes and maybe even rise in the corporate ladder by being gifted at
office politics, and because most good programmers are not in the job market
(they either have a job or get headhunted before they enter the market), this
leaves employers in a tricky position with an insufficient set of tools to evaluate
candidates (see [The Market for
Lemons](https://en.wikipedia.org/wiki/The_Market_for_Lemons) for an interesting
discussion on adverse selection). GitHub, on the other hand, cuts through the
bullshit (for the most part).

You can fake a resume, or end up with a good one simply as a function of
your privilege. For example, if you're born into wealth,
your parents can probably call in favors to get you jobs at prestigious
companies. But can you really fake GitHub profile? It's tough to do so,
and that's because the "screening", as it were, is done by OSS maintainers. You
can't bullshit your way into getting pull requests landed. And no matter your parent's
standing in society, if your code stinks, you can't contribute. This makes GitHub a
precious tool for recruiters.

Because open-source is good at cutting through the bullshit, it also makes it an equalizer. If you come from an
underprivileged background, you should absolutely use GitHub to get ahead. That's
exactly what I did. I owe my entire career to open-source.

Back in college, I didn't have a personal computer, and I was always on the
move -- from campus to the office, to home. Which made it tough to code
on projects, or solve homework because every time I got my hands on a computer, I
needed to setup the development environment. So I started dreaming about a world
where I can open a browser tab and start coding, in any language,
anywhere. Which started a multi-year project to build an in-browser repl. The
first thing I did was put a textarea with a button that `eval`d JavaScript. I was
able to program on my Nokia phone and work on problems on the go. But I wanted
this experience to be better and to work for more languages.

[Long story](https://news.ycombinator.com/item?id=16578943) short, years after I
had the idea for an online repl was I able, with help from
friends, to build the first polyglot [in-browser repl](https://github.com/replit/jsrepl) along with a [web terminal](https://github.com/replit/jq-console)
implementation. I tried to start a company around this idea, but nobody would
fund me. Luckily, everything was open-source on GitHub and soon after we
released the project I saw that not only one, or two, but more than a dozen
companies in Silicon Valley started using our software.

Although I had applied so many times to work at Google, Facebook, and many
others, I never got a response back, let alone an interview. Open-source became
my ticket there. I joined Codecademy as the #1 employee and helped 10s of millions
of people to learn how to code.

Afterward, I joined Facebook to try and work at the team behind React.js. But I
was stuck working on the photos product (which I couldn't care less for) because
the React team was one of the hottest teams at the company. So
I started contributing to their open-source projects. I know it sounds crazy and
roundabout, but I was able to prove myself more via my GitHub contributions than my
day job. I think that played a big part in letting me in the team where I worked on
React Native.

Today, I'm trying to pay it forward. At my new company, [Repl.it](https://repl.it), we believe that
programming is a great equalizer. We've seen our product used by [refugees](https://repl.it/site/blog/refugees) to
learn how to code. By people to [upgrade](https://repl.it/site/blog/two_stories)
their careers and land tech jobs and to
[teach](https://repl.it/site/blog/two_stories) low-income high-achieving children how to code. Or by [homeless](https://www.reddit.com/r/learnpython/comments/54d53z/help_a_homeless_man_code_again/) people who
only have access to computers at the public library. At this point, we've heard enough "rags to
riches" stories in programming that it becomes difficult to dismiss this as
simply "survivorship bias".

To conclude: if you come from an
underprivileged background then the unfortunate reality of the situation is that
you're going to have to work harder than everyone else. And you're going to want
to use any tool at your disposal, like Github, to signal that you're you going
to be great at your job so you can land great jobs.

If you need advice, I'd be happy to help, my DM are open on [twitter](https://twitter.com/amasad).

----------------------------------------------
<small>
[1]: It's still a safe assumption to start with, even if it's not entirely
accurate. Even if you believe that bigotry (or unconscious bias) plays a big part in
excluding people, I think that from a first-person point of view, you can't control
that. For example, it's hard for me as an individual Muslim to change the fact
that some people hate Muslims, so it's better for me to focus my energy on
things that I can control. This, however, doesn't mean that as a society we shouldn't discuss issues of
discrimination.
</small>