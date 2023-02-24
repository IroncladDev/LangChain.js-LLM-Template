
---
title: Revamping the GitHub Import Flow
author: Victor Wang, Emilie Ma
date: 2022-07-21
cover: https://blog-images.util.repl.co/nix-github-imports/nix-github-imports.png
categories: eng,product
profiles: VictorWang19,emilieatreplit
---

Early last year, we made the [announcement that our infrastructure and Repls](https://blog.replit.com/nix) now had Nix baked in. Just a few months ago, we announced [all new Repls](https://blog.replit.com/powered-by-nix) would be Nix-based. And today, we're happy to announce that our GitHub imports flow is now also powered by Nix!

For a while now, the state of Git and GitHub integration within Replit has been a major pain point. One of the foremost problems was that while the rest of Replit jumped on the Nix train, repos imported from GitHub were still forced to use the old Bash style Repls. 

We hear you: it's frustrating not to have the ability to use our [packager](https://docs.replit.com/programming-ide/installing-packages) or to go through a convoluted multi-step import experience. While many other parts of Replit have been getting frequent updates and reworks, the code powering everything Git was left behind. 

It was thought that this change would be a rather significant and difficult change. The longer we pushed it off, the more adamant we became that we'd need to get it done right this time.

We finally decided that enough was enough - we dove deep into actually resolving this. And after some changes, we very quickly realised that the problem was not nearly as scary as we thought. After some tinkering, your GitHub imports should now be faster and more intuitive than ever!

Here's a side-by-side comparison of the two flows:

<video controls>
    <source src="https://blog-images.util.repl.co/nix-github-imports/nix-github-imports-video.webm" type="video/webm">
    <source src="https://blog-images.util.repl.co/nix-github-imports/nix-github-imports-video.mp4" type="video/mp4">
</video>

---

We originally thought we would have to do a significant amount of work to integrate Nix into existing language Repls. However, in reality, we realised we could actually do the opposite.

We would start with an existing Nix language template, clear out the unused files from within it that were associated with the template, then clone in the files from GitHub. In this manner, we could preserve the existing `.replit` and `replit.nix` files that were used by each language. And we could also preserve existing environment files that were necessary for certain languages (e.g. the `venv` folder for Python).

From there, most of the existing work is already done. We then just needed a way to determine a language template to import into, which files from each template we could remove, and then finally perhaps some other small improvements to the GitHub import flow to make the user experience just a little bit nicer. 

To figure out which language template to clone into, we originally considered looking into analyzing file extensions and content, but this quickly grew unfeasible as we realized the amount of edge cases that we'd have to handle. 

GitHub API to the rescue! The GitHub API exposes [an endpoint for the languages in a repository](https://docs.github.com/en/rest/repos/repos#list-repository-languages). We use this to automatically detect your repository's language to recommend the correct template.

Next up, figuring out which files from each template to remove. We want to make sure any Repl-specific files in our templates would be overwritten by the repositories users imported. This meant getting rid of all the boilerplate files, like `index.html` in the HTML Template, and `main.py` in the Python Repl.

As well, we wanted to make sure that users can work end-to-end with Replit and GitHub. This means that the experience from working in a Repl → pushing to GitHub → importing it back should be seamless. And now, it is! `.replit` and `replit.nix` configurations pushed to the repository are always reflected in the imported Repl. 

Among our miscellaneous other improvements:
- Revamped the styling of the configuration plugin
  - More options to customize your run and compile commands, as well as an option to use our existing [Prybar](https://github.com/replit/prybar) interpreters
- Detecting and recommending common run commands, like `npm run start` for Node.js projects

---

This brings us one step closer to fully migrating Replit from our legacy [Polygott](https://github.com/replit/polygott) backend to a new Nix world. For more updates on our progress, check out [arewenixyet.com](https://arewenixyet.com/). 

We hope unleashing the full power of Nix on repository imports gives users more power to fine-tune their development environment. We're excited to see what you create with this new flow!