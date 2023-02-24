{
  "title": "On Hosting Sites from Your Editor",
  "date": "03/08/2021",
  "image": "https://amasad.me/public/images/hosting.png"
}
---

This website is hosted on an [editor](/__repl). I can update it live and I can even see you visiting it in my editor [console](https://blog.replit.com/internet-of-fun).

This idea is not too far from how we used to make websites in the 90s and early 2000s. You wrote your code and FTP'd it into remote server and restart the webserver process to pick up the changes. Today, most people do it by git-pushing to a PaaS provider. I've been hosting apps, sites, bots, and microservices from my editor for the last two years, and in this post, I'll share my experience. While I've been doing in Replit, where it collapses your entire workflow into your code -- a code-first environment -- the following applies to anyone who's hosting code directly from where they wrote it.

When writing code, the development environment feels closest to you. It's where you are making the changes and seeing your creation come to life. After coding, in a typical workflow, you push up your code for storage and sharing (to something like GitHub). If your changes are ready to release, you'll also push them to a hosting provider (say Heroku). Here is a diagram of it:

![a diagram showing three different environments: localhost, production, git](/public/images/hosting.png)

The moment you send your code to a remote environment, you've created distance between you and your creation. It's living in a different environment where it's not easy to inspect and update. You've fragmented your workflow and now have two other locations where your code lives, and while git is great and maintaining copies of code, you've introduced multiple potential sources of truth. 

This destroys momentum especially for early-stage startups, side-projects, and those who are learning to code. Sadly, the "industry standard" often gets applied indiscriminately, robbing people of a superior mode of creation and all the fun and reward that comes with it. 

The alternative: 

![a diagram showing one environment](/public/images/hosting2.png)

When hosting from your editor, you're moving fast, updating the site and seeing crashes and debugging issues in realtime. For example, in Replit, I can enter the production repl and see active connections, inspect, and even hot-update live objects. 

<blockquote class="twitter-tweet"><p lang="en" dir="ltr">I was wondering if the app is already getting usage and one of the wonderful things about hosting on <a href="https://twitter.com/replit?ref_src=twsrc%5Etfw">@Replit</a> is getting a live repl on the hosted app. <br><br>Here I just got a reference to the db and listed the entries. <a href="https://t.co/UIoERFc50D">pic.twitter.com/UIoERFc50D</a></p>&mdash; Amjad Masad ⠕ (@amasad) <a href="https://twitter.com/amasad/status/1332029622075047936?ref_src=twsrc%5Etfw">November 26, 2020</a></blockquote> <script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>

Having a production repl is super valuable. Paul Graham recounts how he used the Hacker News prod repl to react to an issue from his phone: 

<blockquote class="twitter-tweet"><p lang="en" dir="ltr">I once had to write code on a phone, after HN mistook investor usage on Demo Day for a DDoS attempt and started ignoring the venue&#39;s IP address. I had to log into HN on a phone and paste a fix into the repl. This looks a lot more civilized.</p>&mdash; Paul Graham (@paulg) <a href="https://twitter.com/paulg/status/1255235112226238466?ref_src=twsrc%5Etfw">April 28, 2020</a></blockquote> <script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>

Another issue I've run into with today's standard workflow is projects going stale. After leaving a project for a few months the barrier to going back to hacking feels high: I'd have to pull, set up the dev environment again, and figure out how the hosting provider is configured. However, when hosting from my editor, I open up the project, and I'm right there hacking and "deploying."

Because the distance from creation is reduced, I also start (and complete) many more projects. I'm quick to spin up something or to automate a piece of work. At work, because Replit feels close and fast, we spin up many bots to automate tedious tasks or introduce fun and serendipity. 

![lunch bot](https://pbs.twimg.com/media/EuCd-dvVkAwNO8K?format=jpg&name=medium)

Finally, in cases of emergency, it also helps to be able to code live. We've been able to respond to emergencies  at breakneck speed. For example, a few months ago PyPi quitely deprecated their package search API which we use in our packager UI. Luckily, we found a package that searches PyPi via scraping the site. We spun up an alternative on Replit in 30 minutes:

<blockquote class="twitter-tweet"><p lang="en" dir="ltr">Multiplayer <a href="https://twitter.com/replit?ref_src=twsrc%5Etfw">@replit</a> story: <br><br>3rd party service deprecated w/ no warning 😱<br><br>I spun up a repl with and prototyped replacement ⚡️<br><br>Single-threaded couldn&#39;t handle 1 rps 😢<br><br>Someone jumps in w/ `uwsgi` now we&#39;re at 3 rps 💆🏽‍♀️<br><br>Dropped in LRU and now we&#39;re up to 50 rps 📈<br><br>Good—Shipit!</p>&mdash; Amjad Masad ⠕ (@amasad) <a href="https://twitter.com/amasad/status/1340108478967267329?ref_src=twsrc%5Etfw">December 19, 2020</a></blockquote> <script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>

I'd like to see the dev community introduce more fun and interactivity back into building, especially when teaching new devs how to code. Most bootcamps today spend their first weeks teaching people git. But their students have no mental model for version control to be able to grok git, so it just starts on the wrong foot with people feeling inadequate or dumb for not "getting it." 

Seymour Papert called this the ["project/problem inversion"](http://www.papert.org/articles/AnExplorationintheSpaceofMathematicsEducations.html). The natural way to acquire knowledge of new tools is to have the use-case for them; today new developers are taught to cargo-cult advanced development techniques before they've even finished learning how to code. 