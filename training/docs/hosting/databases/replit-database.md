---
sidebar_position: 2
---

# Replit Database

## What is Replit Database?

Replit Database is a simple, user-friendly key-value store inside of every Repl. No configuration is required; you can get started right away!

Read on for answers to Database FAQs, or jump right in and follow [this basic phone book tutorial](/tutorials/using-the-replit-database) where you'll learn how to perform the fundamental "CRUD" (Create, Read, Update, Delete) operations with Replit Database.

Here's a short video on how to use the Replit database, or read the text explanation below.

<iframe width="560" height="315" src="https://www.youtube.com/embed/Vx5Ci77K-ss" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Using Replit Database

Every Repl can access and interact with its own unique Replit Database. This database can be accessed from the library, and requires no configuration beyond import. Interacting with the Replit Database follows much of the same syntax and logic as creating and interacting with the key-value pairs of a Python dictionary.

### Importing the database

To access the Replit database we use `import db`:

```python
from replit import db
```

### Creating data

The Replit Database works a lot like a Python dictionary, so we can add data to our database by assigning values to keys using square bracket indexing:

```python
from replit import db

# Add a key and associated value to the database
db["key1"] = "value1"
```

Replit Database is able to handle different types of values like lists, dictionaries, integers, floats, NoneType, and strings:

```python
from replit import db

db["key1"] = "value1"
db["integer_1"] = 100
db["float_1"] = 9.99
db["my_list"] = [1,2,3]
db["my_dictionary"] = {"key_a": "value_a", "key_b": "value_b"}
db["none_key"] = None
```

Make use of 2D lists as a value to create table-like structures within your database:

```python
from replit import db

db["2D_key"] = [["id","name"],[1,"James"],[2,"Angel"]]

for column in db["2D_key"]:
    print(column)
```

**Output:**

```
ObservedList(value=["id","name"])
ObservedList(value=[1,"James"])
ObservedList(value=[2,"Angel"])
```

The `ObservedList` object you see in the output is a Replit Database object that acts like a Python list and can be indexed as such.

### Reading data

Read from your database by referencing the key of the value:

```python
from replit import db

# Create data in the database
db["key1"] = "value1"
db["my_list"] = [1,2,3]
db["my_dictionary"] = {"key_a": "value_a", "key_b": "value_b"}

# Access and print data from the database
print(db["key1"])
print(db["my_list"][0])
print(db["my_dictionary"]["key_a"])
```

**Output:**

```
value1
1
value_a
```

We can use the built-in Python dictionary method `.get()` to retrieve the value at the key passed in as an argument:

```python
from replit import db

# Create data for the database
db["float_1"] = 9.99

# Access the value of the data created by its key
print(db.get("float_1"))
```

We can loop through the keys stored in the database to get access to the values of those keys:

```python
from replit import db

# Create data for the database
db["key1"] = "value1"
db["my_list"] = [1,2,3]
db["my_dictionary"] = {"key_a": "value_a", "key_b": "value_b"}

# Access the keys from the database and print the values associated for key in db
  print(db.get(key))
```

The `.keys()` method returns a list of the keys in our database:

```python
from replit import db

# Create data for the database
db["key1"] = "value1"
db["my_list"] = [1,2,3]
db["my_dictionary"] = {"key_a": "value_a", "key_b": "value_b"}

# Print all the keys from the database
print(db.keys())
```

**Output:**

```
{'key1', 'my_list', 'my_dictionary', '2D_keys'}
```

The `.prefix()` method allows us to get the values of keys with only part of that key. This allows us to return multiple values for keys that share the same prefix:

```python
from replit import db

# Create data for the database
db["key1"] = "value1"
db["my_list"] = [1,2,3]
db["my_dictionary"] = {"key_a": "value_a", "key_b": "value_b"}

# Print all the keys from the database that have a prefix of "my"
print(db.prefix("my"))
```

**Output:**

```
('my_dictionary', 'my_list')
```

### Updating data

We can update values that are stored in our database by assigning new values to their associated key:

```python
from replit import db

# Create data with "float_1" as key and print
db["float_1"] = 9.99
print(db[“float_1”])

# Update data at "float_1" key and print
db[“float_1”] = 3.33
print(db[“float_1”])
```

