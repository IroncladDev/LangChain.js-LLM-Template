# Using the Version Control GUI

In the [previous tutorial](private-repo), you learned about allowing replit access to your personal and private repositories. Let's first commit some code and then finally make a pull request with the GUI (Graphical User Interface).

<div style="position: relative;paddingBottom: 56.25%;height: 0">
  <iframe src="https://www.loom.com/embed/b665c867f74c4e3984776a1c407df341" frameborder="0" webkitallowfullscreen mozallowfullscreen allowfullscreen style={{
    position: 'absolute',
    top: 0,
    left: 0,
    width: '100%',
    height: '100%'
  }}></iframe>
</div>

---

Navigate to the Version Control tab. You can see all the past commits you've made and any file changes.

![gui interface](https://replit-docs-images.util.repl.co/gh/images/gui-interface.png)

## Making a commit to your repository

First, let's make some edits to a file in the Repl. In this case, we add a comment to one of the files.

![making code changes](https://replit-docs-images.util.repl.co/gh/images/making-code-changes.png)

After that, navigate back to the Version Control tab and see the file change.

![file change indication](https://replit-docs-images.util.repl.co/gh/images/file-change-indication.png)

Next, write a commit message in the text field and then press **Commit All & Push**.

![making the commit](https://replit-docs-images.util.repl.co/gh/images/commitment.png)

Sweet! Finally, you can check the code on GitHub to confirm that it was committed successfully.

![checking our changes on github](https://replit-docs-images.util.repl.co/gh/images/check-github.png)

## Making a pull request

Large projects that require asynchronous collaboration will often involve making pull requests to the remote repository to GitHub. The process of a Pull Request (PR) usually looks like:

1. Creating a new branch
2. Committing your changes to that branch
3. System Checks and Code Review
4. Merging

To create a new branch, go to the Version Control tab and press the "+" icon next to the branch selector.

![creating a new branch](https://replit-docs-images.util.repl.co/gh/images/new-branch.png)

Next, name your branch.

![naming-branch](https://replit-docs-images.util.repl.co/gh/images/naming-branch.png)

Add a comment describing the changes you are committing.

![updating the code](https://replit-docs-images.util.repl.co/gh/images/code-change-pr.png)

After committing your changes on your branch, push the updated code in the Version Control tab, which syncs it to your remote repository.

Navigate to the GitHub repository on GitHub and you should see a banner indicating that your new branch had recent pushes. Press **Compare & pull request** to create a PR.

![github showing a new commit](https://replit-docs-images.util.repl.co/gh/images/new-commit-indication.png)

After you add description and create your PR, the next step is usually to wait for someone to review your code. If code reviewing is disabled or if you own the GitHub repository, you should be able to merge without code review. In this case, code reviewing is disabled for this tutorial's repository so we can go ahead and merge.

![the merge button](https://replit-docs-images.util.repl.co/gh/images/merge.png)

After having merged the pull request, we can now see that our changes have been added to the repository!

![merge changes](https://replit-docs-images.util.repl.co/gh/images/merge-changes.png)

Of course we can't rely on the GUI 100% of the time since git gets to a pretty complex level. Let's learn how to use [git with the shell/terminal](git-shell)!
