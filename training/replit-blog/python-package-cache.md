---
title: Introducing the Python package cache
author: Luis Héctor Chávez
date: 2021-03-19T19:45:00.000Z
categories: infra
---

Figuring out how to install third-party libraries can derail people from learning to code or starting a new side project. We built the [Universal Package Manager](https://blog.replit.com/upm) (UPM for short) to save people from having to think about package installation at all. Just import the library, press run, and UPM will install it into your repl!

Every time you run a repl or a repl wakes up, UPM checks to see if it needs to download and install any dependencies. This is handy (no matter what's gone inside your repl, it will always have the dependencies it needs) but slow: UPM needs to download typically tens of megabytes worth of packages, extract them on the local filesystem, and sometimes also pre-compile them for better runtime performance.

Or at least it used to be slow until yesterday when we enabled the Python package cache, so now the most popular Python packages are pre-populated in pip's cache (`/home/runner/.cache/pip`), so the download step is going to be mostly gone for the _vast_ majority of Python repls! It also uses pre-built wheels as much as possible to avoid even having to pre-compile code.

## How does it work?

We had two goals in mind when we started designing this:

1. it should be as transparent as possible, which meant that users would still be able to add packages to the local cache while avoiding copying files around (which would have defeated the purpose of using a cache in the first place), and
2. each repl's cache should be independent of each other, to prevent cross-repl cache attacks (pollution, poisoning, etc.).

To achieve both goals, we are using the same technique that Docker uses to be able to share files between images: the [Overlay Filesystem](https://www.kernel.org/doc/html/latest/filesystems/overlayfs.html). On each machine that [runs repls](https://blog.replit.com/killing-containers-at-scale#replit-architecture), we have a read-only snapshot of the contents of the cache after installing the most popular packages. The snapshot is read-only bind-mounted into each repl into `/mnt/cacache`. We then perform an Overlay-mount into the directory where the cache expects it to be (`/home/runner/.cache/pip`), using `/mnt/cacache/pip` as the "lower" directory and  `/mnt/scratch/cacache_pip/upper` (a user-writable directory) as the "upper" directory. This means that the shared files cannot be modified, and each repl has a [copy-on-write](https://en.wikipedia.org/wiki/Copy-on-write) view of the cache.

In order to keep the cache contents fresh, we gather stats about packages being downloaded from [PyPI](https://pypi.org/), and every week we'll rebuild the cache with the list of most popular pip packages.

Thanks to this, the average time to install packages has gone down ~40% across all [Always On](https://blog.replit.com/alwayson) repls.

![Always-on package time-to-install](https://blog.replit.com/images/python-package-cache/packages-time-to-install.png "The cardinal sin of data visualization: unmarked axes")

### "cacache"?

The name is derived from [**C**ontent-**A**ddressable storage](https://en.wikipedia.org/wiki/Content-addressable_storage) (plus "cache"). One of the properties that is needed for all this to work is that when a package is installed into the system, it is placed in a stable location in the filesystem that depends on the _contents_ of the package (typically the hash of the contents). Every time a package is going to be installed, the package installer (`pip` in the case of Python) asks the package server for the metadata about the package, which includes the hash of the package. This hash is used to find whether the file is already in the cache, and the local copy is used instead of downloading a new one. Furthermore, since the hash of the contents of the package is already available, the contents can be checked for integrity by comparing the hash of the local copy with the expected one!

[pip](https://pip.pypa.io/en/stable/) (for Python), [npm](https://www.npmjs.com/) (for Node.js), and [Maven](https://maven.apache.org/) (for Java) all use content-addressable caches.

## What's next?

We're going to give the same treatment to Java (Maven packages) and JavaScript (npm packages) repls in the next couple of weeks to complete the three most popular languages. Plus a mysterious "language" that will be unveiled soon.

Happy (Python) repling!