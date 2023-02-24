{
  "title": "Python book",
  "date": "03/16/2014",
  "hidden": true
}
---

In this chapter we'll look at the basics of the Python programming language, and we'll build up to your first program! 

## What is Python?

Python is a general-purpose programming language that can be used for many different types of programming projects. It was designed by Guido van Rossum and first released in 1991. It has a simple syntax, making it easy to learn, and is powerful enough to write large applications. It has been used for many things including web development, graphical user interfaces, game development, and scientific applications.

One of the key features of Python is that it is interpreted. This means that rather than having to compile the program into a machine-readable format, you can simply run the program directly from the source code. This is one of the reasons why Python is so popular for beginners - it's easy to run and experiment with code!

Another key feature of Python is that it is a high-level language. This means that the programs you write are much more abstract than programs in languages like C. This makes them easier to read and understand, and it makes the programs easier to modify. It also means that you don't have to worry about some of the lower-level details of how the computer actually works.

One of the best things about Python is that it has a huge library of pre-written code that you can use in your own programs. This makes Python an ideal choice for beginners, since you don't have to worry about the details of how to do things - you just use the functions that someone else has already written.

Python is free, and it is available for all major operating systems, including Windows, Mac OS X, and Linux.

## Expressions

An expression is a piece of code that returns a value. For example, 2 + 2 returns the value 4, and "Hello" + "World" returns the value "HelloWorld". In Python, expressions are made up of values and operators. Values can be numbers, strings, variables, or even objects, while operators are symbols that perform some kind of action on the values. For example, the plus sign (+) is an operator that adds two values together. The following are some examples of expressions:

```
"Hello" + "World"

"I am " + "learning Python"

2 + 2

"Hello" * 3

"Hello" / 2

5 * 2

"Hello" + "World" * 3
```

In Python, expressions are evaluated from left to right, so in the above examples, the first value is added to the second, the first number is multiplied by the second number, and so on.

## The print function

The print function is used to output values to the screen. In Python, print takes one argument, which can be any value, including strings, numbers, and even other objects. For example, the following are all valid print statements:

```
print("Hello")

print(1)

print(2 + 2)

print(1 / 2)

print(1 + 1)

print("Hello", "World")

print(1 + 2, "Hello", "World")

print(2 + 2, "Hello", "World")
```

In Python, the output from print is always shown after a newline character. This is why the print statement in the above examples always ends with a newline. If you want to display multiple lines of text, you can use the triple-quoted string format:

```
print("""This is
a multi-line string. """)
```

## Basic data types

In Python, integers are used to represent whole numbers. In other languages, the integers might be called "int" or "long" instead. For example, the following are all valid integer values:

```
123

1234

1234567890

-100
```

In Python, strings are used to represent sequences of characters. In other languages, the strings might be called "str" or "text" instead. For example, the following are all valid strings:

```
"Hello"

"Hello, World"

"This is a string"

"This is a string" + " with multiple words"
```

