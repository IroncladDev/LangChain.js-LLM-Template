---
title: Replit Mobile App
author: Laima Tazmin, Abdel Rahman Elleithy, Matthew Chen, Ian Kirkpatrick
date: 2022-10-19T08:00:00.000Z
cover: https://blog.repl.it/images/mobile-app/mobile-banner.jpg
categories: news,eng,product
---
![mobile art](https://blog.replit.com/images/mobileart.jpg)

<div style="display: flex; justify-content: center;">
  <a class="cta-btn" href="https://replit.com/mobile" target="_blank"
    style="display: flex;
    flex-direction: row;
    color: #fff;
    background-color: #0079F2;
    padding: 12px 18px;
    width: fit-content;
    border-radius: 8px;
    justify-content: center;
    align-items: center;
    transition-duration: 0.1s;
    text-decoration: none;
    font-size: 1.1em;">Download the App</a>
</div>


Introducing the Replit mobile app for [Android](https://play.google.com/store/apps/details?id=com.replit.app) and [iOS](https://apps.apple.com/us/app/replit-code-anything/id1614022293).

Today, we’re excited to announce the launch of the Replit mobile app. With the mobile app, you can code anything, anywhere. Build more, type less.

<style>
  .video-container {
  position: relative;
  padding-bottom: 56.25%;
}

.video-container iframe {
  position: absolute;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
}
</style>
<div class="video-container"><iframe src="https://www.youtube.com/embed/Cmq3TrS3ccU" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe></div>

Use the app to write a Python bot, build and launch your personal website, or run any program you can imagine with the [power of Nix](https://blog.replit.com/powered-by-nix), which gives access to millions of open-source packages. With Replit, you instantly have a powerful computer in your pocket.

We're on a mission to turn smartphones from devices optimized for consumption into powerful creative tools.

Before we had a dedicated app, we saw increasing global mobile usage of our browser-based code editor. Last year, [we invested in making the mobile web IDE](https://blog.replit.com/mobile-v2) more reliable and performant. Our users noticed - it doubled our retention. Today, nearly 20% of Replit's users build on their mobile devices.

Yet we heard again and again from our community that they wanted a native mobile app. Building natively would allow us to expand into device-specific capabilities, work better and faster in spotty network conditions around the world, and push the limits of interaction design.

Unlike other types of mobile creation apps, you can create anything with code on Replit. With phones, we can empower billions of people to build, learn, and earn from software creation.

## Features

We focused the new Replit mobile app on creation with an all-new code editing experience.

When you open the app, we take you straight into your current projects, or Repls. In the second tab, **Create**, you’ll find a rich world of languages and starter templates to kick off your next coding project. 

Our ultimate goal: help you build more and type less. 

Here are some of the ways we’re making coding on mobile devices easier: 

### Navigate with the coding joystick

<video width="375" height="auto" class="css-3qjkrt" autoplay muted playsinline loop controls src="https://blog.repl.it/images/mobile-app/joystick_demo.mp4">
Sorry, your browser doesn’t support HTML5 media.
</video>

On your phone, it can be frustrating to move the cursor and select text, let alone code. We’ve built a native control interface that lets you navigate code faster. It's called the joystick.  

Drag the joystick up & down to move through code quickly. Swipe left & right (or tap the arrows on each side) to nudge the cursor exactly where you need it.

Even better, tap the joystick to select the current token, tap again to select a whole line, then tap again to expand further.

### Edit with smart suggestions and common actions

<video width="375" height="auto" class="css-3qjkrt" autoplay muted playsinline loop controls src="https://blog.repl.it/images/mobile-app/suggestions_demo.mp4?x=1">
Sorry, your browser doesn’t support HTML5 media.
</video>

Auto-completion is critical to coding. For the mobile app, we built a local-first auto-completion engine that is super fast, with a library of language-specific snippets tucked behind the keyboard. We currently support Python, HTML, CSS, JS, and Typescript, with more to come.

The coding keyboard toolbar also offers common actions, like undo & redo, indent, and toggle comment. Plus, we've added a clipboard manager for copy & pasting code between repls.

### Turn ideas into code with Ghostwriter

<video width="375" height="auto" class="css-3qjkrt" autoplay muted playsinline loop controls src="https://blog.repl.it/images/mobile-app/ghostwriter_demo.mp4?x=1">
Sorry, your browser doesn’t support HTML5 media.
</video>

We announced [Ghostwriter](https://blog.replit.com/ai), your personal AI pair programmer, a few months ago. It's available on the Replit mobile app to early testers with a full launch coming later this month.

### Make the workspace yours

<video width="375" height="auto" class="css-3qjkrt" autoplay muted playsinline loop controls src="https://blog.repl.it/images/mobile-app/tabs_demo.mp4">
Sorry, your browser doesn’t support HTML5 media.
</video>

We recently [announced tabs on desktop](https://blog.replit.com/tabs). The same flexible system powers tabs on mobile too! 

Open multiple files at once, switch between them easily, and access more tools without losing your place in code.

## Challenges

While building, we faced hard but interesting challenges at the core of interaction design. 

How do we keep the user interface simple, elegant & performant, while surfacing the flexible & powerful capabilities of Replit? 

How do we use screen space judiciously, and handle cross-platform differences with ease?

### Behind smart suggestions

One area we paid special attention to is how we architect and surface auto-completion.

Coding is hard on a mobile phone. Typing variable names, for example, is tricky on a mobile keyboard. The Replit app comes to the rescue by parsing your code and using it to generate suggestions.

To be useful, that parsing has to keep up with every keystroke. That's not easy - people type fast! That means we need to do the parsing right on your device, rather than consult a remote server. The Replit app uses the [Lezer Parser System](https://lezer.codemirror.net) from CodeMirror to do snappy incremental parsing in milliseconds. This lets us offer a smart keyboard that will grow increasingly helpful with time.

In some cases, we produce many suggestions, so we have a scoring system to ensure that we feature the most useful and frequently-used suggestions.

If you type the letter "i" in your Python Repl, you might be offered these auto-completion suggestions:

* An `import` snippet that helps you fill in the module to import.
* `if`, `if...else`, or `if...elif...else` snippets. These snippets include syntax, smart whitespace, etc.
* `index`, a variable you've defined elsewhere that is in scope.

We offer a wide variety of suggestions that reflect the language or file format of your file and your content.

## What’s next

If you’re familiar with Replit on web, you’ll notice that the app doesn’t have the same community features. Over the coming months, we’ll be rolling out more social and collaboration features, designed with mobile experiences and creation in mind.

We've only just scratched the surface on the core editing features we envisioned for the app. We’ll continue to ship improvements in code navigation and smart suggestions.

By this time next year, the Replit app will be even more powerful, fast, and educational. It will inspire you to create even more with ease. Join now and become a part of the journey.

<div style="display: flex; justify-content: center;">
  <a class="cta-btn" href="https://replit.com/mobile" target="_blank"
    style="display: flex;
    flex-direction: row;
    color: #fff;
    background-color: #0079F2;
    padding: 12px 18px;
    width: fit-content;
    border-radius: 8px;
    justify-content: center;
    align-items: center;
    transition-duration: 0.1s;
    text-decoration: none;
    font-size: 1.1em;">Download the App</a>
</div>


Does the idea of bringing creation to the world excite you? [Apply to join the team](https://jobs.ashbyhq.com/replit/edec839f-d21d-4581-bd47-64ba6e06698b)!


<script>
  window.addEventListener('load', videoScroll);
window.addEventListener('scroll', videoScroll);

function videoScroll() {

  if ( document.querySelectorAll('video[autoplay]').length > 0) {
    var windowHeight = window.innerHeight,
        videoEl = document.querySelectorAll('video[autoplay]');

    for (var i = 0; i < videoEl.length; i++) {

      var thisVideoEl = videoEl[i],
          videoHeight = thisVideoEl.clientHeight,
          videoClientRect = thisVideoEl.getBoundingClientRect().top;

      if ( videoClientRect <= ( (windowHeight) - (videoHeight*.5) ) && videoClientRect >= ( 0 - ( videoHeight*.5 ) ) ) {
        thisVideoEl.play();
      } else {
        thisVideoEl.pause();
      }

    }
  }

}
</script>