---
sidebar_position: 3
---

# Theme Design

You can make your theme look even better by considering details like contrast, color palette, and visibility. Let's go over how to do this for your favorite themes.

## Examples of popular existing themes

Let's take a look at some of the most popular VS Code themes and spot some differences between them.

### 1. Atom One Dark

Atom One Dark is one of the most popular themes of all time. Originally made for Atom code editor, this theme has made its way across many different code editors. Take a look at the vibrant color palette used here and how well the colors contrast against each other.
![atom one dark theme](https://replit-docs-images.util.repl.co/themes/themes/atom-one-dark.png)

### 2. Nord

The Nord theme is a beautiful, minimalistic theme that uses blue, green, and white hues for syntax highlighting. While it may not use as many colors as the Atom One Dark theme, each color is carefully chosen to complement the others and the foreground.
![nord theme](https://replit-docs-images.util.repl.co/themes/themes/nord.png)

### 3. Tokyo Night (Storm)

In Tokyo Night (Storm), the contrast between the foreground text and the background is greater than in the previous two themes. It uses hues of red and purple to color the code.
![tokyo night storm theme](https://replit-docs-images.util.repl.co/themes/themes/tokyo-night-storm.png)

### 4. Night Owl

Of all the themes, Night Owl has the highest contrast between the code and the background. Similar to Atom One Dark, this color palette uses a wide range of colors rather than just one.
![night owl theme](https://replit-docs-images.util.repl.co/themes/themes/night-owl.png)

### 5. Bluloco Light

Bluloco Light has a playful design and uses a wide range of colors in its syntax highlighting palette. In light mode, the foreground colors are brighter to improve visibility against the background.
![bluloco light theme](https://replit-docs-images.util.repl.co/themes/themes/bluloco-light.png)

## Background and Foreground

As you may have noticed, we've been using the terms "background" and "foreground" a lot. Background refers to the color of your theme's background and Foreground refers to the content on top of the background, such as text. To get a better understanding of how this works, there is a blog post on how many of Replit's theme tokens work located here:
https://blog.replit.com/rui-tokens.

To choose a background color for your theme, it's best to pick a color that is close to black or white, with a hint of a colorful hue. If you take a look back at the popular themes we featured above, notice how none of the backgrounds use sharp colors like **hot pink** or **lime green**.

Here is a gif of some examples of backgrounds that should not be used for theming:

![bad themes gif](https://replit-docs-images.util.repl.co/themes/bad-themes.gif)

In contrast, here are some examples of good dark mode background colors:

![good dark themes gif](https://replit-docs-images.util.repl.co/themes/good-themes.gif)

And of course, some nice-looking light mode themes with well-chosen, accessible background colors.

![good light themes gif](https://replit-docs-images.util.repl.co/themes/good-light-themes.gif)

## Accent Colors

Accent colors should typically have a medium-high contrast relative to the background but not as high as the foreground.

![accent colors](https://replit-docs-images.util.repl.co/themes/accents.png)

## Syntax Highlighting

Notice how the code syntax colors in the screenshots above look nice next to each other and contrast well against the background. To have legible syntax highlighting in your theme, try your best to:

- Make sure your colors don't clash visually.
- Enforce a range of brightness for your color palette.
- Make sure your colors aren't hard to see against the background.
- Make sure your colors don't appear with such a large contrast difference against your background.

If you can nail those four points, your theme's going to look awesome. Here are some examples of bad code syntax highlighting colors:

### 1. Large Brightness Difference

Notice the two circled elements in the code with different colors. In this case, `app` is quite dark while the string is very bright. When the brightness of selected colors varies too much, code becomes a lot harder to read.
![bad code syntax highlighting colors in brightness](https://replit-docs-images.util.repl.co/themes/syntax-brightness-bad.png)

### 2. Poor Color Matching

Although most of the colors in this example fall within a similar brightness range, they don't look great together. It's best to choose similar colors for different areas rather than painting a rainbow all over your code. [Color Hunt](https://colorhunt.co) has some cool palettes that you can use to color different areas of your code if you need some inspiration.
![bad color matching](https://replit-docs-images.util.repl.co/themes/bad-color-matching.png)

### 3. Low Contrast

If you have to squint to see your code, that is not good. Make sure your code has enough contrast so that it can be easily read, especially by those with impaired visibility.
![super low contrast](https://replit-docs-images.util.repl.co/themes/super-low-contrast.png)

---

Awesome! Keep building great themes and you'll become a pro in no time! If you're wondering how to get your favorite theme from VS Code ported over to Replit, check out the [next tutorial](port-from-vscode)!