Strings can be enclosed in single quotes (') or double quotes ("). In Python, strings are always treated as Unicode, which means that you can use any characters that are part of the Unicode character set.

The following are all valid strings:

```
'Hello'

'Hello, World'

'This is a string'

'This is a string' + ' with multiple words'

'This is a string' + ' with multiple words' + ' and multiple lines'

'This is a string' + ' with multiple words' + ' and multiple lines' + ' and a newline'
```

## Variables

A variable is a name that refers to a value. Variables can be used to store values that you need to use later. For example, you might have a variable named "number" that stores the value 2. Later, you can use the variable number to represent the value 2.

The following are all valid variable names:

```
number

a

a1

a2

abc
```

Some variables are predefined in Python, such as True and False.

Variables can be assigned values using the assignment operator, which is an equals sign (=). For example, the following assigns the value 2 to the variable number:


```
number = 2
```

Now `number` holds the integer `2`. We can now use the variable in the next expression:

```
print(number * 5)
```

Which will print `10`.


## Your first program

Before we write our first program let's learn one more function: input().

The input() function is used to ask the user to input a value. For example, the following code will ask the user to enter a number:

```
number = input("Enter a number: ")
```

When the user enters a number and hits enter, the number is stored in the variable number.

Now let's write our first program:

```
print("Hello")

print("World")

number = input("Enter a number: ")

print("You entered: ", number)

Let's look at this program in detail:

print("Hello")

print("World")
```

This code prints the words "Hello" and "World" to the screen.

```
number = input("Enter a number: ")
```

This code asks the user to enter a number and stores it in the variable number.

```
print("You entered: ", number)
```

This code prints the word "You entered:" and then the number that was entered.

# Chapter 2: Control Flow

In the last chapter we learned how to write and execute Python programs as a series of instructions. However, what makes programming powerful is its ability to control the flow of execution. That is, we can specify conditions under which a certain instruction is executed.

## Boolean Values

Python has a data type boolean, which can have the values True or False .

```
>>> True
True
>>> False
False
>>> True == False
False
```

The == operator tests for equality. The != operator tests for inequality.

Note that True and False are not strings.

## Comparison Operators

The comparison operators test whether two values are equal or not. The comparison operators are == , != , < , > , <= , >= .

```
>>> 2 < 3
True
>>> 2 == 3
False
>>> 2 != 3
False
>>> 2 > 3
False
>>> 2 >= 3
False 
>>> 2 <= 3
False
```

## Boolean Operators

The and operator evaluates to True if both operands are True . The or operator evaluates to True if either operand is True . The not operator negates a Boolean value.

```
>>> True and True
True
>>> True and False
False
>>> False or True
True
>>> not True
False
```

## If Statements

Lines of code can be grouped into a block. A block begins with a line that starts with a colon ( : ) and end when the indentation decreases. The lines within the block must be indented.

```
if x > y:
  print(x)
  print(y)
```

This if statement contains two lines of code. The first line of code prints the value of x if x is greater than y . The second line of code prints the value of y .

The if statement is an expression. If x > y is True , then the expression x is True .

The and and or operators can be used in an if statement.

```
if x > y and x > z:
  print(x)
  print(z)
```

The if statement is a compound statement. The compound statement consists of the if statement and the two lines of code. The and operator is used to join two statements.

```
if x > y and x > z:
  print(x)
  print(z)
```

If x is greater than y and greater than z , then the statements print(x) and print(z) are executed.

## Else

The else keyword can be used in an if statement to specify what should happen if the condition is not true.

```
if x > y:
  print(x)
  print(y)
else:
  print(x + y)
```

In this example, the value of x is printed if x is greater than y . Otherwise, the value of x + y is printed.

Python provides a short-circuit evaluation. If x > y is true, then x + y will never be evaluated because it is not necessary.

## Nested if Statements

A nested if statement contains one if statement inside another if statement.

```
if x > y:
  print(x)
  print(y)
  if x > z:
    print(x)
    print(z)
```

This nested if statement will print the value of x if x is greater than y . If x is greater than z , then the value of x is printed.

## else and elif

else and elif are used to extend the if statement.

```
if x > y:
  print(x)
  print(y)
elif x > z:
  print(x)
  print(z)
else:
  print(x + y + z)
```

The elif keyword can be used in place of the else keyword.

```
if x > y:
  print(x)
  print(y)
elif x > z:
  print(x)
  print(z)
else:
  print(x + y + z)
```

If x is greater than y , then the statements print(x) and print(y) are executed. If x is greater than z , then the statements print(x) and print(z) are executed.

## Loops

Loops are used to execute a block of code repeatedly. There are two types of loops: the while loop and the for loop.

## While Loops

A while loop executes a block of code while a condition is True .

```
i = 0
while i < 10:
  print(i)
  i = i + 1
```

In this example, the value of i is printed. The while loop continues until the value of i is greater than 10.

The while loop is an expression. If i < 10 is True , then the expression i is True .

## For Loops

A for loop executes a block of code a specified number of times.

```
for i in range(10):
  print(i)
```

In this example, the value of i is printed 10 times.

The for loop is a compound statement. The compound statement consists of the for loop and the two lines of code.

## Break and Continue

The break and continue keywords can be used in a loop.

```
while True:
  i = input('Enter a number: ')
  if i > 0:
    print('The number is positive.')
    continue 
  if i < 0:
    print('The number is negative.')
    break

The break keyword is used to terminate a loop.

The continue keyword is used to skip the rest of the code block and continue to the next iteration of the loop.

## The range() function

The range() function can be used to generate a list of numbers.

```
for i in range(5):
  print(i)
```

The range() function takes one parameter, which is the number of numbers in the list. The range() function returns a list.
