---
title: "Repl.it: the IDE That Grows—from Playgrounds to Fullstack Apps"
author: Amjad Masad
date: 2018-03-13T07:00:00.000Z
categories: product
---

At Repl.it we come to work every day to explore a single idea—what if
programming just worked? What if instead of fiddling around with packages,
configurations, and mismatching versions, you just open your IDE and start
coding. What if developers can go from an idea to coding and shipping software
with no time in between. What if teachers who want to teach programming don't
have to also work as IT administrators. What if students can just code their
homework without having to set up the development environment on every computer
they wanted to code on.

There exists an inverse relationship between developer tool sophistication and
the getting started step. In other words, the more sophisticated our tools are,
the harder it is to set up. Some would go as far as to say that programming is
getting [harder to
learn](http://allendowney.blogspot.com/2018/02/learning-to-program-is-getting-harder.html). Given
that progress in programming and developer tools will continue we have to
actively fight back against the ever-increasing complexity of setting up the dev
environment.

Online coding playgrounds solve part of the problem by getting people to code as
soon as possible. They're pre-setup environments that make a lot of decisions
for you. They make it easy to get started, to learn to code, and maybe even
prototype simple apps. However, up until now, they lacked universality which is
key to computing. In other words, you can only use one language, maybe a few
frameworks but you're often limited by what you can do.

Today, we're changing this. We want the best of both worlds, an IDE that starts
out looking like a playground but can grow with you as soon as you require the
extra power. Here is how the IDE can grow from a simple
Read-Eval-Print-Loop to a full-stack application development environment:

1. Repl.it will always start out as a simple REPL, with a single file editor and
a console. You hit run, a new environment is created, your editor script is
evaluated, and then you can interact with the result in the console.

2. If you want to use files, write to files, split your code into modules, etc.,
you just do that and behinds the scenes the environment will switch to one
where you're interacting with the filesystem. Your code will start to compile
and run as you'd expect it when you run a project.

3. Say you need to use a third-party library, merely find it (through our
widget, or your favorite package registry search), require/import it, and we'll
take care of installing it for you.

4. Say, for example, you were coding in NodeJS, and that package you just
required was
ExpressJS. You use it to listen on a port, any port you'd like; we'll detect that,
host your server/repl on your Repl.it subdomain (forever!) and that's it you're
developing/deploying an application.

Here is a gif of what the entire workflow could look like from interacting with
the repl to deploy a server:

![server](/public/images/blog/server.gif)

We might've buried the lede here but it's worth repeating: __opening a port in the
repl is deploying!__ You can deploy microservices, full-stack applications, or
even a background compute job.

We also know that not all applications will grow incrementally so in typical
Repl.it one-click-start fashion we've pre-setup a Django, Rails, Express, and
Sinatra apps. You can get started on the [languages](/languages) page.

<a target="_blank" href="https://repl.it/languages"><img src="/public/images/blog/rails.png"/></a>

This will also work for other kinds of applications. You can start out by
experimenting in the repl and end up building and training a machine learning
model. As an example, [here](https://repl.it/@Jae_DukDuk/Simple-GAN) is a simple Generative Adversarial Network by
[@Jae_DukDuk](https://repl.it/@Jae_DukDuk) that uses
the MNIST database and scikit-learn python package:

<a target="_blank" href="https://repl.it/@Jae_DukDuk/Simple-GAN"><img src="/public/images/blog/mnist.png"/></a>


## A new computing primitive?

One of the most exciting things about building a platform is watching all the
creative and unexpected ways people use it. Repl.it serverless apps are unique in
that they're stateful and that the same repl, same protocol, same everything,
that you use in development is deployed and running in production.

What we're seeing with some of our users is that they split out their
applications into multiple repls. They might develop their website on one repl
and have another repl be their logs and administrator interface. One of the more
interesting applications we've seen recently is a repl as a client-interface to a chat
application. The 13-year-old [@pylieas](https://repl.it/@pyelias) built a repl that's a client chat
interface to the backend that he made separately (which is becoming the
unofficial chat applications for some of the young Repl.it programmers):

<a target="_blank" href="https://repl.it/@pyelias/Chatroom"><img alt="replit chat client" src="/public/images/blog/chat.png"/></a>

After getting [user-interest](https://repl.it/ibuiltthis/p/working-chatroom) @pyelias is starting to explore building a full
stack application using Django.

We're excited to see where where our users will take this. If you have any
feedback for us, we'd love to [hear](/feedback) it.