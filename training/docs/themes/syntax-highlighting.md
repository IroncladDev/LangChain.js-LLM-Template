---
sidebar_position: 2
---

# Syntax Highlighting

Syntax highlighting enables you to color specific tokens in your code. Imagine what a life it would be if all of your code was only one color! Thanks to Custom Themes, you can now customize syntax highlighting to your liking!

- ## `Variable Names`
  Usually this color is applied when you use or define a variable in which no declaration keyword is used.

### Javascript

```javascript
const message = "Hello World";
console.log(message); // "message" on this line gets highlighted
```

### Python

```python
message = "hello python" # no declaration keyword like "const" is used, so 'message' is colored here
print(message) # and during usage
```

- ## `Variable Definitions`
  This color gets put into use when defining a variable with a definition keyword such as `const`, `var`, `int`, etc.

### Javascript

```javascript
const variableName = "Look Ma, I'm a variable!"; // 'variableName' is highlighted
```

### Java

```java
public class Main {
  public static void main(String[] args) {
    int numericValue = 100; // 'numericValue' is highlighted
  }
}
```

- ## `Function References`
  This color gets applied when you call a function.

### Javascript

```javascript
function run() {
  console.log("I'm Running!");
}
run(); // 'run' is highlighted
```

### Python

```python
def dog_bark():
  print("Woof!")
dog_bark() # 'dog_bark' is highlighted
```

- ## `Function Definitions`
  When defining a function, this is the color that your function definition will be.

### Javascript

```javascript
function run() {
  // 'run' is highlighted
  console.log("I'm Running!");
}
```

### Python

```python
def dog_bark(): # 'dog_bark' is highlighted
  print("Woof!")
```

- ## `Keywords`
  This one color highlights the important keywords in your code such as variable definitions, class definitions, imports/exports, and more!

### Javascript

```javascript
export default async function MyAsyncFunction() {
  // 'export', 'default', 'async', and 'function' get highlighted
  // 'return' and 'new' get highlighted
  return new Promise((resolve, reject) => resolve("hello world"));
}
```

### Python

```python
import string, sys # 'import' gets highlighted
for i in sys.argv[1:]: # 'for' and 'in' get highlighted
  try: # 'try' gets highlighted
    fahrenheit=float(string.atoi(i))
  except string.atoi_error: # 'expect' gets highlighted
    print(repr(i), "not a numeric value") # 'print' gets highlighted
```

- ## `Property Names`
  This color gets applied when accessing a property from a variable.

### Javascript

```javascript
const person = {
  name: "John",
  job: "Programmer",
};
const { job } = person; // 'job' is highlighted
console.log(person.name, job); // 'name' is highlighted
```

- ## `Property Definitions`
  This color gets applied when defining a method or property.

### Javascript

```javascript
class Person {
  constructor(name, job) {
    // 'constructor' gets highlighted
    this.name = name;
    this.job = job;
    this.stats = {
      weight: 200, // 'weight' gets highlighted
    };
  }
}
```

- ## `Function Properties`
  This color gets applied when calling a method.

### Javascript

```javascript
console.log("Hello World"); // 'log' gets highlighted
```

### Python

```python
fahrenheit = float(string.atoi(i)) # 'atoi' gets highlighted
```

- ## `Tag Names`

  This color applies to tags in HTML and JSX.

  ### HTML

  ```html
  <div>This is a test</div>
  <!--'div' gets highlighted in both places-->
  ```

- ## `Type Names`

  This color applies to types in strongly typed languages such as Java, TypeScript, etc.

  ### Typescript

  ```typescript
  const name: string = "John"; // 'string' gets highlighted
  const allNames: Array<string> = [name]; // 'Array' and 'string' get highlighted
  ```

  ### Java

  ```java
  int N = 100; // 'N' gets highlighted
  boolean[] isPrime = new boolean[N + 1]; // 'boolean' gets highlighted in both cases
  ```

- ## `Class Names`
  When defining or, in some cases, using a class, this is the color that will be used.

### Javascript

```javascript
class Animal {
  // 'Animal' gets highlighted
  constructor(type) {
    this.type = type;
  }
}
const Fish = new Animal("catfish"); // 'Animal' gets highlighted
```

### Python

```python
class Person: # 'Person' gets highlighted
  def __init__(self, name, age):
    self.name = name
    self.age = age
```

- ## `Attribute Names`
  This color gets usually gets applied in HTML and JSX tag attributes.

### HTML

```html
<div className="dog" id="the-dog"></div>
<!--'className' and 'id' get highlighted-->
```

### JSX

```jsx
const MyComponent = (props) => {
  // 'passedProp' gets highlighted
  return (
    <OtherComponent passedProp={props.prop}>
      <div>{props.children}</div>
    </OtherComponent>
  );
};
```

- ## `Comments`
  This color applies to all code comments.

### Javascript

```javascript
// This comment gets colored
```

### Python

```python
# This comment gets colored
```

- ## `Strings`
  This color refers to strings in code.

### Javascript

```javascript
console.log("hello!"); // '"hello"' gets highlighted
```

### Python

```python
print("hi!") // '"hi!"' gets highlighted
```

- ## `Numbers`
  This color refers to all numerical values including integers, floats, doubles, and more.

### Javascript

```javascript
console.log(12345); // '12345' gets highlighted
```

### Python

```python
print(54321) # '54321' gets highlighted
```

- ## `Booleans`
  This color gets applied to boolean values like `true` and `false`.

### Javascript

```javascript
const t = true; // 'true' gets highlighted
const f = false; // 'false' gets highlighted
```

### Python

```python
t = True # 'True' is highlighted
f = False # 'False' is highlighted
```

- ## `Regular Expressions`
  This color gets applied for regular expressions.

### Javascript

```javascript
const str = "ohhh hello world!";
const matchOs = str.match(/o/gi); // '/o/ig' gets highlighted
```

- ## `Operators`
  Operators such as `+`, `-`, `*`, `/`, and more get highlighted with this color.

### Javascript

```javascript
console.log(5 + (3 % 2)); // '.', '+', and '%' get highlighted
```

### Python

```python
if len("dog") == 3: # '==' gets highlighted
  print("dog is " + "3" + " characters long") # '+' gets highlighted in both cases
```

- ## `Square Brackets`
  This colors square brackets, usually the `[` and `]` characters.

### Javascript

```javascript
const arr = [0, 1, 2, 3, 4, 5]; // '[' and ']' get highlighted
```

### Python

```python
arr = [0, 1, 2, 3, 4, 5]; # '[' and ']' get highlighted
```

- ## `Angle Brackets`
  This colors angle brackets, usually the `<` and `>` characters, when they aren't being used as part of HTML and JSX tags or other token types.

### HTML

```html
<h1>Hi, World!</h1>
<!--'<' and '>' on both sides of each tag get highlighted-->
```

Congratulations on getting your syntax highlighting colors customized! Now let's learn how to further [improve the design of your theme](theme-design).
