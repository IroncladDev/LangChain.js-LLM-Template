---
title: How To Build a Website with Replit
author: Yev Barkalov
date: 2018-06-14T03:32:26.000Z
categories: projects
---

While you can write web applications and text-based ensembles in Repl.it, sometimes it's nice to be able to just put together a simple HTML/CSS website using the same awesome editor!

# Making your first website tutorial!

This is a guide for making your very first website using HTML and CSS and, if you follow the tutorial, you should end up with something that looks like this:

![first website tutorial](/public/images/blog/website_workshop/final.png)

Though, to succeed with this tutorial, your final website should *not* look like that. To succeed at this tutorial, you should branch off and get creative with the code you write because you won't be just making just _a_ website but _your_ website!

The first thing we're going to do is go to [https://repl.it](https://repl.it) and, where it says "Search for a Language", start typing "HTML" then select the `HTML, CSS, JS` option that comes up.

![html repl selection](/public/images/blog/website_workshop/html_repl.gif)

If you have another screen come up (where your url ends with `/repls`, `/teacher`, or `/student`), you can head over to https://repl.it/languages and select the `HTML, CSS, JS` option that way.

Now that the environment's loaded, it should look something like this:

![html repl](/public/images/blog/website_workshop/editor.png)

If you press the run button right now with the code inside the editor, you won't see much because, well, there isn't much to display. However we can change that!

In the area that starts with `<!DOCTYPE html>`, select all the text and delete it. In the blank space, put the following code in

```html
<!DOCTYPE html>
<html>
  <head>
  </head>
  <body>
    <h1>Hello World!</h1>
  </body>
</html>
```

Now when you press "Run", you should see the following come out.

<iframe height="500px" width="100%" src="https://repl.it/@yevbar/Website-Workshop1?lite=true" scrolling="no" frameborder="no" allowtransparency="true" allowfullscreen="true" sandbox="allow-forms allow-pointer-lock allow-popups allow-same-origin allow-scripts allow-modals"></iframe>

Or, if you want to view the website in a separate tab, just click on the preview button!

![website workshop preview](/public/images/blog/website_workshop/preview.gif)

You've successfully put together a "Hello World!" program in HTML! (Out of tradition, people start learning a new language by first learning how to say "Hello World!")

Let's figure out what's going on in this program before we add more ~~bugs~~ features.

The very first line
```html
<!DOCTYPE html>
```
 tells the browser that we want to display an html file, which it gladly does.

The following lines consist of words inside angle brackets that are called "tags" and are often grouped in pairs like
```html
<html></html>
```
 where the first tag is referred to as the "opening tag" and the second is referred to as the "closing tag" (an element without the opening/closing pair is then a "self-closing tag").

The set up we have with indents and opening and closing tags is not something I came up with randomly, if you inspect the element of the page (or right click and "View page source"), you should see a similar structure to this

![inspecting code](/public/images/blog/website_workshop/inspect.png)

Getting back the code we have, at the top, we have a `<head>` tag, which you can think of as being the head of the website but we don't usually see things in here but, instead, in the `<body>` tag, which has all the juicy stuff.

Inside our `<body>` element, we have an `<h1>` tag, which displays text. The `1` in the tag refers to the size, see what happens when you change the "1" to other numbers like "2" or "3". Which numbers work? Which numbers don't work? There are plenty of elements and tags that can display text so, to mix things up, let's try the `<p>` tag out!

```html
<!DOCTYPE html>
<html>
  <head>
  </head>
  <body>
    <h1>Hello World!</h1>
    <p>I love coding!
      I also love tiny plastic hands!</p>
  </body>
</html>  
```

Once that's in, press "Run" and then:

<iframe height="500px" width="100%" src="https://repl.it/@yevbar/Website-Workshop2?lite=true" scrolling="no" frameborder="no" allowtransparency="true" allowfullscreen="true" sandbox="allow-forms allow-pointer-lock allow-popups allow-same-origin allow-scripts allow-modals"></iframe>

As you can see, simply pressing enter or line break doesn't separate the two lines so, to fix that, let's put the two lines into their own `<p>`, or paragraph, tags so that your code looks like the following.

```html
<!DOCTYPE html>
<html>
  <head>
  </head>
  <body>
    <h1>Hello World!</h1>
    <p>I love coding!</p>
    <p>I also love tiny plastic hands!</p>
  </body>
</html>
```

Let's run to make sure that the two lines are separated this time...

<iframe height="500px" width="100%" src="https://repl.it/@yevbar/Website-Workshop3?lite=true" scrolling="no" frameborder="no" allowtransparency="true" allowfullscreen="true" sandbox="allow-forms allow-pointer-lock allow-popups allow-same-origin allow-scripts allow-modals"></iframe>

The reason we had to do that is because HTML does not change the spacing on content on the page, regardless of how many extra spaces or newlines there are.

Now that we've got text rolling, let's add in some images!

First thing you want to do is find an image that you want to put into your website. Feel free to use Google Images, Facebook, or some other site but, when you find the desired image, right click on it and select "**Copy Image Address**".

Images are inserted into webpages by using the image tag, or `<img>`. This element has an attribute or inner field called "src" that tells the browser where to find the image. Since we're using images from the internet with some url, what that will look like is (using the actual url instead of just the text `url`)

```html
<img src="url"/>
```

As you can see, there's no `</img>` tag and I put a slash before the second angle bracket, so this is a self closing tag. The image tag is a self-closing tag because it does not actually store any content besides, with the `src` attribute, we wouldn't have anything to put inside the opening/closing tags so we're good the way it is.

