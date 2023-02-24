---
sidebar_position: 1
---

# Always On

Repls typically go to sleep after a period of inactivity. To make sure that your Repl is restarted, you can use the Always On Power Up.

You can add Always On to your Repls by purchasing [Cycles](https://replit.com/pricing) or by subscribing to our [Hacker plan](https://replit.com/site/pricing), which comes with one Always On Power Up.

## What does Always On do?

Repls ordinarily do not run unless someone presses the "Run" button or if [the Repl receives HTTP traffic](/hosting/deploying-http-servers). Always On runs your Repl when neither of those occur. When running your Repl, Always On will install packages and apply [your Run button configuration](/repls/dot-replit).

Always On does not extend your Repl's lifetime, and all Repls are subject to go to sleep at any time. However, Always On will immediately run your Repl again whenever this happens. If your process exits on its own, Always On will not restart it. We recommend using [Replit Database](/hosting/database-faq) to persist information outside of your process.

## Enabling Always On

You can toggle on Always On from your Repl. To enable it:

1. Navigate to your Repl
2. Open the info panel by clicking on your Repl's name in the navbar
3. Enable Always On by pressing the toggle

![Screenshot of Always On toggle](https://replit-docs-images.util.repl.co/images/repls/always-on-toggle.png)

Once you've enabled Always On, your Repl will restart whenever it goes to sleep.
