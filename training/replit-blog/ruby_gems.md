---
title: Require Ruby Gems
author: Amjad Masad
date: 2018-03-08T08:00:00.000Z
categories: product
---

On the heels of our Node.js npm support [announcement](node_modules), we're pleased to announce that we now
support Ruby [Gems](https://rubygems.org/) too. We're excited to have the Ruby
community join the fun.

The way it works is slightly different from our Node or Python
implementations. In Node or Python you simple require/import the module you'd
like to use, and we'll automagically install the package for you. In Ruby,
unfortunately, we couldn't find a reliable way to map requires to Gems so we had
to go with a neat feature of Bundler:
[bundler/inline](https://gist.github.com/chrisroos/0ddf618ac711abe0f465) where
you can define your gemspec in the code. This works well for Repl.it because
we'd like to make it easy for people to use the repl without having to add files.

Here is an example, this uses the gem `colorlize` to print an ascii drawing of the
American flag:

<iframe height="400px" width="100%" src="https://repl.it/@amasad/Murica?lite=true" scrolling="no" frameborder="no" allowtransparency="true" allowfullscreen="true" sandbox="allow-forms allow-pointer-lock allow-popups allow-same-origin allow-scripts allow-modals"></iframe>

We're still working on improving this, look forward to the following the coming
days:

- Per repl caching: install once, there forever
- Gemfile support

[Feedback](/feedback) welcome!