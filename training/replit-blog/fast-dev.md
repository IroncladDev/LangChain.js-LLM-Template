---
title: Replit Case Study - Creating a 700+ User Web App in a Month
author: Rishabh Anand
date: 2021-03-23T00:00:00.000Z
cover: https://blog.replit.com/images/fast-dev.png
categories: projects
--- 

Hey there 👋🏻
My name is [Rishabh Anand](https://twitter.com/rishabh16_) and I am an ex-resident at the National University of Singapore's (NUS) [Raffles Hall of residence](https://nus.edu.sg/osa/raffleshall). It's one of the on-campus student accommodations that houses students from all levels of undergraduate education at NUS with the majority being freshmen and sophomores.

[RHDEVS](https://www.linkedin.com/company/rhdevs/) – the software development club at Raffles – was tasked by upper management to build a convenience app for the Hall’s student body. The app itself was nothing new; it has some basic features students would potentially use in their daily hall lives:

- Laundry
- Facilities Booking for clubs
- Events Booking / Management
- Calendar and Timetable Planner
- Crowd Tracking and Analysis (COVID-19 measures)

Here’s the catch: we only had a month and half from design, to implementation, to testing, before deployment and marketing. Like any startup, you’d expect us to start building MVPs for <5 users (i.e., the loyal few) and scale up from there, constantly iterating and shipping, asking for feedback, and growing organically.

Well, not here. We had to build for over 700 students from scratch.

Here’s how Replit saved my team during “hell month”.

## Serving and Deploying

I was the Backend Lead supervising a team of 13 student-developers who had little to no experience with server development and deployment. Every day came with a new set of learnings on what to do and what not to do.

Fortunately, the more experienced ones (minority) chipped in to teach the beginners (majority) how to write good server code. Soon, the semi-confident team split into groups, each focusing on different features with weekly deliverables and stand-ups in this one-month code sprint.

Backend is tricky business. All the infrastructure and apps the club builds rely on the backend’s services and stability. At our scale, without backups or custom on-premise hardware, a single crash would likely throw all the other services into limbo. Owing to budget issues, we did not have access to crash analytics either.

Our first one and half weeks were spent planning excessively. We charted schematics, drew ER diagrams, class diagrams, and more. We had to nail it in our first try or risk delaying the official launch window. The next few weeks were solely for development. There was no looking back.

The design team regularly sent us wireframes based on user feedback and we had to tweak our plans here and there.

## Where Replit Really Shines

### Faster Prototyping

In some way or the other, Replit definitely sped up our iteration cycles. From a motley crew that was once clueless on building servers, we became rapid-action deployers. The [tutorials](https://docs.replit.com/repls/http-servers) and [forums](https://replit.com/talk/all) saved us from a lot of Googling and Stack Overflow-ing.

Deploying on Replit allowed us to focus our energy on writing stable backend code. In fact, it gave us time to set a standard for writing code. We came up with a contribution and programming style guide – a luxury we wouldn’t have been able to afford if we spent our time fiddling around with complex server hosting platforms instead. It really set us up for future projects!

### Ease of Deployment

The team comprised of students who were well-versed in basic Python, but had never built any large-scale projects. 

Clicking the “Run” button in the IDE was enough to trigger a deployment, and this was a blessing for most of the beginner students. This meant we no longer had to worry about Procfiles, configurations, requirements, and virtual machine types.

For the unaware, most Python server hosting services require a user-submitted requirements.txt file with the packages and their right versions (the VM would then install them when deployed). Personally, the biggest “flex” Replit has over the other cloud providers is the automatic requirements.txt and config files generation; all we had to do is write our code and the IDE takes care of the rest.

An added bonus was the ability to add a .env file with our database keys and administrative credentials without worrying about intrusion or hacking.

Ultimately, we had around 4 dedicated servers taking care of different tasks. No doubt, one of the smoothest deployment procedures I’ve come across!

### Importing from GitHub

Our codebase is largely maintained on GitHub. Importing projects and collaborating on them with teammates was fun! We no longer had to huddle around someone’s laptop to see changes being made to the document. 

It’s like coding on Google Docs together; definitely gamified the experience :D

### Low Costs

We’re broke college students, remember? Our budget mainly went into frontend development, design, and miscellaneous administrative activities (like buying redbull and snacks for our sprints). 

The other guys (GCP, AWS, Heroku, DigitalOcean) were definitely out of our budget and expertise if we looked at the long term. The app would be used by a large percentage of the student body simultaneously in a day and naturally, these server costs would balloon up. We were not prepared for that just yet.

Perhaps, the most important benefit of using Replit was the inexpensive Hacker plan we were on. 

ICYMI: It’s free for students!

### Active Servers and Minimal Downtime

I mentioned above that many students would be using the app at any given time. Though, during non-peak hours (like those pesky late-night study sessions), there may be pockets of time where user activity is effectively zero.

Replit servers are designed to wake up automatically after periods of inactivity. My team was fortunate in that we did not have to build a heartbeat server to wake up dead servers, i.e., an additional manhour-intensive task we had no time for. It’s all taken care of under the hood.

## The Present

It seems like I’m overexaggerating certain things here. I assure you, I’m not. Replit was definitely a lifesaver when it came to creating servers without worrying about a lot of technical issues. For a fairly novice team, this was the best option we had. I’d definitely recommend starting out projects (like organisation intranets, game servers, application portals, and more) with Replit regardless of the team’s experience. 

It enabled fast prototyping, minimal but fruitful testing, faster deployments, and got us to launch faster than we had imagined. It has all the backend infrastructure services you need on a silver platter. For the skilled many out there, Replit offers support for practically every language out there!

Here’s a crusty screenshot of a COVID-19 rules-compliant call with the team:

![team screenshot](https://blog.replit.com/images/fast-dev.png)

Till date, RHDEVS is actively maintaining the app and is still using Replit as our backend. There are no plans of switching to the other guys anytime soon so lots more to explore, for sure!

Want to banter about Replit or tech in general? Slide into my DMs on [Twitter](https://twitter.com/rishabh16_)!