# Installing packages

Replit will install most available Python and Javascript packages using [the universal package manager](https://blog.replit.com/upm).

## Searching For and Adding Packages

On a Python or JavaScript Repl, you can search for a package to install by clicking on the <img
src="https://replit-docs-images.util.repl.co/images/media/misc/libraries_hover.png"
style="height: 24;verticalAlign: text-bottom;width: 21;margin: 0 3px;display: inline-block"/> icon on the sidebar in the workspace. Search for the package you want and select it to install the package or to view its documentation. Clicking on the "Add Package" icon will put it in a spec file and a lock file.

Unless otherwise specified, your Repl will attempt to install the latest version of each package.

## Direct Imports

If you would prefer to import directly, you can do that too (though we recommend using the Package Manager):

Python:

```python
import flask
```

JavaScript:

```javascript
const express = require("express");
```

This will install the latest version of the package into your Repl. A spec file and lock file will be created so the versions won't change. Wherever possible, we recommend using a file to manage dependencies.

### Guessing Failures

When you add a package by importing, we guess what package you want based on the modules you are importing. This works well for most languages, but in Python we sometimes get it wrong. If that happens, you can request a specific package on the import line.

```python
import twitter #upm package(python-twitter)
```

You can configure additional options for package guessing by reading about the [.replit](/programming-ide/configuring-repl) file.

## Spec Files

Each language has a file that is used to describe the project's required packages:

- Python: `pyproject.toml`
- JavaScript (Node.js): `package.json`

### Python

In a `pyproject.toml` file, you list your packages along with other details about your project. For example, consider the following snippet from `pyproject.toml`:

```
...
[tool.poetry.dependencies]
python = "^3.8"
flask = "^1.1"
...
```

This will tell the packager that your project requires at least Python version 3.8, and to install the flask package at version 1.1.

### JavaScript

Note that `package.json` files are only for Nodejs/Express Repls (they do not work in HTML/CSS/JS Repls). A `package.json` file contains more information about the project, but also lists the dependencies. As an example, here is the `package.json` file you can include in a
[Nodejs/Express template](https://replit.com/languages/nodejs):

```json
{
  "name": "app",
  "version": "0.0.1",
  "description": "",
  "main": "index.js",
  "scripts": {},
  "author": "",
  "license": "MIT",
  "dependencies": {
    "express": "latest",
    "body-parser": "latest",
    "sqlite3": "latest"
  }
}
```

All the packages will be installed with the latest version. If you need a specific version number, you can replace "latest" with that version number or precede a version number with a carat `^` to indicate "this version or newer". For example:

```json
  "dependencies": {
    "express": "^4.16.3",
    "body-parser": "latest",
    "sqlite3": "3.1.12"
  }
```

This will install `express` at version 4.16.3 or newer, `body-parser` at the latest version, and `sqlite3` at exactly version 3.1.12.
