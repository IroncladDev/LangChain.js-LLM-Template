---
title: Building a web app with Nix (Because why not?)
author: Guillaume St-Pierre
date: 2021-07-16
categories: projects
---

Learning a new programming language can be a very difficult task. Where should you start? How do I improve my skills from "Hello, World!" to building complete applications? It helps to have a starter project. One of my favourites is building a web app. I have been learning the Nix package manager for a few weeks now - [starting with creating a dynamic version system](https://blog.replit.com/nix_dynamic_version) - and I think its the perfect time to write a web application with it (Even though I probably shouldn't).

But wait, isn't Nix a package manager and reproducible build system? Am I going to write an entire post on how to package a PHP app with Nix and run it? Well, yes and no. Nix is indeed a build system, but Nix packages are configured using a functional programming language (also named Nix) created specifically for the Nix package manager. Since Nix is a complete programming language, this means we can execute it without building a package thanks to the interpreter built into the Nix package manager itself. Clearly, Nix was not built for web development, but let's see how far we can take it.

## Hello, World!
In the long list of reasons why Nix was not created for building web applications, we have the reality that starting a web server that executes Nix code through Nix itself is not feasible at the moment. Nix is not the type of application that can be configured to wait for calls on some hostname/port and execute arbitrary code when a client connects. It is much easier to use something like `nix eval` through a more standard web server, so we'll do just that.

Let's start by creating a mandatory "Hello, World!" example with Nix. For this post, I have created all the code inside of a [Nix repl on replit.com](https://replit.com/@replitguillaume/NixWebApp). Feel free to follow along in that repl or to create your own.

Create a new repl using the **nix (beta)** language to get started, click on the three dots icon next to the Files header in the filetree and select "Show config files". Once the config files are visible, open the `replit.nix` file and replace `pkgs.cowsay` with `pkgs.python3`, we will need python later. Now that the repl is configured, create a `default.nix` file inside of a directory named `app` and write the following code in it.

```nix
# ./app/default.nix
{ }:
rec {
  get = ''
    <html>
      <head>
        <title>Nix web server - Home</title>
      </head>
      <body>
        <h1>Hello from Nix!</h1>
      </body>
    </html>
  '';
}
```

The code looks a lot like a standard derivation file. The basis of the `default.nix` file is a function (The signature for a Nix function is `arg: body`) that takes an attribute set as its single argument and should return __something_. Like most functional programming languages, Nix automatically uses the last statement of a function as the return value for that function. In fact, Nix only allows a single statement per function, purely functional. When executed, the code in this default file will return an attribute set with a single attribute: `get`. This get attribute contains our "Hello, World!" HTML code.

Now, how do we run this code through a web server? For this post, we will be using a python web server, but you could use anything you like, even bash. Here is the code for our web server, paste it in a file named `server.py` in the repl root directory (not in `./app`).

```python
# ./server.py
from http.server import BaseHTTPRequestHandler, HTTPServer
import subprocess

hostName = "0.0.0.0"
serverPort = 8080

class NixServer(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()

        command = 'nix eval --raw -f ./app get'

        # Run nix
        process = subprocess.Popen(command.split(), stdout=subprocess.PIPE)

        output, _ = process.communicate()
        self.wfile.write(output)

if __name__ == "__main__":        
    webServer = HTTPServer((hostName, serverPort), NixServer)
    print("Server started http://%s:%s" % (hostName, serverPort))

    try:
        webServer.serve_forever()
    except KeyboardInterrupt:
        pass

    webServer.server_close()
    print("Server stopped.")
```

The important part here is line 14: `command = 'nix eval --raw -f ./app get'`. Using the `subprocess` package, we trigger the `nix eval` command. The `--raw` option tells nix to return the result as an unquoted string, which makes things simpler for this server. We then use the `-f` option to tell Nix to use the `default.nix` file from the `app` directory. Finally, the last option tells nix which attribute from the returned attribute set to print. Combined, this will interpret our `./app/default.nix` file - thus executing the function in that file - and get the content of the `get` attribute, printing the HTML code as a raw string. Type `python ./server.py` in the repl console and wait for the web preview to appear, you should see the "Hello, World!" message displayed on screen.

## Adding a router
Displaying HTML is all fine and good, but most web applications include more than a single page of content.  Nix can't access anything from the web server or the environment, it is fully isolated. We need to find some way to know which URL the user accessed in our web app to display the correct page. We could use the python server to handle calling different Nix files based on which path the user access, but we want to do as much as possible directly in Nix. Instead of trying to frontload all the work to the python server, let's get the path from the url in python and give it to Nix as an argument. Update the `do_GET` method with this new code.

```python
# ./server.py
def do_GET(self):
	self.send_response(200)
	self.send_header("Content-type", "text/html")
	self.end_headers()
	
	# Update the command to add the --arg option
	command = f'nix eval --arg route "{self.path}" --raw -f ./app get'
	
	# Run nix
	process = subprocess.Popen(command.split(), stdout=subprocess.PIPE)
	
	output, _ = process.communicate()
	self.wfile.write(output)
```

We can extend the `nix eval` command to pass arguments to Nix using the `--arg` option. Here, we pass a `route` attribute as the value of the path from the web server. Let's see how we can use this in the `default.nix` file.

```nix
# ./app/default.nix
{ route ? "/" }:
let
  routes = {
    "/" = ''
      <html>
        <head>
          <title>Nix web server - Home</title>
        </head>
        <body>
          <h1>Hello from Nix!</h1>
          <ul>
            <li><a href="/nix">Nix info</a></li>
            <li><a href="/404">404</a></li>
          </ul>
        </body>
      </html>
    '';
    "/nix" = ''
      <html>
        <head>
          <title>Nix web server - Nix</title>
        </head>
        <body>
          <h1>Nix info</h1>
          <p>
            Nix is running on ${builtins.currentSystem}
          <p>
          </p>
            <i>With the caveat that a python web server is serving everything...</i>
          </p>
        </body>
      </html>
    '';
  };
in rec {
  get = if builtins.hasAttr route routes then routes."${route}" else ''
      <html>
        <head>
          <title>Nix web server - Not found</title>
        </head>
        <body>
          <h1>404 Page ${route} not found</h1>
        </body>
      </html>
  '';
}
```

Let's unpack this. On line 2, we can see the `route` argument added as a key from the attribute set. Anything given to the `--arg` option of the `nix eval` command will be added here using the format `--arg key value`. On line 3, we create a `let..in` block that defines another attribute set with our possible routes, each returning some HTML. Remember when I said that Nix function could only contain one statement? The `let..in` block is a special expression that allows us to bypass this limitation by defining variables in this block and passing them to whatever statement follows the `in`. For example:

```nix  
{ entry ? 0 }:  
let
	foo = "bar";
	bar = 1;
	file = builtins.readFile ./some-file.txt;
in if entry == 1 then foo else bar
```

This statement defines three variables and uses two of them in an `if` statement. `If` statements must always have a `then` block and a `else` block. No single line `if` or `else if` here. We can do a lot more with the `let` statement, but the one thing we cannot do is to trigger side effects. Nix is incredibly lazy and does not allow code that does something without assigning it to a variable. Furthermore, it will not interpret unused code. For example, the `file` variable above will not be interpreted and the `some-file.txt` file will not be read, even though we assign its content to a variable. The `?` on line 1 character defines the default value of an attribute in an attribute set. If the `entry` key is not set when the function is called, it will default to `0`. 

To go back to our own code, the core of the router is on line 36 were we use an `if` statement to set the value of the `get` attribute. The condition checks if the `routes` set from line 4 has a key equal to the passed route using `builtins.hasAttr`. If yes, it fetches the value for that attribute with the `dot` operator and returns the HTML. If not, it will instead return the content of a 404 page. This is code acts as a sort of `switch` statement and is one of the best way to implement an `else if` statement in Nix.

Restart the by typing CTRL+C then typing `python ./server.py`. You should now see the "Hello, World!" message printed on the web preview, with some links. Clicking on those links will route you to the pages we have defined.

## Adding an API
We now have a very nice set of web pages, and it's still fairly fast considering how we're running it. Yet, it's all static content. No web application would be complete without some sort of data management! It is time to take our app to the next level by adding a TODO API.

Let's start with some refactoring. Create a `./app/get.nix` file, we will move the code from `./app/default.nix` there with a few modifications.

```nix
# ./app/get.nix
{ }:
let
  routes = {
    "/" = ''
      <html>
        <head>
          <title>Nix web server - Home</title>
        </head>
        <body>
          <h1>Hello from Nix!</h1>
          <ul>
            <li><a href="/nix">Nix info</a></li>
            <li><a href="/404">404</a></li>
          </ul>
        </body>
      </html>
    '';
    "/nix" = ''
      <html>
        <head>
          <title>Nix web server - Nix</title>
        </head>
        <body>
          <h1>Nix info</h1>
          <p>
            Nix is running on ${builtins.currentSystem}
          <p>
          </p>
            <i>With the caveat that a python web server is serving everything...</i>
          </p>
        </body>
      </html>
    '';
  };

  getContent = route: if builtins.hasAttr route routes then routes."${route}" else ''
      <html>
        <head>
          <title>Nix web server - Not found</title>
        </head>
        <body>
          <h1>404 Page ${route} not found</h1>
        </body>
      </html>
  '';
in getContent
```

The main difference here compared to `default.nix` is that we return a function for the router rather than call it through an attribute set.

Going back to `default.nix`, we can update the code there to `import` this function and use it rather than have the router live in the default file. It makes our code a little easier to manage and will keep the file size small as we add more code. `import` is a special keyword that will execute the function in the given file (hence why we give it an attribute set as its second argument) and return its return value. In this case, `./get.nix` returns the `getContent` function and that's what we receive from `import`.

```
# ./app/default.nix
{ route ? "/" }:
let
  getContent = import ./get.nix {};
in rec {
  get = getContent route;
}
```

Now, let's add a `./app/post.nix` file and get started building a small API. We will be using the Replit database in this post, but feel free to use any database system you want.

```nix
# ./app/post.nix  
{ pkgs ? import <nixpkgs>{}, replit_db_url ? "" }:
let
  postApi = route: body: let
    setTodos = builtins.readFile (pkgs.runCommand "setTodos" {
      buildInputs = [ pkgs.cacert pkgs.curl ];
    } ''
      curl ${replit_db_url} -d 'todos=${body}' | tr -d '\n' > $out
    '');

    routes = {
      "/api/todos" = setTodos;
    };
  in if builtins.hasAttr route routes then routes."${route}" else ''
      Not found
  '';
in postApi
```

Let's go over this code. First, on line 2, we define our function with two attributes: the base nix packages and a `replit_db_url` string. We will get back to the `replit_db_url` attribute later. The nix packages include all the utility packages provided by Nix, which can be found in [their own repo](https://github.com/NixOS/nixpkgs). In the case of the `pkgs` attribute, it means Nix will automatically fetch all packages even if we do not pass it in the attribute set.

In the `let..in` block, we define our router function like in the `./app/get.nix` file with an added `body` parameter. The router only defines one route, which triggers a function called `setTodos` when the route is accessed. We define everything inside of the `postApi` function to make sure the `setTodos` function has access to the `body` attribute.

This `setTodos` function is where the magic happens. We use the `pkgs.runCommand` function to trigger a bash script on the server. This script will call the `curl` command and add data into the Replit database through its HTTP API. We then assign the result of this command, cleaned of all line breaks, to the magic `$out` variable. `runCommand` will write everything added to `$out` to its derivation file, which we then need to read using `builtins.readFile`. Since `runCommand` does not have anything installed by default, we also give it a few tools to make sure curl works.

Remember when I said that Nix does not allow side effects? `runCommand` is the best way to work around that. Nix will still not execute the bash script if the result is not read through a variable, but, as long as we make sure it is, we can trigger any side effect we want in the bash script.

We can use the `runCommand` code to write a `GET` version of this as well, let's return to `./app/get.nix` and add a few more lines of code.

```nix
# ./app/get.nix
{ pkgs ? import <nixpkgs>{}, replit_db_url ? "" }:
let
  getTodos = builtins.readFile (pkgs.runCommand "getTodos" {
      buildInputs = [ pkgs.cacert pkgs.curl ];
      dummy = builtins.currentTime;
    } ''
      curl ${replit_db_url}/todos | tr -d '\n' > $out
  '');

  routes = {
  	# Same routes, content cut for brevity
    ...
    "/api/todos" = getTodos;
  };

  getContent = ...; # Same code, content cut for brevity
in getContent
```

The code is very similar to the `./app/post.nix` code, but we fetch the todos data with curl rather than set them.

You may notice the `dummy = builtins.currentTime` line in `runCommand`, what's up with that? Nix is very good at avoiding unnecessary executions. It checks the content of the shell script and all the attributes given as the second parameter to determine if anything changes. If Nix decides the previous execution of `runCommand` has all the data needed already, it will not execute the bash script and instead resolve to the result of the previous execution. This was less of a problem with our `POST` code since Nix will always re-execute the code if its content changes (Which it will when the `POST` body data is different, unless the user adds the same TODO twice), but our `GET` code has no changing dependencies. We need to make sure to tell Nix to always rerun that script. The `dummy` attribute does so by creating a dependency to the current time, meaning it is sure to change between each execution.

Let's update the `./app/default.nix` file to connect those changes and expose our API endpoints.

```nix
# ./app/default.nix
{ pkgs ? import <nixpkgs>{}, route ? "/", body ? "{}", replit_db_url ? "" }:
let
  getContent = import ./get.nix { inherit pkgs; inherit replit_db_url; };
  postApi = import ./post.nix { inherit pkgs; inherit replit_db_url; };
in rec {
  get = getContent route;
  post = postApi route body;
}
```

We added a few attributes to the attribute set of our function and now expose a second attribute to our returned set for `POST` calls. We use the `inherit` keyword to pass attributes to our imported packages without having to type `pkgs = pkgs`, it is the equivalent of doing `{ foo: foo }` in an object in JavaScript for example. We need to also update the python web server to provide those as arguments, replace the `NixServer` class with the following code.

```python
# ./server.py
class NixServer(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()

        replit_db_url = os.getenv("REPLIT_DB_URL")

        command = f'nix eval --arg route "{self.path}" --arg replit_db_url "{replit_db_url}" --raw -f ./app get'

        # Run nix
        process = subprocess.Popen(command.split(), stdout=subprocess.PIPE)

        output, _ = process.communicate()
        self.wfile.write(output)

    def do_POST(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()

        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length)
        post_body = json.dumps(post_data.decode('utf-8'))
        replit_db_url = os.getenv("REPLIT_DB_URL")

        command = [
          "nix",
          "eval",
          "--arg",
          "route",
          f'"{self.path}"',
          "--arg",
          "body",
          f'{post_body}',
          "--arg",
          "replit_db_url",
          f'"{replit_db_url}"',
          "--raw",
          "-f",
          "./app",
          "post"
        ]

        # Run nix
        process = subprocess.Popen(command, stdout=subprocess.PIPE)

        output, _ = process.communicate()
        self.wfile.write(output)
```

The URL for the Replit database is available as an environment variable for all repls. We can fetch it and pass it to the `nix eval` command using the `--arg` option. We also added a `do_POST` method to the class to process `POST` calls with the `post` attribute returned from Nix. This method will pass all the attributes we expect, plus the decoded body from the `POST` call. Remember that `pkgs` has a default value that sets it to a link to all Nix packages, so we can omit it from our `nix eval` call.

Restart the server and try accessing these two endpoints using Curl or Postman with the repl URL (Available in the web preview). The `GET` endpoint should return the data saved by the `POST` endpoint!

## Adding a web app
We now have static content and a dynamic API, all that's left for our TODO app is to connect to the two together! For this application, I decided to go framework-less and use a web component. A web component is a custom HTML element managed through JavaScript. Think React, but without all its JSX fancyness.

Create a `./app/app.js` file and copy the following code in there:

```javascript
// ./app/app.js
class TodoList extends HTMLElement {
  constructor() {
    super();
    this.todos = null;
  }

  // Called when the component connects to the DOM. I.E. When it is rendered for the first time.
  connectedCallback() {
    this.render();
    
    this.fetchTodos();
  }

  fetchTodos() {
    fetch('/api/todos').then(data => data.json()).then(result => {
      this.todos = result;
      this.render();
    }).catch(() => {
      // This block exist to handle cases were the API returns an empty string (no data)
      this.todos = [];
      this.render();
    });
  }

  saveTodos(event) {
  	// Don't actually submit the form.
    event.preventDefault();

    const newTodo = this.querySelector("#todo-form #new-todo").value;

    fetch('/api/todos', {
      method: 'POST',
      body: JSON.stringify(this.todos.concat({ task: newTodo })),
    }).then(() => {
      this.fetchTodos();
    });
  }

  render() {
    if (!this.todos) {
      this.innerHTML = '<i>Loading...</i>';
      return;
    }

    this.innerHTML = `
      <div>
        <ul>
          ${this.todos.map(todo => `
            <li>
              ${todo.task}
            </li>
          `).join('')}
        </ul>
        <form id="todo-form">
          <input placeholder="Add a task" id="new-todo" name="new-todo" />
          <button type="submit">Add</button>
        </form>
      </div>
    `;

    this.querySelector("#todo-form").addEventListener('submit', this.saveTodos.bind(this));
  }
}
    
customElements.define('todo-list', TodoList);
```

I won't go into too much details about web components in this article. What's important here is that `connectedCallback` is triggered when the component is picked up by the browser and rendered on screen. We tell that component to render a loading indicator and start fetching todos using our `GET` API from the previous section. Once fetched, we rerender and display the list of todos plus a small form instead of the loading indicator. Creating a todo using the form will call the `POST` API endpoint, then trigger a refetch of the `GET` endpoint, and finally a rerender.

Let's update the `routes`set of our `./app/get.nix` file to use this component, replace the first route with the following code.

```nix  
"/" = ''
  <html>
    <head>
      <title>Nix web server - Home</title>
    </head>
    <body>
      <h1>Hello from Nix!</h1>
      <ul>
        <li><a href="/todos">Todo list page</a></li>
        <li><a href="/nix">Nix info</a></li>
      </ul>
    </body>
  </html>
'';
"/todos" = ''
  <html>
    <head>
      <title>Nix web server - Todos</title>
    </head>
    <body>
      <h1>Listing todos</h1>
      <todo-list></todo-list>
      <script>
        ${builtins.readFile ./app.js}
      </script>
    </body>
  </html>
'';
```

We added a link to the new `/todos` route in our home page. This `/todos` route adds the web component we created and copies the JavaScript code into a script tag by reading the JavaScript file. Nix knows to copy unquoted paths like these to its store and can access our JavaScript file no problem.

Refresh the web preview (no need to reset the server since we didn't change any of the python code) and you should see the new link. Clicking on the todo list link will trigger the web component code and show you an empty list of todos. Try adding a new todo using the form, you'll see the list refreshing after around 5 seconds. Be patient, it is _very_ slow.

## Conclusion
What did we learn today? We learned the hard way that Nix isn't suited to web development - which was to be expected - but also that Nix can be very slow for what seems to be fairly basic operations. Nix is a build system first, while it has many optimizations (Which we had to work around) to make things faster, it's not made to provide the type of performance web applications need. The `runCommand` function creates a new build derivation that configures a _lot_ of things and creates new processes. It's meant to take some time as Nix figures out what it needs to do. `builtins.readFile` adds another layer of complexity as Nix creates yet another process to fetch and read the file.

But what about `fetchUrl`? Could it be faster and simpler than `runCommand`? Unfortunately, `fetchUrl` uses a bash script and curl behind the scene, which ends up being very similar in structure and performance to our `runCommand` setup, but without our `dummy` attribute. This leads to caching issues where adding more than one todo won't change the result of the `GET` call. `fetchUrl` is meant to fetch and unpack archives for using them in build processes, not make `GET`/`POST` calls to an HTTP API.

I think there might be some way to hack Nix a little bit more by making use of the `runCommand` cache we had to work around with the `dummy` attribute. There might be some way to use that to our advantage to always return the latest version of the saved data when calling the `GET` endpoint unless a `POST` call has happened. This could lead to a slow first `GET` call, but instant subsequent calls. Until a todo is added (Maybe we'll explore that in a part 2!).

What I love about the Nix language is how simple it is. There is very little bloat and the core of the language can be learned really quickly (we only missed the `with` keyword in this post, we covered everything else!). There is definitely some potential for writing applications with this language. This was a fun adventure and a very good way to learn the Nix language, but it seems my dream of a Nix powered web application will have to wait until an interpreter makes its way on the Internets.