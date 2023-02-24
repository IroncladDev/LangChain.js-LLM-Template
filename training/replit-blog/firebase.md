---
title: How to use Firebase for a website with Replit
author: Yev Barkalov
date: 2018-07-26T00:55:39.000Z
categories: projects
---

Today we're going to learn how to use Firebase as a database for a simple website using JavaScript!

Right now, this is what my fantastic website looks like

> ![This is my fantastic website!](/public/images/blog/firebase/fantastic_website.png)

What I want to do is include a guestbook, a way for people who visit the site to leave a wonderful message for those who follow in their steps. So, in the end, I should have a website that looks something like this.

> ![website with textbox](/public/images/blog/firebase/fantastic_final.png)

I don't have any CSS in my website but that's only so the implemented feature is blatantly obvious.

The first thing you'll need for this is a website and a url you can access it with. I'll be using my fantastic website which you can fork [here](https://repl.it/@yevbar/My-Fantastic-Website). Once you have those two things, continue along to the following steps!

We need to first set up Firebase before we can use it in our website so let's go and do that. If you're interested in learning a bit more about Firebase, check out their website at [firebase.google.com](https://firebase.google.com/).

Once you're ready, go over to [console.firebase.google.com](https://console.firebase.google.com/). If you're not already logged into a Google account, it'll prompt you to do so.

As soon as you're logged in, you'll be greeted with your Firebase Console

![Firebase website](/public/images/blog/firebase/console.png)

Go ahead and "Add Project" then put whatever you like for the name of your application

![project on firebase](/public/images/blog/firebase/i_love_replit.png)

Select "Create Project" and after a few seconds you'll see the dashboard for the app you just created

![firebase dashboard](/public/images/blog/firebase/dashboard.png)

At this point, we have an application but it's not fully configured yet so let's change that. Under **Develop**, select **Authentication**

![firebase authentication](/public/images/blog/firebase/authentication.png)

Next, go to the **Sign-In method** tab

![firebase signin](/public/images/blog/firebase/signin_method.png)

Scroll down to the section with **Authorized domains** and add the url for the hosted repl

![firebase domain](/public/images/blog/firebase/domain.png)

The last thing we need to do to configure our database is actually set the permissions for an app to access/write our database. To do that, go over to **Database**

![firebase database](/public/images/blog/firebase/database.png)

Scroll down to **Realtime Database** and "Create database"

![firebase realtime](/public/images/blog/firebase/realtime.png)

It doesn't really matter what rules you initialize with since we'll be setting those next. As soon as you create your database, you'll see a dashboard for that database. Click on "Rules" and, if needed, modify the JSON so that it's the following

```javascript
{
  "rules": {
    ".read": true,
    ".write": true
  }
}
```

What this means is that any user or app that is under the authorized domains can both read and modify our database. In my case with reviews on my website, I don't really mind, however, if you're making a website or project where security of information is important then do manage permissions accordingly. If you're looking to access the database from a server or such, check out how to [add the Firebase Admin SDK to your server](https://firebase.google.com/docs/admin/setup) so that you can properly configure the rules for your app.

With that, we're ready to start using Firebase!

The first thing we'll need to put in our website are some dependencies. I'll be using JQuery to dynamically add comments as well as two Firebase libraries where one's to connect to Firebase and the other is to utilize the realtime database. Be sure to put these before any of your `<script>` elements

```html
<script src="https://code.jquery.com/jquery-3.3.1.min.js"></script>
<script src="https://www.gstatic.com/firebasejs/5.3.0/firebase-app.js"></script>
<script src="https://www.gstatic.com/firebasejs/5.3.0/firebase-database.js"></script>
```
At the end of my `<body>` I put a `div` with the id "comments" and this is where my comments will go

```html
<body>
  <!-- Some other HTML... -->
  <div id="comments">
  </div>
</body>
```

That's it for the HTML, now we can get working in our JavaScript file.

First, we'll put in our JQuery `ready` function so that the code only executes when the browser is ready

```javascript
$(document).ready(function() {
   // This is where our code will go
});
```

We've already configured the database but we need to actually initialize a database connection in our JavaScript so go back to the dashboard for your application and select **Add Firebase to your web app** so that you're prompted with a code snippet

![firebase code snippet](/public/images/blog/firebase/add.png)

Copy the JavaScript that's between the `script` tags and paste it into your `ready` function so it looks something like this

```javascript
$(document).ready(function() {
  // Initialize Firebase
  var config = {
    apiKey: "AIzaSyDz8OrTtNBOZY2HliZ2-cmsPX8wi-4rGAQ",
    authDomain: "i-love-replit.firebaseapp.com",
    databaseURL: "https://i-love-replit.firebaseio.com",
    projectId: "i-love-replit",
    storageBucket: "i-love-replit.appspot.com",
    messagingSenderId: "214072077152"
  };
  firebase.initializeApp(config);
});
```

This just connects to Firebase, we'll want to connect to the Realtime Database and we can do so with the following

```javascript
let guestBook = firebase.database().ref();
```

With the `guestBook` object, we can utilize the power of the realtime database (moohoohaha)

The first method I'm going to define is a `signGuestbook` method so, whenever I have a name and comment for a review, I can append it on swiftly

```javascript
function signGuestbook(name, comment) {
  $("#comments").append("<p><b>" + name + "</b><br/>" + comment + "</p>");
}
```

With that method defined, we're ready to receive objects in the database so let's create a listener for that

```javascript
guestBook.on('child_added', function(guest) {
  // Code goes here
});
```

The way we can access the `guest`'s data is by calling its `val()` function and, using our `signGuestbook` method, we can add reviews as we receive them

```javascript
guestBook.on('child_added', function(guest) {
  if (guest.val().name && guest.val().comment) {
      signGuestbook(guest.val().name,guest.val().comment);
  }
});
```

The reason for checking that the `name` and `comment` are truthy is so that our comment appending doesn't break.

So now that we're ready to receive guests and reviews, let's introduce a way to create them in the first place. To do that, I made a simple HTML form

```html
<form id="guestbook">
      <span>Name:</span>
      <br/>
      <input type="text" id="name">
      <br/>
      <span>Comment:</span>
      <br/>
      <input type="text" id="comment">
      <br/>
      <button type="submit">Submit</button>
</form>
```

To keep the page from reloading when I "submit", I use JQuery

```javascript
$('#guestbook').submit(function(event) {
    event.preventDefault();
});
```

When I submit my form, that means I'm adding a review so let's add the given values to our database

```javascript
$('#guestbook').submit(function(event) {
  event.preventDefault();
  // Add guest to guestbook
  guestBook.push({
    name: $('#name').val(),
    comment: $('#comment').val(),
  });
});
```

The reason we only add the review to Firebase and not call `signGuestbook` is because, when we add the review, it triggers the `child_added` listener so it gets appended from that.

For the sake of keeping things clean, I'm going to clear the input elements and reset the focus

```javascript
$('#guestbook').submit(function(event) {
  event.preventDefault();
  // Add guest to guestbook
  guestBook.push({
    name: $('#name').val(),
    comment: $('#comment').val(),
  });

  $('#name').val('');
  $('#comment').val('');
  $('#name').focus();
});
```

Go ahead and start adding your comments and you'll see your guestbook come to life! If you reload the tab or open in another browser, after a few seconds, you'll see all the previous reviews get appended even though we never made an explicit call to get old data!

The reason for that is, when we initialize our `guestBook` with the realtime database, it syncs up old data so that it's in the same state as it is on Firebase which makes thing convinient on our end.

The last topic to cover is a massive security flaw on our website called XSS. You can learn a lot from the [OWASP page](https://www.owasp.org/index.php/XSS) but it's an attack where user generated code gets executed on another client's app.

As an example for something you can do right now, put the following as either a name or comment

```html
<script>alert(1);</script>
```

What this does is alert the browser which, albeit, is just annoying. However, I can run any javascript here which means I can do a lot more than just annoy you.

How do we solve this? The only thing we really need to do is HTML escape some characters and we can do that with JQuery

```javascript
function signGuestbook(name, comment) {
  const review = document.createElement('p');
  review.textContent = comment;

  const name = document.createElement('p');
  const bold = document.createElement('b');
  bold.textContent = name;
  name.appendChild(bold);

  document.getElementById('comments').appendChild(name);
  document.getElementById('comments').appendChild(review);
}
```

And, with that, you have a functioning guestbook on your website!

If you have any questions or just want to say hi, feel free to shoot me an email at [yev@repl.it](mailto:yev@repl.it) and till next time!