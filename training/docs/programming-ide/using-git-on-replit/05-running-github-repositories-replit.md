# Running GitHub repositories on Replit

GitHub repositories can be run automatically on Replit. Head to https://replit.com/github to import a repository. Any public repository under 500 MB (or 1GB with Hacker plan) can be cloned. You can unlock private repos after authenticating with GitHub and purchasing private repls with [Cycles](https://replit.com/pricing) or with our [Hacker plan](https://replit.com/pricing).

<img src="https://replit-docs-images.util.repl.co/images/programming-ide/running-github-repositories-replit/XOFmfO94Du.png" alt="import modal" style="width: 70% !important" />

From the modal above, you can select the repo, language, and owner of the repl. We will automatically detect the language if your GitHub repository already has a `.replit` file!

## Configuring a Cloned Repo

When you clone a repository without a `.replit` file, we automatically show the visual `.replit` editor:

<img src="https://replit-docs-images.util.repl.co/images/programming-ide/running-github-repositories-replit/2QlSkG7YCB.png" alt="Visual config editor" style="width: 70% !important" />

This will automatically create the `.replit` file and make it possible to customize how the repl will run.

You can use the shell to run any command and then set the "Run" button once you've decided what it should do.

Clicking "done" will finalize the repl's configuration and close the visual editor.

Adding a `.replit` file to a repository makes cloning fast with no configuration necessary. The configuration file can always be changed at any time. For more information on how to configure your repl, see the documentation on [configuring your repl](/programming-ide/configuring-repl).

## Adding a "Run on Replit" Badge

<img
style="height: 40px; width: 190px"
src="https://replit.com/badge/github/replit/clui"
/>

After configuring a run command for your repl, you can add a badge to your repository README that will allow anyone to run your project automatically!

### Generate a badge

<iframe
  style="border: 0; width: 100%; height: 280;"
  src="https://run-on-replit.util.repl.co">
</iframe>
