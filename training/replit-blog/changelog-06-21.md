---
title: Changelog - June 2021
author: Replit team
date: 2021-07-02T18:00:00.000Z
categories: news
---
Welcome to the June edition of our monthly changelog, where we highlight some of our big and small feature releases, user experience changes, and bug fixes!


We love hearing from you! Please leave any feedback you have [here](https://replit.canny.io/general-feedback).

# Features

- We released the first version of our multiplayer debugger! See the [blog post](https://blog.replit.com/multiplayer-debugging) for all the details.
- You can now observe other users when multiplaying by clicking on their avatar. ![follow demo](images/changelog/follow-demo.gif)
- You can now also see which file other users are in from the filetree. *
- New dotfiles features:
  * nix repls can now use `~/${REPL_SLUG}/.config` to store their dotfiles / config files in a [XDG Base Directory Specification](https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html)-compliant way.
  * ssh and fluxbox dotfiles are now available at `~/${REPL_SLUG}/.config/{ssh,fluxbox}` respectively for all repls, nix or non-nix.
- Have you ever had the urge to download one, single file from a repl? Now you can! Just click on the three dots next to file name and hit ‘Download’ to download your file. ![downloading just one file. amazing.](images/changelog/single-file-download.gif)

# User experience changes
- We rolled out an updated profile experience. Visit any replit user's profile to see their showcased repls. We really like this [one](https://replit.com/@LeviathanCoding?showcase=2)!
- The Packages tab has been updated with a fresh coat of paint. Information is now more contextual and notifications happen inline. 
  ![Packager UX update — packages expand inline now, and versions are exposed](images/changelog/packager-updates.png)
- `.replit` and Secrets overrides are now evaluated more consistently in more places. In increasing order of priority:
  - The OS environment:
    - The environment baked into Polygott
    - The environment injected by Docker
  - The nix environment
  - The `.replit` file
  - Secrets



# Bug fixes

- GitHub commits should now properly attribute changes to your GitHub account, and will use a privacy email when that setting is enabled on your GitHub account.
- We cleaned up some extra blank space near the home screen header.
- Fixes around deleting team repls.
- The notification icon is back in its correct location.
- Deleting an open file could temporarily open a .env file.
- Users sessions expire much less frequently, keeping you logged into replit longer.


\* enabled for [explorers](https://docs.replit.com/misc/explorer)