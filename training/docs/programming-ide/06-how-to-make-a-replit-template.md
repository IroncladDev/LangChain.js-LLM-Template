# How to make a Replit template

If your Repl can be used as a good starting point for other project, you might want to submit it as a template! Let's learn what a Replit template is and how to make a good one.

## What _is_ a template?

Templates are a type of published repl. They appear on the Replit [Templates page](https://replit.com/templates), where you'll find different kinds of templates. The official templates, made by Replit, have a checkbox next to the name of the template:

![Official Replit templates](https://replit-docs-images.bardia.repl.co/images/programming-ide/creating-a-template/template-official.png)

The [HTML, CSS, JS template](https://replit.com/@replit/HTML-CSS-JS?v=1#index.html) template is very popular and can be used as a starting point for creating a vanilla JavaScript project. You can fork the template to use it.

Other templates have been created by community members, like this one:

<img 
    src="https://replit-docs-images.bardia.repl.co/images/programming-ide/creating-a-template/template-community.png" 
    alt="Community Replit template"
/>

Let's learn how to make a template.

## Creating a template

You can learn how to make a repl by following [this guide]/tutorials/introduction-to-the-repl-it-ide). Once you have created the template, you can follow the Replit [publishing flow](https://blog.replit.com/publishing). Make your published repl a template by checking the "Submit as Template for Review" box in the last step of the publishing flow. The Replit team will review your template before it is live on the Templates page.

![Publish as template](https://replit-docs-images.util.repl.co/images/programming-ide/creating-a-template/publish.png)

Before you submit your template, make sure it's as easy to use as possible. It should include all the boiler plate code that is needed to get a project started, and it should work right away when the "Run" button is pressed.

A good template should always include well-commented code, easily editable variables, and a README file. It's always important to comment your code, but it's even more important when others will be using your code for their own projects. In the `README.md` file, add descriptive details about your template, and information about the variables that the user can change. READMEs help users understand how your template works, and if there are any requirements, licensing, or other factors they should be aware of.

The `.md` in `README.md` stands for Markdown, which is a basic text language. READMEs can be written in any text format, but we'll use Markdown as it's the best pratice.

Here's an example outline for a README - feel free to use this for your own templates!

```md
# Template Name

Choose a self-descriptive name, you can also add a simple description about your template.

# Usage

Explain how you can install / use this template. Make sure to provide a detailed explanation and make it easy for people to read. Also, add any code snippets if needed.

# License

This will define how people can use your template. You can visit https://opensource.org/licenses to choose a license.
```

You can also edit your submitted template and share update messages to show how your project has changed over time.

Let's take a look at a practical example of a community template.

## A practical example: Creating the Phaser Vite starter template

We created this [Phaser Vite starter template](https://replit.com/@ritza/Phaser-Vite-starter-template?v=1) to show you how you can create your own templates in Replit. The Phaser Vite starter template includes everything you need to create a Phaser game in Replit.

Phaser is a beginner-friendly 2D JavaScript game framework that is used to create HTML5 games. [Vite](https://vitejs.dev) is a development server and JavaScript bundler.

The Phaser Vite starter template is quite complex, as it provides for developing your game as well as creating, serving, and downloading the production bundle. You can do all stages of development in your browser. Many Replit templates are less complex, such as the [HTML, CSS, JS template](https://replit.com/@replit/HTML-CSS-JS?v=1#index.html). But the Phaser Vite starter template makes for a good example template, since it shows you how you can use Replit's features to handle multiple run commands.

The Phaser Vite starter template is configured to build a production-ready bundle of a Phaser game.

The template has some basic starting code that demonstrates these useful features of Phaser 3 for building games:

- Loading game assets: images.
- Moving a sprite.
- Adding physics.
- Adding user input.
- The Scale Manager, which handles responsive game layout.
- Adding text.

The following Vite commands are available in the template:

- `npm run dev` runs `vite` to start the dev server.
- `npm run build` runs `vite build` to build the production bundle to the `dist` folder.
- `npm run preview` runs `vite preview` to serve the production bundle.

When you fork the template, the npm packages in the `package.json` file are automatically installed.

### Setting up the development server

To get the dev server template working in Replit, we needed to add a `vite.config.js` file and configure it to conditionally determine the configuration options based on the Vite command used: `dev` / `serve` or `build`. You can read more about conditional Vite configuration in the [Vite docs](https://vitejs.dev/config/#conditional-config).

### Configuring the "Run" button

The `.replit` file is used to determine what the repl "Run" button will do. The `.replit` file is hidden in most repls. You can show the hidden files by clicking the three dot menu in the file tree of the repl template, and selecting "Show hidden files". In this template, the `.replit` file is modified to make the "Run" button run different Vite commands for development and production.

<img
 src="https://replit-docs-images.bardia.repl.co/images/programming-ide/creating-a-template/show-hidden.png"
 alt="Community Replit template"
/>

The "Run" button is initially configured to run the dev server. You can see this in the `.replit` file:

```toml
# run dev
run="npm run dev"
entrypoint="/src/main.js"
```

The `entrypoint` command is the name of the main file. It's the file that will be run and is shown by default when opening the editor. For development, the `/src/main.js` file is used.

### Creating the production build bundle

Once you have finished building your game, you can create a production build bundle of your game by running the following command in the "Shell" tab:

```bash
npm run build
```

This creates a production build bundle that is added to the `dist` folder.

To view the running production bundle code, the `.replit` config file needs to be altered so that the `vite preview` command is run when the "Run" button is pressed. The dev commands need to be commented out and the commands for running the production build need to be added:

```toml
language="nodejs"

# run dev
# run="npm run dev"
# entrypoint="/src/main.js"

# run production build
run="npm run preview"
entrypoint="/dist/assets/index.a808088d.js"
```

When you bundle your code using Vite, a random hash is added to the `html`, `css`, and `js` files. The hash in the `js` file of the `entrypoint` command of your bundle would be different from the one above.

### Downloading your production bundle

If you want to use your production bundle elsewhere, you can download it as a zip file by running the following command in the "Shell" tab:

```bash
zip -r myPhaserGameDownload.zip dist
```

This will create a zip file named `myPhaserGameDownload.zip` in the file tree. You can download this zip file by clicking the three dot menu that appears next to the zip file name when you hover your mouse over the zip file, or by selecting the zip file and clicking "Download".

<img
 src="https://replit-docs-images.bardia.repl.co/images/programming-ide/creating-a-template/file-download.png"
 alt="Download zip"
/>

To create the zip file, the Nix `zip` package is added to the repl. It's used to create a zip folder of your production bundle that you can download. If you have a repl that does not have the `zip` package installed and try to use the `zip` command in the "Shell" tab, you will get the following message in the shell:

```bash
zip: command not installed, but was located via Nix. Would you like to run zip from Nix and add it to your replit.nix file? [Yn]
```

If you type `y`, you will then get the following message in the shell:

```bash
Adding zip to replit.nix
success
...
```

If you look in the `replit.nix` file, you will see that the dependency (`deps`) will be added:

```
pkgs.zip
```

This adds the Nix `zip` package to the repl. This dependency is already added to the Phaser Vite starter template.

You can also download the whole project by clicking the three dot menu in the file tree and selecting "Download as zip". This method downloads the whole project, including all of the node modules from the project dependencies.

You can enable or disable Phaser 3 features in the `vite.config.js` file to optimize your production build. Disable features you don't need to reduce the bundle size.

## A note on choosing libraries

When creating a template that uses a specific library, it's a good idea to consider alternative libraries to determine which one will make the best template.

With the Phaser Vite starter template, for example, we considered the production bundle size when choosing a bundler. We could have made the template with Webpack as a bundler instead of Vite. To compare the bundle sizes of Vite and Webpack, we created production bundles of this [Flappy Bird game](https://replit.com/@ritza/Flappy-Bird-Phaser#script.js). We used the [Phaser starter template (using Webpack 4)](https://github.com/photonstorm/phaser3-project-template) to create the Webpack bundle. The JavaScript bundle size was 1.02 MB using Webpack and 1.29 MB using the Replit Phaser Vite starter template.

To further reduce bundle size, the configurations of each bundler can be tweaked to optimize the build for a particular project. For example, Storybook compared [Webpack and Vite bundling](https://storybook.js.org/blog/storybook-performance-from-webpack-to-vite) and found that Vite produced smaller production bundles for published Storybooks.

Ultimately, we chose Vite to make this Replit Phaser template because of its ease of use and fast development build times, which makes for a better developer experience. Vite also updates the development server when code changes, even before the file is saved. It has very fast [Hot Module Replacement](https://vitejs.dev/guide/features.html#hot-module-replacement).

## Further reading

Here are some resources to learn more about submitting and configuring templates, configuring Vite, and creating a Phaser 3 game:

- [Sharing Your Repl]/hosting/sharing-your-repl)
- [Replit's new publish flow](https://blog.replit.com/publishing)
- [Configuring a Repl]/programming-ide/configuring-repl)
- [Repl Space and Templates](https://blog.replit.com/replspace-templates)
- [How Replit went from supporting 50 languages to all of them by using Nix](https://blog.replit.com/nix)
- [Configuring Vite](https://vitejs.dev/config)
- [Making your first Phaser 3 game](https://phaser.io/tutorials/making-your-first-phaser-3-game/part1)

Replit hosts [Template Jams](https://blog.replit.com/template-jam), template-building competitions with cash prizes for the winning templates. Look out for the next one if you're interested and follow the [Replit Twitter account](https://twitter.com/replit) to get the latest Replit news.