The quotes are important because the url isn't actually important to the structure of the website, it's only a specific thing about the image element. For this, I want to use the beautiful face of the Zucc, which I've stored at the url https://repl.it/public/images/blog/website_workshop/zucc.png. So, with that image, my image tag will look like

```html
<img src="https://repl.it/public/images/blog/website_workshop/zucc.png"/>
```

Once you have your image tag set, put it right in before the `<h1>` tag so that you get the following result.

<iframe height="500px" width="100%" src="https://repl.it/@yevbar/Website-Workshop4?lite=true" scrolling="no" frameborder="no" allowtransparency="true" allowfullscreen="true" sandbox="allow-forms allow-pointer-lock allow-popups allow-same-origin allow-scripts allow-modals"></iframe>

Well done, you've just used HTML in order to make a fantastic website!

However, don't you wish it had just a bit of help looking presentable?

Thankfully, there is CSS, which is short of Cascading Style Sheets. CSS is a language that allows you to style the tags and elements in the webpage.

When we were using HTML to make the website, we were using it to introduce structure and content whereas the CSS will allow us to introduce visuals and design for a more complete website.

What's nice is that we already have an "index.css" file as you can see in the file tree on the left but, if we were to put styling in there right now, nothing would change because we haven't told the browser to look at that file.

To include a CSS file, we'll need to link to it with a, you guessed it, `<link>` tag. We will be needing two attributes in this tag to include the CSS file.

```html
<link rel="stylesheet" href="index.css"/>
```

The "rel" attribute tells the browser what the importance of this file is relative to the html which, in this case, is a stylesheet and then the "href" attribute tells the browser where to look for the stylesheet, which is at `index.css`.

As said before, the `<body>` element has all the juicy content but the `<head>` element is where the metadata goes, which is data that refers to other data. In this case, we're putting in CSS, which is refers to the content inside the body. And. so, we put the link tag inside the head like so

```html
<!DOCTYPE html>
<html>
  <head>
    <link rel="stylesheet" href="index.css"/>
  </head>
  <body>
    <img src="https://repl.it/public/images/blog/website_workshop/zucc.png"/>
    <h1>Hello World!</h1>
    <p>I love coding!</p>
    <p>I also love tiny plastic hands!</p>
  </body>
</html>
```

Now that the link tag is there, we can start putting things into our styles.css file!

The way css works is by statements comprised of *selector*, *property*, and *value* in the following format

```css
selector {
  property: value;
}
```

The selector refers to the element or type of element you're looking to modify and then the property is the specific property of the desired element and the value is the value you're setting that property to.

The first thing I'm going to do is change the background to be a different color. This will mean I'm taking the `body` element and modifying the `background-color` property to the value `grey` so, following that intuition, we get

```css
body {
  background-color: grey;
}
```

When you press run, you should see the following

<iframe height="500px" width="100%" src="https://repl.it/@yevbar/Website-Workshop5?lite=true" scrolling="no" frameborder="no" allowtransparency="true" allowfullscreen="true" sandbox="allow-forms allow-pointer-lock allow-popups allow-same-origin allow-scripts allow-modals"></iframe>

Now let's change the font of the text to something truly beautiful, Comic Sans. For this, we will be changing the "font family" of the elements inside the body so I'll add on the following to our CSS file.

```css
body {
  background-color: grey;
  font-family: "Comic Sans MS", "Comic Sans", cursive;
}
```

The reason for the multiple quotes and words after the colon is because different browsers actually behave differently from each other so, by adding commas, we assure that this code will be sufficient. When run, it looks, without a doubt, gorgeous.

<iframe height="500px" width="100%" src="https://repl.it/@yevbar/Website-Workshop6?lite=true" scrolling="no" frameborder="no" allowtransparency="true" allowfullscreen="true" sandbox="allow-forms allow-pointer-lock allow-popups allow-same-origin allow-scripts allow-modals"></iframe>

One thing that's stuck out the entire time is that the text was the color black. Let's change the color of the "Hello World!" to something more lively, like perhaps green. We know that the text is an `<h1>` tag so we can target that and then style it's "color".

```css
h1 {
  color: green;
}
```

By selecting only the `<h1>` tag, you only apply whatever styles you wish to it so, if you wanted to, you could apply a "color" style to the `<p>` tag as well. The last thing I want to do before finishing this project is align everything in the center so that it stands out more properly. The style we're looking for is the "text align" style and, so, we get the following

```css
body {
  background-color: grey;
  font-family: "Comic Sans MS", "Comic Sans", cursive;
  text-align: center;
}
```

Running our webpage we now have

<iframe height="500px" width="100%" src="https://repl.it/@yevbar/Website-Workshop7?lite=true" scrolling="no" frameborder="no" allowtransparency="true" allowfullscreen="true" sandbox="allow-forms allow-pointer-lock allow-popups allow-same-origin allow-scripts allow-modals"></iframe>

However, if you followed the instructions in the very beginning you would have not made the exact same website as me but, rest assured, these are not the only things you can do with HTML and CSS and, as a matter of fact, this is now the point where you take your webpage to new levels and add in whatever it is you like! The internet is your friend and resource for the rest of this journey. If you are looking for sites for inspiration, here are a few:

- [Eel Slap](http://eelslap.com)
- [Alice Lee](http://byalicelee.com)
- [Yaron Schoen](http://yaronschoen.com)
- [Roxanne Ravago](http://www.roxanneravago.com)
- [Pushkar Modi](http://pushkarmodi.com)