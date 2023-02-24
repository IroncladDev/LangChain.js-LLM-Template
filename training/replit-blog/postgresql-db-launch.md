---
title: PostgreSQL Database Preview Now Available On Replit
author: Lincoln Bergeson, Xiaoyi Chen
date: 2023-01-23T17:15:00Z
cover: https://blog.replit.com/images/postgres-launch/Postgres_Header_image.png
categories: product
---
![Header Image](https://blog.replit.com/images/postgres-launch/Postgres_Header_image.png)

Databases and web apps go together like peanut butter and jelly. In a word, they're inseparable. And despite all the amazing innovations in NoSQL data stores, often a good old relational database is the most reliable tool for the job.

We want to make it completely seamless to develop applications that need databases on Replit. Starting today, you can create and instantly begin to use PostgreSQL databases from within the Replit workspace.

Here's how you use it. First, click the PostgreSQL icon in the Tools pane on the lower left hand side of the workspace.

![DB_Image_1](https://blog.replit.com/images/postgres-launch/DB_Image_1.png)

Or, you can open a new tab and select PostgreSQL from there.

![DB_Image_2](https://blog.replit.com/images/postgres-launch/DB_Image_2.png)

From this pane, you can provision a PostgreSQL database. Compared to most SQL offerings which can take several minutes, your database on Replit will be available within just a few seconds.

![DB_Image_3](https://blog.replit.com/images/postgres-launch/DB_Image_3.png)

For now we are only offering one size of database: 100 cycles per day for 10GB. The database has 1 dedicated CPU and 4 GB of RAM to process your queries. 

Once you've created the database, you can start using it! The `DATABASE_URL` environment variable will have your connection string. To connect to your database with NodeJS using the `pg` package, you might use a code snippet like this:

```js
const { Client } = require('pg')
const client = new Client(process.env.DATABASE_URL)
 
client.connect()
 
client.query('SELECT $1::text as message', ['Hello world!'], (err, res) => {
  console.log(err ? err.stack : res.rows[0].message) // Hello World!
  client.end()
})
```

We've also created a SQL explorer that you can use to write SQL statements and see the contents of your database.

![Recap Header Image](https://blog.replit.com/images/postgres-launch/DB_SQL_Explorer.mp4)

If you've purchased Ghostwriter, AI-based code completion for SQL will be available in the statement editor.

For more information on your PostgreSQL database, check out:
- [The docs](https://docs.replit.com/neon-database/intro)
- [Learn how to use the database](https://replit.com/learn/intro-to-postgresql)
- [Try building a Discord Bot with sentiment analysis](https://replit.com/@DavidAtReplit/Discord-Bot-for-Sentiment-Analysis)

Under the hood, this product is powered by our friends at [Neon](https://neon.tech/) who have created a lightning-fast serverless database. The database will go to sleep after 5 minutes of inactivity. Most clients should handle the reconnection seamlessly.

In the near future we plan to offer much more flexibility and customizability in your database options. You'll be able to choose variable amounts of storage, different compute configurations, and even usage-based pricing, where you only pay for what you actually use.

If you experience any issues with your database at all, please post in [the forum](https://ask.replit.com/) and we will get back to you as quickly as possible. Let us know what you think!