**Output:**

```
9.99
3.33
```

We can also mutate numbers that are stored in our database:

```python
from replit import db

# Create data with "float_1" as key and print
db["float_1"] = 9.99

# Perform an operation on the data
db["float_1"] += 0.01

# Print result of operation
print(db["float_1"])
```

**Output:**

```
10.0
```

### Deleting data

We make use of the `del` keyword and square bracket indexing to delete key-value pairings from our database:

```python
from replit import db

# Create data for the database
db["float_1"] = 9.99

# Delete the data we added at the key "float_1"
del db["float_1"]
if "float_1" not in db:
	print("Value deleted successfully.")
```

**Output:**

```
Value deleted successfully.
```

### Summary

Overall, the Replit Database is a simple and useful database that allows us to easily and dynamically update our data. The features resembling the Python dictionary mean we can use the built-in Python dictionary functions to interact with our database.

## FAQs

### Where can I find my database?

When viewing your Repl, you'll find the Database icon toward the bottom of the sidebar – it's the second last icon. That’s Replit’s key-value database, built right into your Repl!

### How can I access my database?

To access Database, you can use a library or simple curl commands.

Replit provides official clients. Use one of these clients if your Repl is in one of these languages:

- [Python](https://pypi.org/project/replit/)
- [Node.js](https://www.npmjs.com/package/@replit/database)
- [Go](https://github.com/replit/database-go)

### How do I use my database?

When you click on the Database icon in the sidebar, you'll see some instructions. If your Repl is in a language that has an official Database client, you can quickly import it and start using Database by clicking on the "Insert" buttons.

If your language does not have a client, we provide some curl examples. They are found below, and are a useful reference if you wish to write your own Database client.

**Set**

```
curl $REPLIT_DB_URL -d '<key>=<value>'
```

If your key and value don't use any unsafe characters, you can use
an alternative version:

```
curl -XPOST $REPLIT_DB_URL/<key>=<value>
```

**Get**

```
curl $REPLIT_DB_URL/<key>
```

**Delete**

```
curl -XDELETE $REPLIT_DB_URL/<key>
```

`Delete` returns status code 204 if the key was deleted or 404 if the key did not exist.

**List**

```
curl $REPLIT_DB_URL --get -d 'prefix=<key>'
```

or

```
curl "$REPLIT_DB_URL?prefix=<key>"
```

The returned keys will be separated by newlines.

Listing also takes a query parameter: `encode=true`. If set, the returned keys will be URL encoded. This lets you safely handle keys that contain newlines.

### What is REPLIT_DB_URL?

This is the environment variable we have created with your Repl. It is the key that will allow you to access your database.

The clients listed above take care of using `REPLIT_DB_URL` for you, but you will need it if you want to write your own client or use a database from a language that doesn't yet have a client. Here are two examples:

Python:

```
import os
print(os.getenv("REPLIT_DB_URL"))
```

Node.js:

```
console.log(process.env.REPLIT_DB_URL)
```

`REPLIT_DB_URL` provides full access to your database. Therefore, you should take care not to expose it to the world or share it with people you don't trust.

The value of `REPLIT_DB_URL` changes from time to time, so we recommend that you don't copy it elsewhere. Subsequent reads by the same process will see the same value. We will restart your Repl if we need to change it after it has been read.

### What limits does Database have?

The limits are currently:

- 50 MB per database (sum of keys and values)
- 5,000 keys per database
- 1000 bytes per key
- 5 MB per value

There are rate limits that apply to all operations. You will receive an HTTP 429 if you exceed them. We recommend implementing an exponential backoff and retry to handle this case.

### How can I tell how much storage I'm using?

The Database sidebar shows you the number of keys in your database along with
the total storage occupied by your keys and values.

### Is my Database private?

Yes, each Database is private and isolated. Every Repl has its own database, and they are not shared among repls.

### How do I share a database across repls?

The easiest way to do this is to use one Repl as the primary database and have other repls connect to it via web hosting. [Here’s an example Repl in Python](https://replit.com/@util/Replit-Database-proxy).

Any requests sent to the above Repl will operate on its database, so sending
requests to it from other repls means that they all share the same information.
