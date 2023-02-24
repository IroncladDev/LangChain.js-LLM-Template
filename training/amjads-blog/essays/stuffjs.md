{
  "title": "stuff.js",
  "author": "Amjad Masad",
  "date": "12/11/2012",
  "hidden": "true"
}
---

With the explosion in online tools that allow to write, share, and run HTML, CSS, and JavaScript
like [JSFiddle](http://jsfiddle.net/), [CSSDeck](http://cssdeck.com/), [codepen](http://codepen.io/)
and many others! I was surprised to see that there wasn't a good opensource library to facilitate
securely running arbitrary code in the browser. So I pulled this out of our codecademy.com source code
into a well-tested library with a nice interface. I call it [stuff.js](https://github.com/Codecademy/stuff.js)
(stuff as in stuffed turkey) and it's on [GitHub](https://github.com/Codecademy/stuff.js).

Here is how you can create a live coding interface (similar to codepen) in less than thirty lines of code using stuff.js
and codemirror:

```javascript
stuff(secureIframeUrl, function (context) {
  var html = CodeMirror.fromTextArea($('#html'), {
    onChange: reload
  , mode: 'text/html'
  });
  var js = CodeMirror.fromTextArea($('#js'), {
    onChange: reload
  , mode: 'javascript'
  });
  var css = CodeMirror.fromTextArea($('#css'), {
    onChange: reload
  , mode: 'css'
  });

  var t = null;
  function reload () {
    clearTimeout(t);
    t = setTimeout(function () {
      var code = '<!DOCTYPE html><html><head>';
      code += '<style>'  + css.getValue() + '</style>';
      code += '<body>' + html.getValue();
      code += '<script>' + js.getValue() + '</script>';
      code += '</body></html>';
      context.load(code);
    }, 50);
  }
  reload();
});
```

Stuff.js puts security first. It is intended to be served from multiple origins for the code to be properly sandboxed
and not have access to the top window.
