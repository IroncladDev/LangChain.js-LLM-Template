# CLUI, the Graphical CLI

Replit has created a text-based interface to interact with various aspects of your account. This page serves as documentation of the various capabilities of CLUI.

## Accessing CLUI

Navigate to the [CLUI page](https://replit.com/~/cli) to access the graphical prompt CLI

![clui](https://replit-docs-images.util.repl.co/images/animations/nav-to-clui.gif)

The prompt will display in-line information about the commands which can be run.

## Walkthrough

This video walks you through how to access and use the CLUI.

<div style={{
  position: 'relative',
  paddingBottom: '56.25%',
  height: '0'
}}>
  <iframe src="https://www.loom.com/embed/a728d471bcaa4bf9861a4ce96ce62b51" frameborder="0" webkitallowfullscreen mozallowfullscreen allowfullscreen style={{
    position: 'absolute',
    top: 0,
    left: 0,
    width: '100%',
    height: '100%'
  }}></iframe>
</div>

<br/>

## Command Reference

<details>
  <summary><b>account</b>: Manage your account</summary>

`account view-warns` <br></br>
View warnings you have been issued.

`account change-username` <br></br>
Change your username (this can only be done once).

</details>

<details>
  <summary><b>trash</b>: List and restore deleted repls</summary>

`trash restore --title $title` <br></br>
Restore a deleted repl by its title. If multiple repls exist with the same name, the most recently deleted repl will be restored.

`trash view` <br></br>
View your most recently deleted repls.

</details>

<details>
  <summary><b>team</b>: View and manage your teams</summary>

`view` <br></br>>
View the members of your team.

`fork-repl-to-project` <br></br>

> Forks an existing Repl to create a Team Project

</details>

<details>
  <summary><b>clear</b>: Clears the screen</summary>

`clear` <br></br>
Clears screen.

</details>

## Further Reading

Check out our [blog post](https://blog.replit.com/clui) for a discussion on building CLUI.
