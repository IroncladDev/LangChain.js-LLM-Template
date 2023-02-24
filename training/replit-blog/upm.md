---
title: Open-Sourcing the Universal Package Manager
author: Radon Rosborough
date: 2019-10-30T00:00:00.000Z
categories: product
---

<img src="/images/upm_cover_small.png" alt="universal package manager"/>

On Repl.it, working with packages is made easy. You can simply type `import flask` in your Python code, and [Flask](https://palletsprojects.com/p/flask/) will automatically be installed for you. Or, if you’re more the browsing type, you can search for packages and install them through a graphical interface.

In Repl.it tradition, once you know how to do package management in one language, you know how to do it in every language. You can use the same interface to install packages in Node.js, simply type `require(“express”)` to get [Express](https://expressjs.com/) up and running and so on.

<div style='position:relative; padding-bottom:calc(64.48% + 44px)'><iframe src='https://gfycat.com/ifr/SecondFarawayBird?hd=1&speed=1.5' frameborder='0' scrolling='no' width='100%' height='100%' style='position:absolute;top:0;left:0;' allowfullscreen></iframe></div>

Today we’re excited to release several months of work on improving the package management experience. Here are the highlights:

* **Reproducible package management.** We’ll still look at your code and install packages automatically, but now we’ll remember exactly which versions to use, so your code will keep working no matter how many package updates are published.
* **Modern tooling and best practices.** We now use the modern dependency manager [Poetry](https://poetry.eustace.io/) to manage your Python packages. Poetry improves on Pip in its security, consistency, usability, and flexibility. We believe tools like Poetry are the future, and we are migrating to them to do our part in improving the ecosystem for developers everywhere.
* **Giving back to the community.** The core of our language-agnostic package management is now [open-source on GitHub](https://github.com/replit/upm). UPM, the Universal Package Manager, is a manager for your package managers: it knows all of their features, best practices, and quirks so that you don’t have to. UPM provides a unified set of abstractions (adding, removing, and listing project packages, searching for packages online, and guessing what packages need to be installed for your project to run) and a consistent, scriptable command-line interface that you can use to manage packages for every language the same way, just like we do on Repl.it. If you want to get your favorite package manager on Repl.it, all you need to do is submit a pull request to UPM. Supporting a new language now only takes about 300 lines of code!
* **More language support.** Splitting out package management into a project which abstracts over language-specific differences makes adding package management to more languages much easier. In fact, we’ve already received a contribution from the [DartLang](https://dart.dev/) team, and also [added](https://github.com/replit/upm/commit/e5b9ee58afc1044bcfbeda3a9f4f00ce40d475fc) package management to [Emacs Lisp](https://repl.it/site/blog/elisp) – check it out [here](https://repl.it/l/elisp)! 

You can take out UPM on your computer. Check out the [Installation](https://github.com/replit/upm#installation) section on GitHub for full instructions for your system. 

Here is a quick demo of the CLI on Repl.it. (You can open a shell in the workspace with `ctrl-shift-s` on mac `command-shift-s`).

<div style='position:relative; padding-bottom:calc(41.51% + 44px)'><iframe src='https://gfycat.com/ifr/WigglyKeyBubblefish?hd=1&speed=1.5' frameborder='0' scrolling='no' width='100%' height='100%' style='position:absolute;top:0;left:0;' allowfullscreen></iframe></div>

Let’s dive into some of the technical aspects of UPM and Repl.it’s new package management.

## Different kinds of package managers

There’s more than one kind of package manager. Broadly speaking, I like to define two categories: *system* package managers, and *project* package managers.

System package managers:
* include [Homebrew](https://brew.sh/), [APT](https://en.wikipedia.org/wiki/APT_%28Package_Manager%29), [RPM](https://rpm.org/), [Pacman](https://wiki.archlinux.org/index.php/pacman), and [Chocolatey](https://chocolatey.org/).
* generally install only the latest versions of all software.
* install software globally, for everyone (or in some cases for a single user).
* often have guarantees by package repository maintainers that the software they install will work together.
* can install anything that’s packaged, regardless of the language it’s written in.

Project package managers:
* include [Pipenv](https://github.com/pypa/pipenv), [Poetry](https://poetry.eustace.io/), [NPM](https://www.npmjs.com/get-npm), [Yarn](https://yarnpkg.com/en/), [Bundler](https://bundler.io/), [Stack](https://docs.haskellstack.org/en/stable/README/), and [Cask](https://cask.readthedocs.io/en/latest/).
* can generally install any versions of available packages, and generally include dependency resolution algorithms that can compute solutions to a large set of package version constraints.
* install packages into an isolated environment for every project, so that they aren’t available (and can’t conflict) globally.
* usually don’t have any guarantee about the quality, compatibility, or even safety of the packages that are installed.
* are almost always limited to one specific language.

In other words, system package managers are meant to administrate your system and install the tools that you use everywhere on your machine, whereas project package managers are meant to help develop and package new software. These are very different use cases, and so the resulting package managers are very different.

You might ask, what about tools like [Pip](https://pypi.org/project/pip/), [RubyGems](https://rubygems.org/pages/download), and [cabal-install](http://hackage.haskell.org/package/cabal-install)? These tools occupy a middle ground: by default, they install packages globally (making them unsuitable for project package management); yet they are also limited to a specific programming language (making them also unsuitable for system package management). As package management ecosystems evolved, using these tools directly is no longer recommended; rather, for system package management you should use a system package manager which packages the software you want to install globally, and for project package management you should use a tool which wraps Pip (e.g. Pipenv or Poetry), RubyGems (Bundler), or cabal-install (Stack) to provide isolation and reproducibility.

## How should project package managers behave?

<div style='position:relative; padding-bottom:calc(80.14% + 44px)'><iframe src='https://gfycat.com/ifr/ThatAthleticIsopod?hd=1&speed=1.5' frameborder='0' scrolling='no' width='100%' height='100%' style='position:absolute;top:0;left:0;' allowfullscreen></iframe></div><p>

Here’s how we visualize project package management as working in an ideal world: *source → specfile → lockfile → installed packages*. Let’s break that down in detail:

* The *source* code is what really defines a project's dependencies. Although often imprecise and implicit through importing and usage of packages, when possible the source should be used as a basis. For example `upm add --guess` will add any packages it think are being used to the specfile.
* The *specfile* describes project dependencies in a human-and-machine-readable format. For example, your specfile might say: “This is a Python project. It needs [Flask](https://pypi.org/project/Flask/) (at least version 1.1, but not 2.0 or anything later) as well as [Selenium](https://pypi.org/project/selenium/) (any version) to run.” For [Poetry](https://poetry.eustace.io/), this file is called `pyproject.toml`. Typically you edit the specfile either by hand or by using a command-line interface (or both). For example, you could create the specfile I described above by running `poetry add “flask ^1.1” “selenium *”`.
* The *lockfile* is a file that describes project dependencies *exactly*, in a machine-readable format. This means that it includes *transitive dependencies* (dependencies of your dependencies), and it has exact versions for every package, rather than the version *constraints* (at least 1.1, less than 2.0) that are found in the specfile. The lockfile is automatically generated from the specfile by the project package manager via *dependency resolution*. Why is it important? If you have a lockfile, then it ensures that every developer working on your library or application will use exactly the same versions of its dependencies. This is very important for reproducibility! Typically, lockfiles also include some checksums or hashes to improve security (if someone has replaced a dependency on PyPI with malware, then the build will fail). For Poetry, the lockfile is called `poetry.lock`.
* The *packages* are installed based on what is listed in the lockfile. Typically, they will be installed into an isolated per-project directory (like `node_modules` or a Python virtualenv).

This one-directional information flow from source to specfile to lockfile to installed packages neatly separates the different functions of a project package manager. Each stage having less human involvement than the last.

## How do project package managers actually behave?

Not well, it turns out. While building the package management infrastructure at Repl.it, we discovered a laundry list of language-specific limitations, quirks, and design mistakes. This is what inspired us to create UPM: we want to make package management as easy as it should be.

Here are some of our favorite quirks:
* Bundler, despite using a project-local specfile and lockfile, installs dependencies *system-globally* by default. You can configure this, but there’s no standard project-local location to use.
* When you run `pip search Flask`, the package named `Flask` does not appear in the search results. As of yet, I’ve been unable to determine why. Also, you can’t compare Python package names using string equality because they are case insensitive and hyphens and underscores are equivalent. (But nonetheless there *is* a canonical format for each package name, which cannot be determined without network access and which is used in some contexts but not others.)
* The lockfile format used by Yarn is *almost* YAML, but not quite. [Yes, really.](https://github.com/yarnpkg/yarn/issues/5629)
* The command-line option to make Bundler produce machine-parseable output is “documented” only by virtue of existing in the source code. Reading Bundler specfiles and lockfiles from an external tool is also only possible by threading together a bunch of internal functions from the Bundler source code.
* There’s no reasonable way in Poetry to discover where dependencies are going to be installed. You have to either create a virtual environment and then ask where the Python binary was installed, or manually reimplement the algorithm, which includes checking environment variables, reading two different configuration variables, parsing an optional TOML file, looking up the Python version, and lowercasing the project name.
* Given a Python import, the best way to determine which package provides it is apparently to look it up in a big list that is generated by [people manually adding packages one at a time](https://github.com/bndr/pipreqs/commits/master/pipreqs/mapping).
* For some packages, the NPM Registry API returns a URL for the package homepage in search results but *not* when you look up details for the package individually.
* The standard Emacs package manager has literally no support for installing anything but the latest version of a package.

If you use UPM, you don’t have to worry about any of this!

## UPM abstractions

The basic principle of UPM is to define [a sensible internal API](https://github.com/replit/upm/blob/c81fda15dfb2cda4cf345911a2c369ed060dde0c/internal/api/types.go#L116-L309) which can be implemented for each language, and then define the user-facing command-line interface in terms of this API. This way, all of the business logic of UPM is guaranteed to be language-independent.

Some parts of the API are simple constants: the names of the specfile and lockfile, and what filenames correspond to the language. These are used for project language autodetection. Other parts implement the core UPM operations: add or remove packages, list the specfile or lockfile, search project source code for possible dependencies to install. In addition to guaranteeing language-independence, this API/CLI split makes it easier to implement language backends. For example, ‘upm add flask’ will first list the specfile and filter out Flask if it’s already been added. This means the implementation of `LanguageBackend.Add` for the Python backend of UPM can just invoke `poetry add`, without needing to worry about the fact that Poetry throws an error if you try to add the same package twice.

One of the main challenges in designing UPM’s language backend API was the fact that different package managers act quite differently. In an ideal world, each package manager would implement three separate operations: add to or remove from the specfile, generate the lockfile from the specfile, and install packages from the lockfile. In reality, some package managers force you to do two or even three steps at once. In UPM, we deal with this by having each language backend declare a set of “quirks”, like `AddRemoveAlsoLocks` and `LockAlsoInstalls`. The implementation of `upm add` will run the `Add` backend method, and will then follow it up with the `Lock` backend method *unless* `AddRemoveAlsoLocks` is included in the backend’s quirks configuration (indicating that the lockfile was already generated in addition to the specfile being modified).

Even worse than some package managers combining steps, some package managers don’t have any concept of a lockfile at all! For example, the standard package manager for Emacs Lisp ([`package.el`](https://wikemacs.org/wiki/Package.el), wrapped by [Cask](https://cask.readthedocs.io/en/latest/)) has no support at all for installing a specific version of a package, so the idea of a lockfile is really a non-starter. (Aside: this annoyed me so much that I wrote [my own package manager for Emacs](https://github.com/raxod502/straight.el), which was part of the reason I got hired to improve the package management infrastructure at Repl.it!)

The approach of UPM to this problem is to preserve the spirit of the specfile/lockfile abstraction as much as possible. For Emacs Lisp, UPM will install directly from the specfile, then generate a lockfile from what is installed (listing exact versions and transitive dependencies, of course).

## Caching and dependency guessing

At Repl.it, we care about performance, because nobody wants to wait for their code to run. That means our package management needs to be as fast as possible, especially when there isn’t actually anything that needs to be installed. Since we want UPM to be as useful a standalone tool as possible, we opted to implement all of the performance optimizations directly in UPM. All of the package management code in Repl.it is essentially just a wrapper around UPM:

* when you add a package through the interface, Repl.it calls `upm add`
* when you remove a package through the interface, Repl.it calls `upm remove`
* when you run your code, Repl.it calls `upm add --guess` (which searches your code for `import` or `require` statements and installs any missing packages)

You might ask how it isn’t incredibly slow to do a code search on every run. (Not to mention making sure the lockfile and installed packages are up to date, since you’re allowed to edit the specfile directly at any time if you want to!)

The answer is that UPM transparently keeps track of some information in a hidden JSON file behind the scenes. It looks something like this:

```json
{
  "version": 2,
  "languages": {
    "python-python3-poetry": {
      "specfileHash": "361e6bddc6a34f1696e71227be88b4b4",
      "lockfileHash": "f208ad0efc93d51f52e04326406816cf",
      "guessedImports": [
        "Flask",
        "selenium"
      ],
      "guessedImportsHash": "8952e87cf73e21ef3313c4e9c98718a7"
    }
  }
}
```

After a successful operation, UPM will automatically record [hashes](https://en.wikipedia.org/wiki/Hash_function) of the specfile and lockfile. That way, it can tell if the specfile has changed since the last time the lockfile was generated. If it hasn’t, then `upm lock` is a very fast no-op. Similarly, if the lockfile hasn’t been changed since the last time packages were installed, then `upm install` can be optimized away.

UPM also optimizes dependency guessing by means of a two-step search. First, it uses a fast [regexp](https://en.wikipedia.org/wiki/Regular_expression) match to heuristically find things that **might** be `import` or `require` statements. Then it converts the deterministically generated sequence of matches into a hash. If this hash matches what was recorded in the JSON file last time a search was done, then the list of guessed packages from last time (also in the JSON file) can be reused. This is very fast. Otherwise, the language backend is asked to do a more advanced search, usually involving [AST](https://en.wikipedia.org/wiki/Abstract_syntax_tree) parsing.

## Closing

We hope you enjoy faster, more modern, and more open package management support on Repl.it. Now that we’ve aggregated all of the language-specific code into a single place, we hope it will be much easier to add package management support for new languages, like [Emacs Lisp](https://repl.it/l/elisp). Check out [UPM on GitHub](https://github.com/replit/upm) and see what it would take to add your favorite package manager to Repl.it! (Or, if Repl.it doesn’t have your favorite programming language yet, check out our other open-source projects, [Polygott](https://github.com/replit/polygott) and [Prybar](https://github.com/replit/prybar), to help us add it.)
