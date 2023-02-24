---
title: Enter the Shadows with Dark Mode
author: Barron Webster
date: 2021-10-5
cover: https://blog.repl.it/images/dark_mode/dark_mode_cover.png
categories: design
---

***Looking for how to change your Replit theme? Click [here](https://blog.replit.com/themehowto).***

It's spooky season, so we have a spooky feature for you: Dark Mode™ is now available for everyone on Replit! 

Just open your sidebar and click the moon to enter the shadow realm. Click the sun to switch back.

![Dark Theme](images/dark_mode/theme_switching.gif) 

Dark theme will work across the app — from the homepage,

![Dark Homescreen](images/dark_mode/dark_homescreen.png)

to the workspace:

![Dark Workspace](images/dark_mode/dark_workspace.png)

to the rest of the site.


### Where we're going
This update has been enabled by a lot of work we're doing on Replit's design system. [Tyler](https://twitter.com/tylerangert), [Alex](https://twitter.com/alex_frantic), Ashlynn & I have restructured & simplified how we use css variables. And we've been building out reusable components and visual utilities that can render across themes. 

This infrastructural work makes it a lot easier to do some really useful and cool things with our interface. Dark mode is a good first step — avoiding being blinded in the middle of the night. In the future, it will enable us to do things like have custom themes — personal themes, themes for a team or class, etc.

It also means it'll be much easier to make sure our UI is accessible. Our refactored color tokens have higher foreground/background contrast across the board. And by building accessibility best practices into our components, it means engineers get them for free when they take components off the shelf. It also makes high-contrast themes, or themes for colorblind users, will be much easier for us to make.


