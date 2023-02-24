---
title: Native Graphics Love ❤️
author: Luis Héctor Chávez
date: 2021-01-15T23:30:00.000Z
categories: product
---

We have reimagined the native graphics experience on Replit. Our community of educators and hackers have given us [immense feedback on graphics performance and reliability](https://blog.repl.it/fix-gfx).

<figure>
    <video width="720" height="480" controls src="https://blog.repl.it/images/native-graphics-love/doom.m4v"></video>
    <figcaption>Yes, <a href="https://itrunsdoom.tumblr.com/">It Runs DOOM!</a></figcaption>
</figure>

Our engineers have built a native graphics experience that is faster, more reliable, and elegant. Games and other native GUI applications launch quickly and reliably on our platform. Common issues like applications not launching and window resizing have been fixed. Among our most popular use cases is Pygame for beginner game programming and Java Swing for AP CSA students.

## Engineering behind the scenes

Before we take a peek behind the curtain, let's look at a very high-level view ofhow graphics work in practice. Like many Linux systems, Repl.it uses the [X Windows System](https://en.wikibooks.org/wiki/Guide_to_X11/Introduction) to display graphics. The X Windows System is natively a network-ready system: so there is one process that directly interacts with the hardware (the server), which doesn't need to be the on same machine where the program (the client) is being run. Nowadays, the networking capabilities of X are rarely used, since many optimizations rely on the fact that both the server and client processes run on the same machine and are able to share memory between them cheaply, to avoid having to move around massive amounts of graphics data through a narrow networking pipe. In order to support being able to view and interact with graphical user interfaces remotely other techologies are used, like [VNC](https://en.wikipedia.org/wiki/Virtual_Network_Computing). And just for completeness' sake, X is not the only solution for graphics in Linux, and [Wayland](https://wayland.freedesktop.org/) is slowly becoming the alternative of choice for X. Android users will be more familiar with [SurfaceFlinger](https://source.android.com/devices/graphics/surfaceflinger-windowmanager).

With that bit of history and context out of the way, let's look at how the previous solution for graphics was implemented: We relied on running [the regular `Xorg` server](https://en.wikipedia.org/wiki/X.Org_Server) and a magic version of [`x11vnc`](https://github.com/LibVNC/x11vnc) that was able to talk the websocket protocol needed to be displayed from the client-side. This custom version of `x11vnc` was more than a year old and hard to update. Starting up the server in every Repl is too expensive, so we were relying on the [`LD_PRELOAD` trick](https://jvns.ca/blog/2014/11/27/ld-preload-is-super-fun-and-easy/) by hooking invocations to [`XOpenDisplay()`](https://tronche.com/gui/x/xlib/display/opening.html) from `libX11.so`. This works well in _most_ cases, but not every single program that communicates with X uses this library, which causes it to not be ready under some circumstances. Two consequences of using the `LD_PRELOAD` trick: _every single_ process that's started will have an extra bit of code that needs to be loaded beforehand, making processes a few milliseconds slower to launch even if they don't end up using the hooked function; the other consequence is that if any process uses a custom environment (or relies on the `LD_PRELOAD` trick itself), this trick no longer works.

In order to avoid having disembodied windows floating around and not being able to close them, we also need to be running a [Window Manager](https://wiki.archlinux.org/index.php/window_manager). We chose to use [Fluxbox](http://fluxbox.org/) since it's fast and lean. One thing that happened every now and then was that the application startup and Fluxbox launch were running concurrently, so Fluxbox sometimes moved the window around to add the decorations, which caused applications to misbehave (the dreaded `X_SetInputFocus` error!) and prompty crash on first launch.

The solution for the performance issue was to use a more modern, combined X server + VNC server. [TigerVNC](https://tigervnc.org/) was our first choice and we were happy with the improved performance and startup time. This also meant that we had one fewer process to take care of. In order to avoid using the `LD_PRELOAD` trick, we took a page out of [systemd's socket activation](http://0pointer.de/blog/projects/socket-activation.html) feature, so that we detect the intent of a repl wanting to communicate with X by opening the socket to the X server, and launch the server + Window Manager at that point in time.

Finally, the solution for the crashes on launch was significantly simpler: just make sure that Fluxbox has finished initializing so that windows are not moved unintentionally and all the inputs are routed to the correct coordinates.

## Improving the Java Swing experience

As part of this undertaking, we have boosted our Java repls to with more powerful virtual conatiners. Every Teams for Education user will now have 4x the power to compile and run *any* Java project. This was essential to ensure that the Java Swing experience could be quick and reliable for teachers and students. Chromebook users should now see a dramatic improvement for all new Java projects.

Checkout Barb Ericson's AP CS PhotoLab from the [official CollegeBoard lab curriculum](https://secure-media.collegeboard.org/digitalServices/pdf/ap/ap-compscia-picture-lab-student-guide.pdf):

<iframe height="400px" width="100%" src="https://repl.it/@demcrepl/PhotoLab?lite=true" scrolling="no" frameborder="no" allowtransparency="true" allowfullscreen="true" sandbox="allow-forms allow-pointer-lock allow-popups allow-same-origin allow-scripts allow-modals"></iframe>

## Connect with us

We will continue to invest in an improved native graphics experience. Native audio integration is next. Stay tuned! Want to chat about the future of native graphics? Connect directly with [Luis](mailto:luis@repl.it).

If building tools that redefine how people learn to code interests you, [join us](https://repl.it/site/careers).  

## Giving Feedback Goes a Long Way

Teachers continue to express their enthusiasm for multiplayer Repls, annotations, and group projects. We will continue to build on these new platform features to provide a seamless collaborative experience for project based learning.

Are you dreaming of Repl.it features to make you a superhero in your classroom? We want to hear about it! Contact [Derrick McMillen](mailto:derrick@repl.it) directly via email. You can also leave feedback for us [via Canny](https://repl.it/feedback/p/improved-gfx-and-gui).


Learn more about *Teams for Education* in our [documentation](https://docs.repl.it/Teams/).

