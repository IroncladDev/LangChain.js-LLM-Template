---
title: Making Repl Identity More Accessible
author: Matt Iselin
categories: eng
cover: https://blog.replit.com/images/rust_cover.png
profiles: mattiselin
date: 2023-01-10T22:00:00Z
---

In August last year, we announced [Repl Identity](https://blog.replit.com/repl-identity), a signed identity for every Repl that your code can use to authenticate other Repls when communicating with your APIs and services.

For a quick refresher, you can try out the [demo](https://replit.com/@mattiselin/repl-identity#main.go) that decodes the identity token and outputs it to the shell.

We have a [Go package](https://github.com/replit/go-replidentity) for this already ([docs here](https://pkg.go.dev/github.com/replit/go-replidentity)), but there's a limited selection of bindings for other languages. To that end, we're rolling out a command-line tool in every Repl that allows you to use features like Repl Identity in any language that can run a subprocess.

Here's a quick demo that you can try in our own Repls:
```shell
$ TOKEN=$($REPLIT_CLI identity create -audience="the target repl id")
$ $REPLIT_CLI identity verify -audience="the target repl id" -token="${TOKEN}" -json
{
  "replid": "ff2d906a-0a47-482b-9067-1ac0a078c394",
  "user": "mattiselin",
  "slug": "replit-cli",
  "aud": "the target repl id"
}
```

Check out this example [Python Repl](https://replit.com/@mattiselin/repl-identity-cli#main.py) that creates and verifies a Repl Identity token:

<iframe frameborder="0" width="100%" height="500px" src="https://replit.com/@mattiselin/repl-identity-cli?embed=true#main.py"></iframe>

You can wrap this command in your code to do token creation and verification without needing a direct language binding.

Enjoy!