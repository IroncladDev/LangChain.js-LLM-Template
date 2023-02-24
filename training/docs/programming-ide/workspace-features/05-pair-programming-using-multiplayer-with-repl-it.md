---
title: Multiplayer
---

# Multiplayer: Pair programming with Replit

Software developers have a reputation for being loners, but they don't always code by themselves. [Pair programming](https://en.wikipedia.org/wiki/Pair_programming) is used by many programmers to

- Write bug-free code more efficiently (for example, one person might watch for mistakes while the other codes).
- Share knowledge (a less-experienced programmer might 'follow along' while a more experienced programmer develops something, learning from each step of the process).
- Assess expertise (if you're considering a new hire, watching them code first can be helpful to assess how good a coder they are, but coding _with_ them allows you to also see their experience in teamwork and communication).

Pair programming intuitively sounds like it would be inefficient: after all, the two developers could instead be working on different projects simultaneously. But on top of catching more bugs, two people working together often display more creativity as well. You might think of an idea based on something your buddy said that wouldn't have come to you alone.

If you have a friend handy, work through this tutorial together to gain real pair programming experience. If you're alone, fire up two browsers (or use incognito mode) to sign into two Replit accounts simultaneously.

## Extending our data science article using pair programming: Getting help

Imagine that you are a developer who has come across the [previous tutorial on plotting and graphing](http://www.codewithrepl.it/04-data-science-and-visualisation-with-repl-it.html). You want to adapt the graphs shown a bit, but you haven't used Python much, so you decide to ask your friend for help.

In this scenario, you are "@Lean3Viljoen94" and the friend that you're asking for help is "@GarethDwyer1".

Start by forking [the data science repl](https://replit.com/@GarethDwyer1/04-data-science-and-visualisation-with-replit) and making sure that you can run it.

![**Image 1:** *Forking another user's project*](https://replit-docs-images.util.repl.co/images/tutorials/05-multiplayer/05-01-fork-repl.png)

Now from your own fork, press the `share` button, as shown below.

![**Image 2:** *Sharing your project with another user*](https://replit-docs-images.util.repl.co/images/tutorials/05-multiplayer/05-02-share-repl.png)

Copy the invite link, and note that this is different from the normal link to your repl. If you copy the link from your URL bar, you can give people _read_ access to your repl, but by copying the invite link you'll give them _write_ access.

![**Image 3:** *Sharing options modal*](https://replit-docs-images.util.repl.co/images/tutorials/05-multiplayer/05-03-share-link.png)

If you knew your friend's Replit username or the email associated with the Replit account, you could instead use the `Invite` box at the top. Share the link with your friend and wait for them to join.

As soon as they do, you will see that a chat box pops up in the bottom right corner. Their profile picture or letter will be at the top of the chat box, so you can always know who is currently active.

Remember, you forked the repl in a previous step, so you are the owner of this fork and the "host" of this multiplayer session. If you invite multiple people and then leave, they can continue collaborating without you, but they won't be able to rejoin if the host is no longer in the session.

You can use the team chat feature, as shown below.

![**Image 4:** *Starting chat with another user*](https://replit-docs-images.util.repl.co/images/tutorials/05-multiplayer/05-04-team-chat.png)

In the previous tutorial, we looked at GDP by country. Imagine that you are now interested in how this is broken down by _continent_ too. You still want to plot each country as a separate data point, but you want them in different colours, one for each continent. You're not sure how to do this, so you ask for help.

You can see a typing indicator to help decide if you should wait around for a reply or go make coffee.

![**Image 5:** *Chat box showing that user is typing*](https://replit-docs-images.util.repl.co/images/tutorials/05-multiplayer/05-05-typing-indicator.png)

Your friend tells you about the `hue` argument and points out that you already have this data in the `continent` column in your data frame. You add `hue="continent"` to the graph and re-run it, but it doesn't quite work out how you expect.

![**Image 6:** *Changing the plot from grouping data by country to grouping by continent*](https://replit-docs-images.util.repl.co/images/tutorials/05-multiplayer/05-06-add-hue-continent.png)

Your friend suggests maybe a scatter plot without the correlation line might look better, but when you try that it results in an error. The error message is hidden by the chat box, so you move it to the other side of the screen.

![**Image 7:** *You can move the chat box to the left of the IDE to see errors better*](https://replit-docs-images.util.repl.co/images/tutorials/05-multiplayer/05-07-move-chatbox.png)

This is getting a bit more complicated than you bargained for. Sometimes showing is easier than telling, so your friend starts editing the code directly instead of telling you how to do so using chat. The code

```python
sns.scatterplot(
    "gdpPercap", "lifeExp", df, hue="continent"
).set_axis_labels("GDP per capita", "Life expectancy")
```

changes to

```python
ax = sns.scatterplot(
    "gdpPercap", "lifeExp", df, hue="continent"
)
ax.set(xlabel="GDP per capita", ylabel="Life expectancy")
```

![**Image 8:** *In our new plot, we can see that African countries tend to have low life expectancy and low GDP, but the correlation looks weaker for the other continents*](https://replit-docs-images.util.repl.co/images/tutorials/05-multiplayer/05-08-figure-one.png)

## Make it your own

If you followed along, you'll already have your own version of the repl to extend. If not, start from ours. Fork it from the embed below.

<iframe height="400px" width="100%" src="https://replit.com/@GarethDwyer1/cwr-05-multiplayer?lite=true" scrolling="no" frameborder="no" allowtransparency="true" allowfullscreen="true" sandbox="allow-forms allow-pointer-lock allow-popups allow-same-origin allow-scripts allow-modals"></iframe>

## Where next?

Getting help on a single file in a program is only one use for multiplayer, but there are many scenarios where it can be useful to see your teammates' changes in real time. For example, if you're a back-end developer you could work closely with a front-end developer, ironing out any issues with data communication between the back- and front-end in real time, instead of waiting for multiple iterations of several days.

That brings us to the end of part 1 of this series and you should now be familiar with all of the basic features of Replit.

In part 2, we'll cover more advanced features, such as running projects from GitHub, storing secrets securely, and productivity hacks.
