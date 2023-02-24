{
  "title": "The Stoic of Open Source",
  "date": "01/13/2016"
}
---

Two unrelated things happened recently:

1. A few high profile open source maintainer burnouts<sup>1</sup>
2. I've been reading a lot of philosophy<sup>2</sup>

I was first introduced to Stoicism by a friend who recommended the book [A Guide
to the Good
Life](http://www.amazon.com/Guide-Good-Life-Ancient-Stoic/dp/0195374614). And
they kept coming up whenever I'm reading about philosophy, and for good reason,
they're a cool bunch.

Stoics understood that you can never depend on external factors for happiness
and that the only way to achieve a sense of well-being is to be internally
satisfied. However, unlike the cynics or the skeptics, they *can* derive
happiness from the external world. In other words, **they get all the upside
while avoiding downside**. This sounds amazing, and at first glance it sounds a
bit like Buddhism, but I think the defining feature of Stoicism is their use of
psychological tricks and reasoning to achieve their goal of tranquility. That's
why I think it may resonate with the programmer community. Maybe we can learn
something from them about open source maintenance?

## insults and attacks

One thing that angers me -- and I see angers many open source
maintainers -- is the harsh criticism mixed with personal attacks that some
users launch against maintainers. There could be thousands of satisfied
users but a handful of loud and vile individuals could make your life
miserable. This can be related to how the Stoics dealt with insults. And they
had a lot to say about the subject.

Epictetus recommended that we pause to consider our insulter. If he is a fool then
rather than become angry or hurt, we should feel relief over his disapproval and
insults. Indeed, **we should be more concerned if we find the fool agreeing with
us**<sup>3</sup>. It goes without saying that someone launching personal attacks
against you for providing your work free of charge, is a fool.

>Begin each day by telling yourself: Today I shall be meeting with interference,
>ingratitude, insolence, disloyalty, ill-will, and selfishness -- all of them
>due to the offenders’ ignorance of what is good or evil?

> -- Marcus Aurelius

If you are putting yourself and your work in the public eye then it's very
likely that you're going to have a run-in with the above-mentioned unpleasant
people. So accept it as a reality and learn to deal with it.

Seneca suggests a potentially more useful way of dealing with insults:

> Why is it an insult, to be told what is self-evident?

If you found that there is some truth in the attack. Then simply extract that
knowledge as constructive feedback and use it to improve yourself and your project.

Those are some tools we can use to reason out the sting of the insult, but
what do we do about it? do we have to reply? The Stoics advocated two main ways of
responding to insults:

1. Humor
2. Refusing to respond

By simply laughing off an insult, we are implying that the insult and insulter
are not to be taken seriously therefore stripping them of any legitimacy that would
otherwise be implied if we replied seriously to their insult. Here are a couple
of amusing anecdotes from Seneca:

>Seneca points approvingly to Cato’s use of humor to deflect a particularly
>grievous insult. Cato was pleading a case when an adversary named Lentulus spit
>in his face. Rather than getting angry or returning the insult, Cato calmly
>wiped off the spit and said, “I will swear to anyone, Lentulus, that people are
>wrong to say that you cannot use your mouth!” Seneca also approves of Socrates’
>response to an even more abusive insult.  Someone once came up to Socrates and,
>without warning, boxed his ears. Rather than getting angry, Socrates made a joke
>about what a nuisance it is, when we go out, that we can never be sure whether
>or not to wear a helmet. <sup>4</sup>

If you are quick-witted then this type of humor may come naturally to you, but I'm
not. And, paradoxically, spending a lot of much time coming up with the perfect comeback
will have the negative effect of dwelling over the insult. Therefore the best
thing to do is act as if it never happened. This, first of all, robs them
of the pleasure of having upset us. And also shows everyone in the community
that we can't be bothered with childish behavior and we have more important
things to attend to (such as maintaining the project).

## on making mistakes

Everyone makes mistakes, and open source maintainers are no exception. You'll
eventually push a breaking change that will unleash a mob of semver purists
gunning for your head (refer to the previous section on how to deal with
obnoxious people). Here, I'll talk about how you should reason about the fact
that you made a mistake.

>Truths about the past are necessary: it is not merely that they aren't other
>than they are—they can't be other than they are, for nothing has the power to
>change the past -- Epictetus

Stoics were pioneers of logic, and it followed from their use of logic that
we should have a fatalistic attitude towards the past. We just learn from our
mistakes and move on -- there could have never been a world where you have not made
that mistake. Because without that event happening the world where you are now
looking back at that mistake doesn't exist. The last part was me going out on a
limb, but all this to say is that you can't change the past and there is no
point in feeling regret.

Mistakes may help you revise and strengthen your processes and tests. It may
even get your users to be more involved in the project's maintenance because they
see you as someone needing their help. I doubt that any one mistake has ever
caused the failure of an open source project, the important thing is to learn
and move on.

## work on your own terms

Taking a utilitarian approach to open source seems to be the best and most
sustainable. In the JS Infra team at
Facebook we have the following dictum:

> We only open source what we use in production

When we stop using something internally we either find a new home for it or
simply deprecate it. This puts us in a better position to serve our community. Similarly, you
can approach your personal open source projects with the same attitude. Keep
your project focused and fully aligned with your needs.

For example, if someone sends you pull request for a feature that you are not
going to use yourself and don't have the time test and maintain, then simply refuse it. It's
better to be focused in scope than to make the project suitable for every
possible use case while increasing your chances of burnout.

> Nothing is worth doing pointlessly -- Marcus Aurelius

People looking from the outside at open source are often amazed by how a
world based on altruism could exist. Sorry, it doesn't. A lot can be gained from
participating in open source. Slaving away with no explicit goal is a recipe
for disaster. I'm not saying that helping others is not a valid a
goal -- it could be, however, it should be intentional.

>It is impossible that happiness, and yearning for what is not present, should
>ever be united -- Epictetus

Try not tie your identity and sense of well-being to your open source
project. Align your needs with the community, get the upside of any contributions and
popularity. But try not to get affected by any downside.

---
<small>
[1] I've never been a sole creator/maintainer of a massively popular open
source project, however, I work as part of teams on massively popular open
source projects. So I probably don't understand the magnitude of stress sole
maintainers may feel.

[2] My favorite books so far: A History of Western Philosophy by Bertrand Russel,
The Guide to the Good Life by William Braxton, and the Philosophize This! podcast.

[3] Great [blogpost](http://throughablogdarkly.blogspot.com/2012/12/stoicism-dealing-with-insults.html?m=1) summarizing how the Stoics dealt with insults

[4] A passage from The Guide to The Good Life
</small>
