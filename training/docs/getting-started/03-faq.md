# FAQ | Frequently Asked Questions

## Why does my Always On Repl restart sometimes?

Repls will need to switch physical servers once in a while to help conserve resources, causing your Always On Repl to restart. Your Repl will turn back on, install all packages, and then run your code, so there will be a small delay between the restart and your code running again.

Always On can be purchased using [Cycles](/cycles/about-cycles) or as part of the [Hacker Plan](https://replit.com/pricing). See [the Always On doc](/power-ups/boosts) for how to turn on this Power Up.

### For help with Always On for chatbots/Discord bots

See the [Replit Discord](https://discord.util.repl.co/join) server #bot-help channel, or our Chatbots category in the [Replit Ask Forum](https://ask.replit.com/c/code-help/discord-bots/24)

#### Read our [Database FAQ](/hosting/database-faq) for persisting data.

## How do I restore a Repl?

Use the clui (command line user interface, [blog](https://blog.replit.com/commandbar)) to access the trash:

1. Go to https://replit.com/~/cli.
2. Once you get to the terminal, type "Trash".
3. Choose the "View" option to see your most recently deleted repls.
4. Go back to "Trash" again and choose "Restore" this time, along with the title of the project you want to restore.

## How do I restore a file in my Repl?

Check out our docs on the [History tool](/programming-ide/using-repl-history) to learn how you can restore a file.

## Where can I get help with my code?

If you are having trouble with your code, you can always reach out to our lively community on our [Discord server](https://discord.util.repl.co/join) or our [forum](https://ask.replit.com). If you can't find answers within our community, search [Stackoverflow](https://stackoverflow.com/), [YouTube](https://youtube.com), or these docs: [HTML](https://www.w3schools.com/html/default.asp), [Python](https://www.python.org/doc/), [Javascript](https://developer.mozilla.org/en-US/docs/Web/javascript).

Here are some basic debugging steps you can take if you are stuck with your code:

1. Double check your code line by line for any syntax mistakes.
2. Enter the command `kill 1` in the Shell tab in your Repl.
3. Fork the Repl.
4. Install all the necessary packages via our package manager if available [packager tab.](/programming-ide/installing-packages)
5. Refresh the page.

## Why is my Repl failing to load?

If your Repl is failing to load, try these debugging steps:

1. Test your [internet connection](https://www.speedtest.net/).
2. Try a different browser.
3. Check if your browser has enabled JavaScript.
4. Use the command `kill 1` in the shell—this will kill and restart the virtual Linux machine backing your Repl.

If none of the above steps helped, check Replit's [Service Status](https://status.replit.com), if "all systems are a go," and you still have issues loading your Repl, please contact [Replit Support](https://replit.com/support).

## How do I create a custom domain?

You can link any Repl to any domain that you own. Learn how to connect your domain [here](/hosting/hosting-web-pages#custom-domains).

## I'm having trouble logging in, what should I do?

1. Make sure you are using the correct email and password.
2. Use the forgot password [page](https://replit.com/forgot) to reset your password.
3. Try a different browser to log in.
4. If those steps fail, contact support.

## How do I change my email if I signed up with Google/Github/Facebook?

We require a password to change your email on your account. If you signed up with another service, such as Google or GitHub, you will not have a password available. To change emails you will first need to go through the reset password process.

For step-by-step instructions:

1. Open the left sidebar, click on your username to open the dropdown menu, and then click `Log out`.
   <img
   src="https://replit-docs-images.util.repl.co/images/getting-started/Log%20Out.jpg"
   alt="Log out"
   style="maxWidth: 100% !important; height: 400px !important"
   />
2. Go back to the login page, click forgot password, and enter your email for the connected account:
   <img
   src="https://replit-docs-images.util.repl.co/images/getting-started/Forgot%20PW.jpg"
   alt="Forgot PW"
   style="maxWidth: 100% !important; height: 400px !important"
   />
3. You will receive an email with a link to create a new password. If you don't see the email, make sure it isn't in your spam filter.
4. Now you can go to your [account page](https://replit.com/account) and change your account email address using your new password.

## How do I change my username?

You can **only** change your username **1 time**, by [clicking here](https://replit.com/~/cli/account/change-username?run=1). If the option is not available to you, then you have already changed it.

<img
src="https://replit-docs-images.util.repl.co/images/misc/account-change-username.png"
alt="Change username"
style="maxWidth: 100% !important; height: 400px !important"
/>

## Can I merge accounts?

Unfortunately, at this time, we don't have a way for users to merge accounts.

## How can I update Python to the latest version?

Our official Python repl is currently on version 3.8. CodingCactus has
a usable [Python 3.10 template](https://replit.com/@CodingCactus/Python-310), but it doesn't support the Python console and the [tkinter](https://docs.python.org/3/library/tkinter.html) UI library.
We are working on an infrastructure update to make updating software in repls easier: nix modules. This
will enable a fully functional Python repl template for the latest version of Python.

## How do I turn on Explorer?

If you want to be on the cutting edge, turn on Explorer mode in your Account settings.

1. Navigate to your username in the upper-left corner the site, and select the down arrow.
2. Select **Account**.
   ![Show Account in username menu](https://replit-docs-images.util.repl.co/images/getting-started/select-account-in-dropdown.png)
3. Scroll down to **Roles**.
4. Toggle on **Explorer**.
   ![Showing toggle on for Explorer in Roles settings](https://replit-docs-images.util.repl.co/images/getting-started/toggle-explorer.png)

Explorers are the first to see new Replit features in the Workspace. Because those features are stil in development, sometimes things don't work as expected. If something isn't working correctly, please let us know. You can remove the role at any time to go back to the Replit you know and love.

## Cycles

### What are Cycles?

Cycles are Replit's new digital tokens! They can be purchased on Replit and combined with any user plan to increase your Repls' performance and functionality.

Cycles are _not_ a cryptocurrency. They are virtual tokens native to the Replit platform and are meant to improve your experience on Replit.

### What can I use Cycles on?

At this moment you can use Cycles to buy Private Repls, Always On, Boosts, Ghostwriter, and more features are coming soon!

### What are Power Ups?

Power Ups are anything that improves your Repls' functionality and performance. Current available Power Ups include: [Boosts](/power-ups/boosts), Always On, or Private Repls.

### How much are Cycles worth?

Cycles can be purchased for $0.01 USD per Cycle. If you earned Cycles through [Bounties](/category/bounties), they are eligible for cash out.

There is a 25% cash out fee and additional fees based on your country of residence and chosen payment method.

### Can anyone buy Cycles?

Any user, regardless of their Replit plan, can purchase Cycles.

You cannot buy Cycles through the Replit Mobile App though, you need to use the web version.

### Can I get a refund on Cycles?

Cycles are non-refundable. For further details, please refer to [Cycles Terms](https://replit.com/site/cycles-terms)

### How do I use my Cycles?

You can use your current Cycles on any Power Up from the Workspace (inside of a Repl).

<img
src="https://replit-docs-images.util.repl.co/images/cycles/FAQ/private-repl-purchase.gif"
alt="Purchase Private Repls"
style="maxWidth: 100% !important; height: 400px !important"
/>

### What happens when I toggle off my Power Up?

For Always On and Boosts, your Power Up power up's functionality on that Repl. You can change Power Ups on and off for as long as your Cycles balance meets the required amount.

### How do I stop paying for a Power Up (i.e., end a Cycles subscription)?

For Always On and Boosts make sure that you toggle off from inside of the Repl where its activated before the renewal date.

<img
src="https://replit-docs-images.util.repl.co/images/cycles/FAQ/toggle-off-boost.gif"
alt="Toggle Off Boost"
style="maxWidth: 100% !important; height: 400px !important"
/>

For private Repls bought with Cycles, head to [My Cycles page](https://replit.com/cycles) and toggle off the subscription.

<img
src="https://replit-docs-images.util.repl.co/images/cycles/FAQ/toggle-off-private-repls.gif"
alt="Toggle Off Private Repls"
style="maxWidth: 100% !important; height: 400px !important"
/>

### What happens to my private Repls if I stop using Cycles or run out of Cycles?

Your Repls will remain private but you will not be able to edit the code unless you make the Repl public or subscribe to private Repls again with Cycles.
