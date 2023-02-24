---
sidebar_position: 1
---

# PostgreSQL on Replit

## What is PostgreSQL?

PostgreSQL is a powerful, open source object-relational database system that is widely used in web applications and other software development projects. We use PostgreSQL version 15 in our integration, which allows you to easily create a production-ready PostgreSQL database directly within Replit. You can run queries and connect to the database using our provided environment variables. For more information on PostgreSQL, visit the [official documentation](https://www.postgresql.org/docs/).

## Why use PostgreSQL?

<ol>
  <li>
    <b>Simplicity:</b> With our integration, you can easily set up a PostgreSQL
    database without having to install any additional software or configure any
    settings. All you need to do is click a button and you'll have a
    fully-functional database ready to go.
  </li>
  <li>
    <b>Seamless integration:</b> Our integration is designed to work seamlessly
    with Replit, so you can easily access your database and run queries within
    the Replit environment or within your code with minimal configuration.
  </li>
  <li>
    <b>Production-ready:</b> The database created with our integration is
    production-ready, so you can use it for real-world applications and
    projects.
  </li>
  <li>
    <b>Convenience:</b> With our provided environment variables, you can easily
    connect to the database from your code, without having to worry about
    setting up the connection manually. This saves you time and makes it easier
    to get your project up and running.
  </li>
  <li>
    <b>Neon documentation:</b> Provides guides on how to connect various
    frameworks, such as Django, to your PostgreSQL database in the{' '}
    <a href="https://neon.tech/docs/connect/">neon documentation</a>.
  </li>
  <li>
    <b>Connection pooling:</b> If you need to enable connection pooling for any
    reason, you can contact us and we'll do it manually for you. More
    information on connection pooling can be found in the{' '}
    <a href="https://neon.tech/docs/connect/connection-pooling/">
      neon documentation
    </a>
    .
  </li>
  <li>
    <b>Compute lifecycle:</b> The database will go to sleep after 5 minutes of
    no queries, so you may experience disconnects. More information on the
    compute lifecycle can be found in the{' '}
    <a href="https://neon.tech/docs/introduction/compute-lifecycle/">
      Neon documentation
    </a>
    .
  </li>
</ol>

## Setup

<ol>
  <li>Open a new tab in Replit and type "PostgreSQL"</li>
  <img
    src="https://replit-docs-images.util.repl.co/images/hosting/databases/pgopentab.png"
    alt="Open a new tab in Replit and type PostgreSQL"
  />
  <li>
    In the "PostgreSQL" panel, click "Buy Cycles & create a DB" or "Use Cycles
    to create a DB"
  </li>
  <img
    src="https://replit-docs-images.util.repl.co/images/hosting/databases/pgbuy.png"
    alt="In the PostgreSQL panel, click Buy Cycles & create a DB or Use Cycles to create a DB"
  />
  <li>
    Expand the "Database env variable" section and copy the variable name
    (DATABASE_URL), for use later
  </li>
  <img
    src="https://replit-docs-images.util.repl.co/images/hosting/databases/pgvar.png"
    alt="Expand the Database env variable section and copy the variable name (DATABASE_URL), for use later"
  />
</ol>

## SQL Explorer

We provide a SQL explorer that you can use to create tables and manage your database. And if you have purchased Ghostwriter, you can use that within the SQL explorer to help you write queries.

## Usage (NodeJS)

### Preparation

<!-- 1. Use the Packager to install `knex` and `pg` -->

1. <span>
     Use the Packager to install <code>knex</code> and <code>pg</code>
   </span>
2. <span>Connect to the DB with Knex using the URL secret</span>

   ```js
   const knex = require("knex")({
     // We are using PostgreSQL
     client: "postgres",
     // Use the secret we provide to connect to the Database
     connection: process.env.DATABASE_URL,

     // Optionally, you can use connection pools to increase query performance
     pool: { min: 0, max: 80 },
   });
   ```

3. <span>
     Use an Async IIFE so we can use <code>await</code>
   </span>

   ```js
   (async () => {
     // Leave this empty for now
   })();
   ```

### Code

1. <span>Create a table</span>

   ```js
   await knex.schema.createTable("users", (table) => {
     table.increments("id");
     table.string("username");
     table.integer("points");
   });
   ```

2. <span>Insert a row</span>

   ```js
   await knex("users").insert({
     username: "alice",
     points: 0,
   });
   ```

3. <span>Update the row</span>

   ```js
   await knex("users")
     .where("username", "alice")
     .update({
       points: knex.raw("points + 1"),
     });
   ```

4. <span>Get the row</span>

   ````js
   const user = await knex('users')
       .where('username', 'alice')
       .first();
       ```
   ````

5. <span>Print the row to the console</span>

   ```js
   console.log(user);
   ```

6. <span>Delete the row</span>

   ```js
   await knex("users").where("username", "alice").delete();
   ```

### Final Code

```js
// Connect to the Database
const knex = require("knex")({
  // We are using PostgreSQL
  client: "postgres",
  // Use the secret we provide to connect to the Database
  connection: process.env.DATABASE_URL,

  // Optionally, you can use connection pools to increase query performance
  pool: { min: 0, max: 80 },
});

(async () => {
  // Create a demo table called "users"
  await knex.schema.createTable("users", (table) => {
    table.increments("id");
    table.string("username");
    table.integer("points");
  });

  // Add a demo user to the table with 0 points
  await knex("users").insert({
    username: "alice",
    points: 0,
  });

  // Increment the points by 1
  await knex("users")
    .where("username", "alice")
    .update({
      points: knex.raw("points + 1"),
    });

  // Get the user
  const user = await knex("users").where("username", "alice").first();

  // Print the user
  console.log(user);

  // Delete the user
  await knex("users").where("username", "alice").delete();
})();
```

## Usage (Python)

### Preparation

1. <span>
     Use the Packager to install <code>psycopg2</code>
   </span>
2. <span>
     Connect to the DB with <code>psycopg2</code> using the URL secret
   </span>

   ```py
   import psycopg2.pool

   # Create a connection pool with a min_size of 0 and a max_size of 80
   pool = psycopg2.pool.SimpleConnectionPool(0, 80, process.env.DATABASE_URL)

   # Get a connection from the pool
   conn = pool.getconn()

   # Create a cursor using the connection
   cur = conn.cursor()

   # Do your database operations using the cursor
   # <Your code goes here>

   # Close the cursor and return the connection to the pool
   cur.close()
   pool.putconn(conn)

   # When you are done using the pool, close it to release the resources
   pool.closeall()
   ```

### Code

1. <span>Create a table</span>

   ```py
   cur.execute(
       """
       CREATE TABLE users (
           id SERIAL PRIMARY KEY,
           username VARCHAR(255),
           points INTEGER
       )
       """
   )
   ```

2. <span>Insert a row</span>

   ```py
   cur.execute(
       """
       INSERT INTO users (username, points)
       VALUES (%s, %s)
       """,
       ('alice', 0)
   )
   ```

3. <span>Update the row</span>

   ```py
   cur.execute(
       """
       UPDATE users
       SET points = points + 1
       WHERE username = %s
       """,
       ('alice',)
   )
   ```

4. <span>Get the row</span>

   ```py
   cur.execute(
       """
       SELECT *
       FROM users
       WHERE username = %s
       """,
       ('alice',)
   )
   user = cur.fetchone()
   ```

5. <span>Print the row to the console</span>

   ```py
   print(user)
   ```

6. <span>Delete the row</span>

   ```py
   cur.execute(
       """
       DELETE FROM users
       WHERE username = %s
       """,
       ('alice',)
   )
   ```

### Final Code

```py
import psycopg2.pool

# Create a connection pool with a min_size of 0 and a max_size of 80
pool = psycopg2.pool.SimpleConnectionPool(0, 80, process.env.DATABASE_URL)

# Get a connection from the pool
conn = pool.getconn()

# Create a cursor using the connection
cur = conn.cursor()

# Do your database operations using the cursor

# Create a demo table called "users"
cur.execute(
    """
    CREATE TABLE users (
        id SERIAL PRIMARY KEY,
        username VARCHAR(255),
        points INTEGER
    )
    """
)

# Add a demo user to the table with 0 points
cur.execute(
    """
    INSERT INTO users (username, points)
    VALUES (%s, %s)
    """,
    ('alice', 0)
)

# Increment the points by 1
cur.execute(
    """
    UPDATE users
    SET points = points + 1
    WHERE username = %s
    """,
    ('alice',)
)

# Get the user
cur.execute(
    """
    SELECT *
    FROM users
    WHERE username = %s
    """,
    ('alice',)
)

user = cur.fetchone()

# Print the user
print(user)

# Delete the user
cur.execute(
    """
    DELETE FROM users
    WHERE username = %s
    """,
    ('alice',)
)

# Close the cursor and return the connection to the pool
cur.close()
pool.putconn(conn)

# When you are done using the pool, close it to release the resources
pool.closeall()
```
