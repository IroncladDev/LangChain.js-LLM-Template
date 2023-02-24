---
title: Understanding Repl Resource Utilization
author: Lincoln Bergeson
categories: eng
date: 2022-1-31T20:00:00Z
cover: https://blog.replit.com/images/rust_cover.png
---

Every computer on earth needs these three essential resources in some form:

1. Processor
2. Memory
3. Storage

The computers we provide for Replit users, or Repls, have access to a virtual CPU, an allocation of RAM, and a virtualized filesystem.

It’s important to understand resource utilization within the context of the software that you’re writing. To this end, we have started rolling out a new component in the file tree to make this more transparent and visible to all of our users.

<div class="max-width-75">

![example of the repl resource component in action](https://blog.replit.com/images/repl-resources.png)

</div>

This component can help you figure out why your repl is running slowly or otherwise misbehaving.

But what do the numbers actually mean?

## CPU

There are many different types of processors, including GPUs, TPUs, microcontrollers, and more. These are specialized devices that serve distinct purposes, such as displaying graphics, machine learning, and powering smart devices.

In addition to any other processors they may have, all modern personal computers have a CPU, or central processing unit. The CPU is responsible for executing instructions and running programs. In a sense, it is the brain of the computer.

Today, repls run on Google Cloud Platform and use Intel-compatible CPUs. For security and economic reasons, we don't give users access to the entire CPU. Instead, we host repls inside sandboxed Linux containers running on virtual machines that partition the CPU into virtual CPUs, or vCPUs.

### What does it mean to "use" the CPU?

The CPU operates by executing machine instructions via the [fetch-execute cycle](https://en.wikipedia.org/wiki/Instruction_cycle).

Modern computers are highly complex and typically need to run more than one program at a time. To accomplish this, the computer runs an operating system which has exclusive control over how all of the applications on a computer share the CPU. The code within the OS that is responsible for allocating CPU time to user applications is known as the [process scheduler](https://en.wikipedia.org/wiki/Completely_Fair_Scheduler).

The details of process scheduling are complex, but the beauty of an operating system is that a user, you don't need to know how it all works under the hood. All you need to know to get started is that the program you're trying to run will get its fair share of the underlying processor, just like everyone else.

### Ok, so what's CPU "utilization"?

Linux tracks the total CPU time used by the entire system in nanoseconds in a file in the [sysfs pseudo-filesystem](https://en.wikipedia.org/wiki/Sysfs). Try reading this file in a shell with `cat /sys/fs/cgroup/cpu/cpuacct.usage`.

The calculation for utilization simply takes the difference in time spent executing instructions by the CPU, or CPU time, over a given interval and divides it by the actual time that passed, or wall time, over that same interval.

You also need to divide this number by the CPU cores that are available on the system. This way, you won't have percentages over 100%, and if your CPU utilization is at 100%, it reflects your intuition that the system is as busy as it can possibly be.

In addition to the resource monitoring component in the file tree, you can run programs such as `top`, `htop`, `mpstat`, and `sar`, all of which you can install in a Nix repl.

### How many CPU cores do I get on Replit?

Free plans get 0.5 vCPUs allocated to their Repls. Hacker repls get 2 vCPUs, and Boosted repls are allocated 4 vCPUs.

If you find yourself running up against resource limits frequently as a free user, consider [purchasing Cycles](https://replit.com/cycles) and adding a Boost to your Repl for 8x more CPU to work with. If you're ready for Hacker, [subscribing to Hacker](https://replit.com/pricing) will instantly upgrade all your programs to have 4x as much CPU and you'll have 5 Boosts to add to any Repl.

## RAM

RAM stands for Random Access Memory.

In the old days, you might have used a clunky device such as a [magnetic drum](https://en.wikipedia.org/wiki/Drum_memory), and it would have to literally spin a metal cylinder around in order to access a memory location. Today, we use lightweight sticks of [DRAM](https://en.wikipedia.org/wiki/Dynamic_random-access_memory), or Dynamic RAM, that can read or write to any memory location instantly with a tiny electronic signal.

Memory is used to store any values that a program needs access to at runtime. For example, a file that is currently open in a text editor is stored in memory.

Here are some more examples:
- This website is being stored in your computer's RAM right now
- If you're playing music, it is buffering through your system's memory
- Any currently running programs have access to RAM to store whatever they need

RAM is a lot easier to understand than CPU. To put it simply, the more programs you run, the more RAM your system will need. However, some programs (*cough* [Google Chrome](https://c.tenor.com/ma0A_HhmKhEAAAAM/chrome-ram.gif) *cough*) use more memory than others. Unfortunately as a user, you have limited control over how much memory your applications use.

### How much memory do I get on Replit?

All free repls are allocated 1 GiB of memory. Hacker repls have 2 GB by default, and 4 GB when boosted.

If you try to use more memory than you have available, the application using too much memory will be terminated. You can test this by running the following program in a C repl:

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  for (int i = 0; i < 1000000; i++) {
    malloc(1024 * 1024);
  }
  return 0;
}
```

This is a simple loop that tries to allocate a large amount of memory. If you run this, you'll see output such as the following:

    $ ./main
    signal: killed

The new resource monitoring component will help you see how much memory your repl is using. The free tier of 1 GB is enough for most basic programs, but power users may want to consider [purchasing Cycles](https://replit.com/cycles) for Boosts or [upgrading to Hacker](https://replit.com/pricing) to run into these resource limits less frequently.

## Storage

Storage is the easiest resource to understand. Each repl gets a 1 GB filesystem on an SSD, or Solid State Drive. SSDs are becoming the default in nearly all laptops and personal computers because they are so much faster than traditional hard drives, or HDDs.

You can view how much total storage you're using in the new resource monitoring component. You can also type the command `du -sh ~/$REPL_SLUG` in the shell of any repl and see how much space your files are taking up.

To see how much space an individual file may be using, you can use the `ls` command. Navigate to any folder with `cd`, and type `ls -lh` in the shell:

    $ ls -lh
    total 152K
    -rw-r--r-- 1 runner runner 132K Apr 12  2021 db.sqlite3
    -rw-r--r-- 1 runner runner  647 Jan 27  2020 manage.py
    drwxr-xr-x 1 runner runner  108 Apr 12  2021 mysite
    -rw-r--r-- 1 runner runner 2.1K Jan 14  2021 poetry.lock
    drwxr-xr-x 1 runner runner   46 Jan 27  2020 __pycache__
    -rw-r--r-- 1 runner runner  294 Jan 14  2021 pyproject.toml
    -rw-r--r-- 1 runner runner 1.3K Apr 12  2021 README.md
    -rw-r--r-- 1 runner runner    7 Jan 27  2020 requirements.txt
    drwxr-xr-x 1 runner runner   20 Apr 12  2021 templates
    drwxr-xr-x 1 runner runner  158 Apr 12  2021 todo

You can see that db.sqlite3 is taking up 132 KB of space, manage.py is using 647 bytes, the folder as a whole is using 152 KB, and so on.

Due to some limitations in our platform, we are unable to provide more than 1 GB of storage in any repl. We are actively working on improvements that will allow us to give users arbitrarily large filesystems to work with.

If you're running out of storage space in your repl, you can delete some files or use an external storage provider such as [GCS](https://cloud.google.com/storage).

## Conclusion

If you made it the end of this post, congratulations! You are well on your way to understanding how the system works under the hood.

We're always trying to find ways to give people as many resources as possible, for as inexpensively as possible. In one sense, allocating resources to users in an efficient and accessible way is the core problem we are solving as a company.

The new resource utilization component gives users a better window into how their repl is operating under the hood. There's so much more work like this to do -- if this post interested you, [consider joining us](https://replit.com/site/careers)!