{
  "title": "The dark side of Function.prototype.bind",
  "date": "07/02/2012",
  "hidden": true
}
---

title:
author: Amjad Masad
date:


`.bind` is a method found on function objects that statically associates the function with a receiver object `this`. It is implemented in ECMAScript 5 (The current version of JavaScript) and by many JavaScript libraries.

When writing Object Oriented JavaScript, you often find it useful to pass object methods as arguments to other functions (callbacks). At a later time when the method is invoked the `this` may change from under your feet to undefined in [Strict Mode](https://developer.mozilla.org/en/JavaScript/Strict_mode) or the window object.

The following will demonstrate the problem:


    var o = { a: 1
            , getA: function () {return this.a}
            };

    o.getA(); // 1

    var fn = o.getA;
    fn(); // undefined



Using `.bind`


    var o = { a: 1
            , getA: function () {return this.a}
            };

    o.getA(); // 1

    var fn = o.getA.bind(o);
    fn(); // 1


Don't be fooled `bind` has its share of weird behavior.
This is expected:


    var fn = o.getA;
    fn === o.getA; //true


However this:


    var fn = o.getA;
    fn === o.getA.bind(o); //false



This happens because `.bind` constructs and returns a new function that is statically bound to an object (`o` in our case).

Before writing this post a quick google search of a typical language feature rant ("considered harmful") brought up an excellent [article](http://pmuellr.blogspot.com/2010/06/bind-considered-harmful.html) by @pmuller where he explains the performance and debugging issues associated with `.bind` and his own and other's dislike to the aesthetics of using it. However I found it lacking the real practical issue that would be most annoying and counterintuitive when using `.bind` in client-side JS.

When building large JS apps, it's smart to try and approach it in a structured manner and use an MVC-like library like [Backbone](http://backbonejs.org/), others, or create your own thing. Whatever you do, you'll most probably end up with libraries that has views or widgets using a JS "class". Consider the following simple editable text widget:


    // http://jsfiddle.net/TE2Cq/

    var Editable = function (initialValue) {
        this.initialValue = initialValue || ''
        this.$container = $('<div/>').appendTo('body');
        this.$input = $('<input type="text">').appendTo(this.$container).hide();
        this.$span = $('<span/>').appendTo(this.$container).text(this.initialValue);
        this.$reset = $('<button>').appendTo(this.$container).text('reset');
        this.bindEvents();
    };

    Editable.prototype.bindEvents = function () {
        this.$span.click(this.startEdit.bind(this));
        var that = this;
        this.$input.blur(this.stopEdit.bind(this)).keydown(function (e) {
            if (e.which === 13) that.stopEdit();
        });
        this.$reset.click(this.reset.bind(this));
    };

    Editable.prototype.startEdit = function () {
        this.$span.hide();
        this.$input.show().val(this.$span.text()).select();
    };

    Editable.prototype.stopEdit = function () {
        this.$span.text(this.$input.val()).show();
        this.$input.hide();
    };

    Editable.prototype.reset = function () {
        this.$span.text(this.initialValue);
    };


This looks great and from a quick look it seems like a library that will allow for extending, sub-classing, overriding, mixins etc. But in reality it isn't as dynamic as a JavaScript class should be. JS classes are really nothing more than a function (constructor) with a prototype and some functions we tend to call "methods" in that case attached to it that are by nature not bound and hence free agents that allow for and should be thought of as reusable functions.

Let's say I want to use the editable widget so I include the library on my page and instantiate it:


    var editable = new Editable('Hello World');


It renders and it does most of what I want from an editable field. However I need this one more confirm dialog step before resetting any editable field. So from my understanding of JavaScript and how prototypes and method (or property) dispatch work, I would intuitively think the following should work:


    editable.reset = function () {
        if (window.confirm('Are you sure you want to reset the text field?')) {
            Editable.prototype.reset.call(this);
        }
    }

This would successfully override the `reset` method on the instance and be able to call the super method. However clicking the reset button the widget had created before would ignore what we just did here and just execute the original method. This is because we passed it a bound version of the method that on it's own became a living thing that we don't have a reference to and can never easily be unbound as the click event handler.

    $('.greet').click(user.greet.bind(user));
    // The following will not work since user.greet != user.greet.bind(user)
    $('.greet').off('click', user.greet);

The override problem can be easily solved by a bind function that doesn't break [Dynamic Dispatch](http://en.wikipedia.org/wiki/Dynamic_dispatch#JavaScript_Implementation).

    // A simple bind function that takes an Object `obj`
    // and a method `m` and returns a function that will
    // lookup the method `m` in `o` and call it with the
    // object `o` as the context.
    var bind = function (obj, m) {
        return function () {
            obj[m].apply(obj, Array.prototype.slice.call(arguments));
        };
    };

You can see it in action [here](http://jsfiddle.net/TE2Cq/1/).

## Bind all the functions

A language like JavaScript is naturally geared towards reuse and if I as a library user that for the most part know what I'm doing, choose to use your (the library creator) function on my own object then I should be able to.

CoffeeScript (and [EcmaScript Next](http://wiki.ecmascript.org/doku.php?id=harmony:arrow_function_syntax)) introduces new function syntax that makes it stupidly simple to statically bind functions on objects which is probably going to be convenient for the library creator (I'm guilty of doing it before CoffeeScript many times for the convenience). However it will be a nightmare for users trying to get any of the promised dynamism out of the language, I believe.


    class Foo
      constructor: -> @bar = 1
      getBar: =>
        @bar

    foo = new Foo()
    alert foo.getBar.apply bar: 2 # 1

    Foo::getBar = -> 99
    # Can't even monkey patch :(
    alert foo.getBar() # 1



## Conclusion

I think I like the dynamic nature of JS and would like to use it the way it was built to be used and quit trying to make it act like something it's not. As a community we should promote and enable reuse in classes, modules, widgets, etc. I particularly like libraries which were built with reuse in mind and has clean and readable source code. I've mentioned Backbone before as it's recently becoming one of my favorite libraries, however it's guilty of statically binding methods as handlers to delegated events.
