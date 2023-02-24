# Getting repl metadata

In some cases, it's useful to automatically retrieve metadata about a Repl from within that Repl. Your Repl's **environment variables** are pre-populated with some data that you can use. However, please avoid printing out the entirety of your Repl's environment variables in a public Repl, as it will expose any secrets you've added.

To access this data, first retrieve your Repl's environment variables.

#### Retrieve environment variables in Node.js

```js
console.log(process.env);
```

#### Retrieve environment variables in Python

```python
import os

print(os.environ)
```

#### Retrieve environment variables in Rust

```rust
use std::env;

fn main() {
    for (key, value) in env::vars() {
        println!("{}: {}", key, value);
    }
}
```

To access a **single** environment variable from within a Repl, use the following examples:

#### Access a single environment variable in Node.js:

```js
const variable = process.env.REPL_SLUG;
console.log(variable);
```

#### Access a single environment variable in Python:

```python
import os

variable = os.environ.get('REPL_SLUG')
print(variable)
```

#### Access a single environment variable in Rust:

```rust
use std::env;

fn main() {
    let variable = env::var("REPL_SLUG").unwrap();
    println!("{}", variable);
}
```

Here is a table showing the most useful metadata accessible inside your Repl:

| key             | description                                                                                                                                                        |
| --------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `REPL_OWNER`    | The username of the owner of the Repl. If your Repl is text-based and has no webserver, `REPL_OWNER` will reflect the value of the current user accessing the Repl |
| `REPLIT_DB_URL` | The URL of your key-value Replit database                                                                                                                          |
| `REPL_ID`       | The unique UUID string of your Repl                                                                                                                                |
| `HOME`          | The home path of your Repl                                                                                                                                         |
| `system`        | The system name of your Repl                                                                                                                                       |
| `LANG`          | Text language and encoding                                                                                                                                         |
| `REPL_IMAGE`    | The docker image that corresponds to your Repl                                                                                                                     |
| `REPL_LANGUAGE` | The language of your Repl                                                                                                                                          |
| `REPL_PUBKEYS`  | A stringified JSON object containing different public api keys                                                                                                     |
| `REPL_SLUG`     | The slug of your Repl                                                                                                                                              |
| `PRYBAR_FILE`   | The main/entrypoint file of your Repl                                                                                                                              |
