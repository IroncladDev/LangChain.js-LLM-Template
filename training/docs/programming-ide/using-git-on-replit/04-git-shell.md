# Using Git with the Shell

## Cloning an existing repository from the shell

Using Git in the shell allows you to do the same things as the graphical Version Control tool and much more, leveraging the full power of Git. You can use Git in the Shell on Replit the same as you would on your local terminal.

To clone a repository, use `git clone <url-to-your-repository>`. The URL should start with `https` so that you don't need to configure an SSH client on your repl. If the repository is public, it will immediately be cloned into your Replit Workspace, and you'll see the new directory appear in your files bar.

If the repository is private, you'll be prompted for your username and password. Note that GitHub no longer accepts passwords on the command line, so if you are cloning a private repository for GitHub you should rather put in a [personal access token](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token) when prompted for your password.

In the example shown below, we run `git clone https://github.com/ritza-co/git-demo.git` and can see the new files appear in a subdirectory on the left called `git-demo`.

![Git Clone](https://replit-docs-images.util.repl.co/images/programming-ide/git-with-replit/git-clone.png)

## Making changes on Replit and pushing back to a remote Git host

Once you've cloned a repository, you can make changes to your files in the Workspace. Once you're happy with the changes, you can add new files, commit your changes, and push everything back up to your Git hosting provider (e.g. GitHub) by running a few commands.

Before running any of the below, make sure you're in the correct directory. For example, if you cloned your repository using `git clone` as described above, you'll first have to change into the sub-directory, e.g. `cd git-demo` in the example we are using.

1. First, check the status of your repository by running the following command. This will show you any new files, changed files, or removed files:

```
git status
```

If you are happy with all of your changes, you can add them all with the following command:

```
git add .
```

Once you've added the files, you can run `git status` again to see that all the changes are listed in green now, showing that they're tracked by Git. In the example below, we see that we changed one file (`READEME.md`) and removed another one (The `git-demo` subdirectory). We also added a new file called `newfile.md` which is shown under "untracked files".

After running `git add .`, all files and changes are tracked by Git, so they appear under "Changes to be committed".

![Git Status and Git Add](https://replit-docs-images.util.repl.co/images/programming-ide/git-with-replit/git-status-git-add.png)

Before we can commit the files, we'll have to tell Git who we are by configuring a name and email address. Run the following commands, using your own name and email address:

```
git config --global user.name "Jane Doe"
git config --global user.email "jane@example.com"
```

Now you can commit and push your changes as follows. You may have to change the branch name `main` to whatever your branch is called, e.g. `git push origin master` or `git push origin develop` are some common names.

```
git commit -m "add newfile and some fixes"
git push origin main
```

You'll be prompted for your username and password, whether or not the repository is public. Remember to use your GitHub access token instead of your password if you are using GitHub.

If everything works out, you should see a "Writing Objects..." message, followed by "done", as shown below.

![Git Commit Git Push](https://replit-docs-images.util.repl.co/images/programming-ide/git-with-replit/git-config-commit-push.png)

## Pushing without typing in your password or access token

There's always a tradeoff between convenience and security. If you are dealing with sensitive code or information, it's best to store your password or access token in a password manager, and paste it in each time you push changes.

If you prefer, you can store your credentials as part of the remote Git URL as environment variables, using Replit secrets. This means you won't have to type your username and password each time, but it also means that anyone with access to your repl will be able to find your password or token.

Under the secrets tab in the sidebar, add a new secret. Put `GIT_URL` as the key and the URL to your Git repository with your credentials as the value. For example, on GitHub you use the format `https://<username>:<github-access-token>@github.com/<user-or-organization>/<repository>`. Click 'Add Secret'. You may have to restart your shell before this secret becomes available, which you can do by typing `exit` in the shell.

![Add secret](https://replit-docs-images.util.repl.co/images/programming-ide/git-with-replit/add-secret.png)

Now you can use `git push $GIT_URL` to push up to your remote Git host without needing to type in your credentials.

For more advanced use of Git, including branching, rebasing, cherry-picking, and more, see our [Git commands reference guide](git-commands).
