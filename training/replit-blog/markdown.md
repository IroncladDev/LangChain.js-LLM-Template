---
title: Previewing Markdown in Repls
author: Tim Chen
date: 2019-08-02T00:42:33.000Z
categories: product
---

When our community members want to provide instructions within a repl,
the most common pattern we've seen is in a `.txt` file, or as a code
comment. Users quickly figured out that while they could make markdown
files, there was no way to render it in a more readable format. Today,
that changes. We're happy to announce that you can now preview markdown
in repls!

# How to get Markdown Previews

It's really simple to use - simply create a markdown file (a file with an
`.md` extension) and viola - you'll see a button to edit and preview in
the top right corner of the editor.

Feel free to edit your markdown file, and toggle back and forth between
preview mode and edit mode as much as you like!

![markdown preview](https://blog-images.amasad.repl.co/markdown-preview.gif)

Opening a markdown file will show the preview by default, so you can use
this as a README for your repl, or to provide special instructions.

# Features

Aside from being able to preview markdown, we also support full syntax
highlighting for code blocks. It will be highlighted in the same theme
as the editor itself.

You can also copy code blocks by clicking on the copy icon in the
top-right corner of code blocks.

We have ideas for more features, but we'd also like to hear from you.
Read on for more!

# Next Steps

Right now, markdown previews are only supported on Monaco, which we use
for non-mobile platforms. Mobile support is coming soon.

Since it's built right into the editor, we have ambitious ideas for how
it can be better integrated with the rest of the Repl.it experience.
One such example of a feature we want to see is the ability to import
a code block directly into a file. This would be especially helpful for
using markdown as tutorial instructions.

We'd also like for files named `README.md` to be the default selected
file, if it exists, so users landing on your repl will see your README
first.

Got more ideas for us? We'd love to hear them over on our
[feedback channels](/feedback)!
