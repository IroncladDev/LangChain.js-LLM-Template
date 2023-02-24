{
  "title": "Lesser-Known JavaScript Debugging Techniques",
  "date": "03/09/2014"
}
---

After I prototype an app I'm building, my time is split between the editor and the browser with the console open. I try to debug as I go to avoid creating a complete mess. Moreover, when I get a bug report for a production app the first thing that I do is try to debug using Chrome devtools, and I usually find the bug without touching my editor. To be effective at that, I had to learn a great deal about the tools available and in this post I’m going to shed light on the lesser-known features and techniques of JavaScript debugging.

## Command Line API

Started by Firebug and currently implemented in all browsers with a debugger. It has [many useful](https://getfirebug.com/wiki/index.php/Command_Line_API) utility functions such as `$`, `$0`, `keys`, `values` etc. and I highly encourage you to [learn everything about them](https://developers.google.com/chrome-developer-tools/docs/commandline-api).

Until recently, Chrome DevTools [didn't implement](https://code.google.com/p/chromium/issues/detail?id=168776) the full API, and even after they did, a lot went [undocumented](https://developers.google.com/chrome-developer-tools/docs/commandline-api). The most useful of those functions are:

### debug and monitor

If you basically live in the console like I do you'd want to be able to add breakpoints to function references without having to go to the source and find the function, especially when debugging production apps with minified source or built source with no source maps.

```js
debug(ExampleApp.exampleFunction)
```

Now every time the `ExampleApp.exampleFunction` is called the debugger will be invoked. To turn it off simply call `undebug` on the same function.

However, you often just need to know if the function was called and the arguments passed to it, for that you can use `monitor` and `unmonitor`.
## Setting up traps

When working on a complex system with many modules, it's impossible to know what every part is doing. Beyond the typical `console.log`ing and breakpoint insertion, a good debugging technique is setting up traps with debugger statements to stop and get an idea of what's going on.

<blockquote class="twitter-tweet" lang="en"><p>Just debugged a link-not-working issue by doing `Event.prototype.preventDefault = function () { debugger; };`. Feeling pretty smooth.</p>&mdash; Domenic Denicola (@domenic) <a href="https://twitter.com/domenic/statuses/441758861649661952">March 7, 2014</a></blockquote>
<script async src="//platform.twitter.com/widgets.js" charset="utf-8"></script>

For a long time I've had a library of functions that I copy-pasted around to help set up traps. But after a round of polishing I'm releasing it as a stand-alone JavaScript library and a chrome extension called [Debug Utils](https://github.com/amasad/debug_utils). You can find it on [GitHub](https://github.com/amasad/debug_utils) and can install it directly from the [Chrome Webstore](https://chrome.google.com/webstore/detail/debug-utils/djailkkojeahmihdpcelmmobkpepmkcl).

## Enter DebugUtils

### Break on native method call

Unfortunately `debug` and `monitor` don't work on native methods so you need to wrap native methods with functions containing a `debugger` statement, similar to the tweet above, except you probably would want to call the original function after the `debugger` statement. In DebugUtils this is called `$dum` (short for debug utils method).

```js
$dum(Event.prototype, 'preventDefault');
```

### Break on custom events

The Command Line API provides a [`monitorEvents`](https://developers.google.com/chrome-developer-tools/docs/commandline-api#monitoreventsobject_events) function which is great for debugging DOM events, but it won't work for custom events. For that you want to setup your own debugger or logger function as a handler to an event on an object. In DebugUtils this is called `$duv` (short for debug utils events).

```js
$duv(exampleModule, 'data');
```

### Break on property access

Often times, objects can start changing from under your feet. You can [setup object getters and setters](http://johnkpaul.com/blog/2013/07/20/break-on-property-change/) containing a  `debugger` statement to find out what part of the code is responsible. When something changes a given property on your object you will stop and be able to trace back what's changing it. In DebugUtils this is called `$dus`:

```js
$dus(exampleObject, 'someProperty');
```
You can also break on property read using `$dug`.

For more documentation and information on DebugUtils, be sure to check out the [Github project](https://github.com/amasad/debug_utils). Happy debugging!

**Edit**: My EmpireJS talk on this subject

<iframe width="560" height="315" src="//www.youtube.com/embed/rcjUR4icvoQ" frameborder="0" allowfullscreen></iframe>
