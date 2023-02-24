---
title: "Common Errors Python Beginners Encounter (with Solutions)"
author: James Gallagher
date: 2020-08-04T07:00:00.000Z
categories: projects
---

Like English, Python has its own set of rules. Lines of code have to be written in a certain way, just like how sentences must follow a specific structure. Punctuation must be used within a set of guidelines when you’re writing in both English and [Python code](https://careerkarma.com/blog/types-of-coding-languages/).

All programmers, even the best developers in the world, encounter errors in their code. There’s no such thing as perfection when it comes to writing code. Errors come and go. Sometimes, errors are caused by typos. Other times, errors are caused by problems in your logic.


## Encountering Errors as a New Programmer

As a beginner, encountering errors can be intimidating. You can be left asking: what should I do? The only wrong answer to that question is “give up!” There’s plenty of support available to help you overcome common errors.

In this article, we’ve compiled a list of common Python errors that beginners encounter. Each error comes with a solution that you can use to fix the error if you encounter it in your code.


## NameError: nameerror name is not defined

[NameErrors are raised](https://careerkarma.com/blog/python-nameerror-name-is-not-defined/) when you use a variable or function name that is invalid. This can be caused by making a spelling mistake when referencing or declaring a variable, using a function or a variable before it is declared, forgetting to define a variable, among other reasons.


## SyntaxError: EOL while scanning string literal

Strings must be closed on the same line on which they are declared, unless you are specifying a multi-line string. If you do not close a string, or use the wrong quotation mark to close a string, you will [receive an EOL error](https://careerkarma.com/blog/python-syntaxerror-eol-while-scanning-string-literal/).


## TypeErrors

TypeErrors are raised when you try to execute an operation on a value whose data type does not support that operation.


### list indices must be integers or slices, not str

To access items in a list, you must specify an index number. [Python array](https://careerkarma.com/blog/python-array/) is indexed from 0 which means that the first item in a list is at the position 0, the second item in a list is at the position 1, and so on. If you try to access a list using a string value, [this error will be raised](https://careerkarma.com/blog/python-typeerror-list-indices-must-be-integers-or-slices-not-str/).


### can only concatenate str (not “int”) to str

Strings can only be concatenated with other strings. Merging a string with an integer results in an error. [To solve this error](https://careerkarma.com/blog/python-typeerror-can-only-concatenate-str-not-int-to-str/), you should convert all numbers to a string before you concatenate them to a string.


### ‘int’ object is not iterable

Unlike lists and dictionaries, you cannot iterate over an integer. This error is commonly raised when you forget to use a range() statement to iterate over a list of numbers. You can [solve this error](https://careerkarma.com/blog/python-typeerror-int-object-is-not-iterable/) by ensuring that you surround a list by a range() statement if you are iterating over it.


### ‘str’ object does not support item assignment

Strings in Python are immutable, meaning they cannot be modified directly. If you want to change the value of a string, [you must create a new string from an existing one](https://careerkarma.com/blog/python-str-object-does-not-support-item-assignment/). This error is raised when you try to change a string as if it were a list using the item assignment technique.


### can’t multiply sequence by non-int of type ‘float’

In Python, strings can be multiplied. This creates a new string that repeats the contents of an old string a certain number of times. Strings cannot be multiplied by floats. If you try to multiply a string by a float, [this error](https://careerkarma.com/blog/python-typeerror-cant-multiply-sequence-by-non-int-of-type-float/) will be returned by the Python interpreter.


## IndexErrors

IndexErrors are returned when you try to access an index that does not exist in a list.


### list index out of range

You can only access items in a list if they exist. This error is common in loops that iterate over a list of numbers and do not account for the fact that lists are indexed from zero. To [solve this problem](https://careerkarma.com/blog/python-indexerror-list-index-out-of-range/), make sure that any list item you reference in your code exists.


### list assignment index out of range

Similarly, you cannot assign an item to a position in a list that does not exist. You can [solve this error](https://careerkarma.com/blog/python-indexerror-list-assignment-index-out-of-range/) by initializing a list with default values before you assign new values to the list.


## Conclusion

We’ve only scratched the surface of all the errors that you can encounter while [learning Python](https://careerkarma.com/blog/how-long-to-learn-python/). There are a lot of unique ways to make mistakes in your code. Here are a few more errors that you may encounter:



*   [typeerror: a bytes-like object is required, not ’str’](https://careerkarma.com/blog/python-typeerror-a-bytes-like-object-is-required/)
*   [typeerror: string indices must be integers](https://careerkarma.com/blog/python-typeerror-string-indices-must-be-integers/)
*   [syntaxerror: positional argument follows keyword argument](https://careerkarma.com/blog/python-positional-argument-follows-keyword-argument/)
*   [typeerror: 'int' object is not subscriptable](https://careerkarma.com/blog/python-typeerror-int-object-is-not-subscriptable/)

Remember, errors are incredibly common. You’ll see developers of all shapes and sizes encounter even the most basic errors on a day-to-day basis. The challenge is in how you respond. It may take some time to solve an error. Once you do, you’ll get a great sense of relief.


**_About the author_**

<img src="https://careerkarma.com/blog/wp-content/uploads/2020/01/james-gallagher-300x300.jpg" alt="James Gallagher" style="height:150px; width:150px; display:inline-block; horizontal-align:left;">

_James Gallagher is a writer at [Career Karma](https://careerkarma.com/) where he focuses on coding tutorials and technical articles. ([twitter](https://twitter.com/jamesg_oca))_
