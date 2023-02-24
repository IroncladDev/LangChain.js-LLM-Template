{
  "title": "Why I'm Excited About Object.observe",
  "date": "03/16/2014",
  "hidden": true
}
---

Object.observe is one of the newer additions to JavaScript that will be landing in [Chrome soon](https://groups.google.com/forum/#!topic/v8-users/aeSFJK1L5n4). It lets you listen to changes on objects and their properties. I think it has many interesting applications and here are the few that I'm excited about the most.

## Basic usage

Before we dive into the applications of `Object.observe`, let's take a second to look at a basic usage example.

```javascript
var o = {};

Object.observe(o, function(changes) {
  // This callback runs asynchronously and aggregates the changes that happened
  // in the previous execution turn into `changes` param.
  changes.forEach(function(change) {
    console.log(change.type, change.name, change.oldValue);
  });
});

o.foo = 1; // add, 'foo', undefined
o.foo = 2; // update, 'foo', 1
delete o.foo; // delete, 'foo', 2
```

You can start playing with it in Chrome today by going to 'about:flags' and enabling the *Enable Experimental JavaScript* flag. For more usage examples and API documentation refer to the to the [Harmony wiki](http://wiki.ecmascript.org/doku.php?id=harmony:observe).

## Two-Way Data Binding

Also known as the holy grail of JavaScript MVC frameworks. The ability to bi-directionally synchronize your model and view without piling on mountains of code makes for easier to maintain code, lower payload size, and possibly faster applications. Without `Object.observe` we currently rely on:

* wrapper objects (Backbone.Model, Ember.Object)
* dirty checking (Angular)
* getters and setters

With wrapper objects we lose interop with the plethora of JS libraries that are built to operate on plain objects and incur the cost of converting from and to plain objects when communicating over the network (or with other windows, web workers etc). On the other hand dirty checking can be expensive to perform and needs to be either performed via polling or restricting where and when we can operate on our data objects. Finally, getters and setters will only notify us of changes on the property level and not of the deletion and addition of properties on the parent object and requires a considerable amount of wiring to boot.

Frameworks can start using `Object.observe` as a faster and simpler implementation while keeping the same API. However, once this lands on all browsers, I think most people will be more than happy to go back to using plain old JS objects without losing any of the power these frameworks provide.

## Evented Programming

Every sufficiently advanced JavaScript library, framework, or application contains at least one implementation of an event emitter system. For example, if you use Backbone or Ember, you have the framework's implementation and also, jQuery's implementation on which both depend. This bloat hurts both the developer, having to deal with multiple similar implementations, and the user, having to download more data and using more bandwidth and battery life. `Object.observe` supports custom notifications via the `Object.getNotifier` API, which can be thought of as “triggering events” in the traditional event emitter implementation.

Here is an example of triggering a ready event on an application controller.

```javascript
Object.observe(App.controller, onReadyCallbak, ['ready']);

// Sometime later…
Object.getNotifier(App.controller).notify({
  type: 'ready'
});
```

## Debugging

Last week I wrote about  [JavaScript debugging techniques](http://amasad.me/2014/03/09/lesser-known-javascript-debugging-techniques/) and how to -- among other things -- break on object property access to stop and take a look at what's changing certain properties on your objects. With `Object.observe`, we can get an idea of when and what changed on an object:

```javascript
Object.observe(someObject, function(changes) {
  console.log('someObject changed', changes);
});
```

Unfortunately, we won't be able to get a stack trace that points back to the code that made the change because the callback runs asynchronously, nonetheless, it should be very useful.

## Other Resources

If you want to learn more, you might be interested in the following resources:

* [The spec on the Harmony wiki](http://wiki.ecmascript.org/doku.php?id=harmony:observe).
* [Rick Waldron's post on Object.observe](http://weblog.bocoup.com/javascript-object-observe/)
* [Addy Osmani's talk on Object.observe](http://addyosmani.com/blog/the-future-of-data-binding-is-object-observe/).
