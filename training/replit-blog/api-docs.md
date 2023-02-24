---
title: API Docs
author: Amjad Masad
date: 2016-06-24T07:00:00.000Z
categories: eng
---

[Update Oct 2022: We have retired our API, we are excited by our previous work but we do not have the resources to support this at the moment.]

Repl.it's code execution API is an HTTP and WebSocket endpoint that you connect
to and send code to execute. You can connect from any device or browser and
start executing code. This guide will describe the concepts behind the service,
how it can be used, and provide a step-by-step guide for signing up and trying
out the service!

## Code Execution

You're probably here because you want to run some user code in an app or website
somewhere. Our customers use the Repl.it API for many different things including:

* In-browser coding environments
* In-browser coding exercises
* Correcting student/user code in an online course
* Realtime interviews
* Many more

So you're at the right place. We provide a sandbox in the cloud to
execute code securely, reliably, cheaply, and easily. The code that you send us
will be executed in a Linux container where you have the ability to access system
resources like the filesystem. Anything that works in a regular development
environment should work on our API.

## The HTTP Interface

If you're interested in executing a piece of code or a project (multiple files) without opening a two-way persistent connection then you should
go with this interface. It's only one API call and it's much simpler.

For an example of how this is used in the wild take a look at
[CoderByte](https://coderbyte.com/editor/guest:First%20Factorial:Python) which
uses our API to create in-browser coding challenges.

## The Websocket Interface

If you want to create a
[REPL-like](https://en.wikipedia.org/wiki/Read%E2%80%93eval%E2%80%93print_loop)
experience where your users can execute code in a *stateful* environment then
this should be your choice. What we mean by stateful is that you can, for
example, define a variable with one call and then access it in in the next. You may be
familiar with this concept from using the Python, Ruby, or Node repl:

```
$ python
>>> x = 1
>>> x
1
>>>
```

For an example of how this is used in the wild take a look at, yours truly,
[repl.it](https://repl.it).


## The JavaScript library

We provide a JavaScript library
[ReplitClient.js](https://github.com/replit/ReplitClient.js) that helps you
connect to our servers and run your code. If you need libraries in other
languages, please get in touch with us. The library leans heavily on JavaScript
Promises to manage async code. It's well documented, well tested, and battle-tested.

The library is installable from npm:

```
npm install replit-client
```

Alternatively you can grab a ready-built library from our site:

```
<script src="https://repl.it/lib/api.js" type="text/javascript" charset="utf-8"></script>
```

## The Token Generator

For security purposes, there is a small backend component, which is
standard for most services that need to generate tokens. Your tokens are good for 5
days, but it's best to generate a new token per user. [Here is a Ruby
program](https://repl.it/gZp/1) that some of our customers use to generate tokens.

Just replace "keyboardcat" with your secret key (found on your account page) and you're good to go.

<script src="//repl.it/embed/gZp/1.js"></script>

## Plans and Limits

The limits are outlined on our [API](/site/api) and [checkout](/api/checkout)
pages. We have two limits that we impose:

* Runs: which is how many times you call `evaluateOnce` or `eval`
* Concurrent WebSocket connections: how many people are connected at the same time

We impose the connection limit on websockets because we keep the
container running for your user while they're connected and this costs us money.

You can see your current status of how many connected users and how many
runs you have left by visiting the following URL where {SECRET} is found on your account page and
in the email we sent you when you signed up.

```
http://api.repl.it/cus/{SECRET}
```

You can read more on the mechanics of rate limiting
[here](/site/blog/websocket-rate-limiting).

## Getting Started

1. Pick the right plan for you and [signup](https://repl.it/site/api) for our
service.
2. Go to your [account](https://repl.it/account) and grab your secret token
3. Grab the JavaScript library (described above)
4. Instantiate the repl instance:

    ```javascript
    var repl = new ReplitClient('api.repl.it', 80, 'ruby', REPLIT_TOKEN);
    ```

5. Use the http interface to execute code:

    ```javascript
    repl.evaluateOnce(
      'puts "hello wolrd"', {
      stdout: function(output) {
        // output from the ruby process: hello world
        console.log(output);
      }
    }).then(
      function success(result) {
        // The evaluation succeeded. Result will contain `data` or `error`
        // depending on whether the code compiled and ran or if there was an
        // error.
        if (result.error) {
          console.log('Error:', result.error);
        } else {
          console.log('Result', result.data);
        }
      },
      function error(error) {
        // There was an error connecting to the service :(
        console.error('Error connecting to repl.it');
      }
    );
    ```

6. Or use the websocket interface to execute code:

    ```javascript
    repl.connect().then(function() {
      console.log('connected');

      // Connected now we evaluate some code.
      return repl.evaluate('x = 1');
    }).then(
      function() {
        // The evaluation succeeded. Result will contain `data` or `error`
        // depending on whether the code compiled and ran or if there was an
        // error.
        if (result.error) {
          console.log('Error:', result.error);
            } else {
          console.log('Result', result.data);
        }

        // After that you may repeat the process and evaluate code in the same context.
      },
      function error(error) {
        // There was an error connecting to the service :(
        console.error('Error connecting to repl.it');
      }
    );
    ```

We put together an [end-to-end example](https://repl.it/C5ox/1) for you on repl.it.
You just need to generate your token (you can use [this](https://repl.it/gZp/1))
and then insert in the JavaScript file where it says `TOKEN` and you should be
able to test out the service.

For more documentation about our JS library don't forget to checkout the
[repo](https://github.com/replit/ReplitClient.js). And shoot us an
[email](mailto:contact@repl.it) with any questions.
