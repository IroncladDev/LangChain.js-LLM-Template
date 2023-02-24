{
  "title": "Computers Doing The Right Thing",
  "date": "12/24/2021"
}
---
I'm fascinated by the idea of computers doing The Right thing without explicit user input. Today this is most apparent in autocorrect, but the idea -- in a more advanced form -- goes back to the early days of computing. 

I think if software designers embraced some of the ideas I'm going to talk about here, computers will be much more delightful to use. We won't need endless pages of menus and buttons. And humans can be free to think about their task as opposed to the software that's doing the task. 

## DWIM

Interlisp is one of the most fascinating could-have-been computer systems in history. It shipped with one of the first from-the-ground-up interactive programming environments, structured editor, and many other innovations. Most impressive was the concept of Do What I Mean (DWIM).

![interlisp manual](/public/images/dwim.png)

The most basic DWIM feature is one of spell-correction, but it goes way further than that. It can fix some basic logic errors and even lets the programmer define their own DWIM logic. 

## From correction to intention

DWIM and other contemporary examples (like Google's "did you mean?") are about correcting user errors. A more advanced and fascinating idea is for the computer to detect intention and act on it. Humans do it all the time; we see the intention in other people and act on it. Like for example making way for someone who's walking towards you. 

Software too can and should do basic intention-detection and I'm surprised I don't see it much in the wild. Let's look at examples of how we used it at work. 

## Intent-based development environment

At Replit, we're really passionate about making a simple yet powerful programming environment. The environment needs to be very intuitive for newbies and should be enjoyable for experts. 

![hello world](/public/images/helloworld.png)

The environment always starts with 3-columns, something we've tested and made sure that newbies intuitively get: files, editor, console. That's great, but now **what if you want to do web development?**

You simply write the code, and the environment will open a new pane to show you the output. 

![web dev](/public/images/web.png)

So how does it work? We hook into the Linux Audit system and watch for any new open sockets. In other words, if you start a server we'll assume you want to see the output from it. And in the vast majority of cases, we're right.

Web development is not the only thing people want to do on Replit, many would also like to build games, plot, or boot up old operating systems for fun. In this case, if you wrote the code, or invoked the program that wants to do graphics, we will detect that and stream VNC down to your browser. So how do we do it? Initially, we relied on [LD_PRELOAD](https://jvns.ca/blog/2014/11/27/ld-preload-is-super-fun-and-easy/) which allows you to override arbitrary function calls and inject your own logic. Pretty neat and works for other intent-based functionality. However, we decided to [move away](https://blog.replit.com/native-graphics-love) from that, here is the new approach:

> In order to avoid using the LD_PRELOAD trick, we took a page out of systemd's socket activation feature, so that we detect the intent of a repl wanting to communicate with X by opening the socket to the X server, and launch the server + Window Manager at that point in time.

Finally, much of software development today involves open-source packages. However, package manager can be a bit of pain to use, and honestly they can take out of the flow of coding. So while we do have native UI for package management, we also built a system to detect your intent to install an OSS package and simply do it for you. 

![import](/public/images/import.gif)

## Intent detection is hard but worth it

As you can see intent-detection required system-level knowledge and hacking. At Replit, we're completely obsessed with creating delightful experiences so we go the extra mile to make it happen. But it's worth recognizing that it's not perfect. Sometimes we get it wrong, and the user can get into a pretty messed-up state. 

While complete detection of intent is an [AI-complete problem](https://en.wikipedia.org/wiki/AI-complete), there are a lot of heuristics that we can apply. Including using modern AI techniques. And software can and should get smarter as more people use it. 

I hope this inspires someone to make their software Do The Right Things. 