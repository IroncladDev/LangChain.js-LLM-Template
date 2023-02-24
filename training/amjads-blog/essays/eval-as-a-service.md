{
  "title": "Eval as a Service",
  "date": "01/17/2016"
}
---

After operating under the radar for a while, we're now publicly launching the
[repl.it code evaluation API](https://repl.it/api) that allows anyone to execute
code in whatever language from anywhere on the internet. Here is the story so far:

[repl.it](https://repl.it) and the underlying tech is a project that grew out
of my frustration from the process of setting up machines to learn
programming. I believed that one of the main turn offs for people wanting to
learn how to code was setting up the development environment. That's when I
thought that putting a REPL on the web was the best way to get started with programming.

In 2011, and after working on the problem for almost a year we were able to cross-compile
numerous language interpreters to JavaScript and we also hand coded some. We
open sourced everything along the way and little did we know that our work would
help accelerate a revolution in online programming education.

Our [open source code evaluation infrastructure](https://github.com/replit) was used by companies like
Codeacademy, Udacity, Bloc, and many others to deliver an in-browser coding
experience. Unfortunately, the way we were
doing things was pushing the envelope for what browsers could do at the time and they would break our code
very often. Coupled with the fact that users had to download megabytes worth
of JavaScript before being able to do anything made it unreliable for websites
serving millions of users all over the world. Since then, I stopped using it in
production in favor for a server-based system and to keep myself honest I
also deprecated the open source project.

After the move, I still got emails from people asking for support on those
projects, and I felt guilty for not being able to help. At the same time
repl.it was  growing and with it my wallet was
shrinking. One of the benefits of doing client-side code evaluation was that the cost
was practically zero. I considered putting ads on the site but I
couldn't do this to our users. Especially because many of them happen to be
students learning as part of classrooms:

<div id="fb-root"></div>
<script>(function(d, s, id) {
  var js, fjs = d.getElementsByTagName(s)[0];
  if (d.getElementById(id)) return;
  js = d.createElement(s); js.id = id;
  js.src = "//connect.facebook.net/en_US/sdk.js#xfbml=1&version=v2.5";
  fjs.parentNode.insertBefore(js, fjs);
}(document, 'script', 'facebook-jssdk'));</script>

<div class="fb-post"
data-href="https://www.facebook.com/amasad9/posts/772878056174859?pnref=story"
data-width="750">
<div class="fb-xfbml-parse-ignore">
<blockquote cite="https://www.facebook.com/amasad9/posts/772878056174859">
<p>Yesterday we
visited a high school in Mountain View where the entire school were learning how
to code. Hundreds of...</p>Posted by <a href="#" role="button">Amjad Masad</a>
on&nbsp;
<a href="https://www.facebook.com/amasad9/posts/772878056174859">Saturday, October
24, 2015</a></blockquote></div></div>

After getting so many emails from people asking for support I decided to offer
our code [evaluation infrastructure as a service](https://repl.it/api). Since then we had a few customers use us -- enough to cover repl.it's cost. More than anything, I'm happy that our customers
are deriving a lot of value from the service and in many cases they're building
things in line with our mission of democratizing programming. For
example, Carnegie Mellon University is using us as part of their online open
learning initiative. Flatiron school and Trinket are using us to build their online education
platforms. Oneinterview and Airety are using us to deliver online interviewing
services. And of course repl.it uses the same API for the main site, and the
[embeds](http://amasad.me/2015/04/09/hello-world/).

I'm planning to do a technical write up about the tech and architecture behind
the service but the basic idea is that you connect to our servers and then send
us programs to execute. It's fast, reliable, and scalable. Try out at
[repl.it](https://repl.t). And check out the [API page](https://repl.it/api) for
more information. Here is what an API call looks like for a "Hello World" in
Ruby:

```js
var repl = new ReplitClient('api.repl.it', 80, 'ruby', token);
repl.connect().then(() => repl.evaluate(
  'puts "hello world"',
  { stdout: out => console.log(out) }
));
```

What started as something that I thought of as a necessary annoyance to keep the
site running turned out to be something that I'm actually proud of. This
wouldn't have been possible without the work from [Haya](http://twitter.com/hayaodeh) and Faris where they
continue to build awesome new features and products on top of repl.it.
