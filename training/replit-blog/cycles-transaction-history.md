---
title: Redesigning Cycles Transaction History
author: Mathurah Ravigulan
date: 2022-12-23
categories: eng,product
cover: https://blog.replit.com/images/cycles_transaction/banner.png
profiles: replit-mathu
---

![Cycles Cover Image](https://blog.replit.com/images/cycles_transaction/banner.png)


Earlier this year we introduced [Cycles](https://docs.replit.com/cycles/about-cycles) to the platform, a virtual token that can be earned or purchased to add compute power and functionality for your Repls. 

Hundreds of thousands of cycles transactions have been made to date. And now more Replit community members are able to earn cycles of their own through bounties!


In the past, Replit transactions looked something like this: 
![image](https://blog.replit.com/images/cycles_transaction/old_transactions.png)


With this view, although simple, it’s hard to know where exactly your cycles are going, whether it's spending on powerups, purchasing, or sending to other replit community members via tips and bounties. There’s also nothing actionable you can do with this information. 

Our initial focus for the first iteration was purely around cycles functionalty. Now there are even more things you can use cycles for, we're revisiting the experience to focus on helping you find information on where you spent or earned cycles on Replit!

As a goal of my internship, I wanted to work on a more complex engineering problem and learn more about the cycles team, which is why I took on this project!


The goals for this project are to: 
- Make the cycles transaction page extensible for future cycles products we build on replit
- Surface transaction IDs (so it's easy to see that each transaction is unique)
- Group transactions by categories 
- Surface details about what the transaction is

The new page looks like this:
![gif](https://blog.replit.com/images/cycles_transaction/newpage.gif)


So, how did we get there? 

I broke my project down into 3 phases: 
1. Talking to replit community members to understand what they would like to see on the transaction history page.
2. Developing an initial design & working with our awesome designer Larry to translate the requirements I gathered into designs.
3. Working on the engineering implementation from database design to front-end implemenation.

Let's dig into understanding how cycles and transactions work on replit: 

We have a table to represent transactions, users, balances, and wallets for interactions that require holding cycles in Google Cloud Spanner. The transactions table in this system is a source of truth for all transactions made on replit. 

In Postgres, we have tables for each type of purchase you can make on replit, for example a table for powerups, bounties, tips, and more. These tables hold more contextual information on the detail of the transaction itself. 

Outside of these spanner tables, we use postgres tables to hold more contextual information about the transactions itself. For example, bouties, powerups, tips all have their own tables that hold more details. 
![image](https://blog.replit.com/images/cycles_transaction/table_1.png)

Let's go through an example. What happens when you purchase a power up on Replit?
1. First it'll create a Repl order that indicates the type of power-up. For example, always on. 
2. Then it'll link this Repl order to another transactions table in postgres.
3. In the transactions table, it creates a transaction id that's linked to the transactions table in spanner. 

![image](https://blog.replit.com/images/cycles_transaction/table_2.png)

One of the main engineering challenges was that the Spanner transactions table is too simple. It was sufficient to provide data for the current view, but if we want Replit community members to be able to see more details on their transaction, it will need to use the transaction ID to search all the possible tables to find this information which will be an expensive compute. 

As part of the project, I introduced a new column to the spanner table called Metadata. Note: this change will only be rolled out to new transactions going forward!

Let's see how the `metadata` would look like for an example `boost` transaction. 

```js
metadata: {
  system: 'web-postgres'
  relation: 'repl_order'
  power_up_type: 'boost'
  id:
}
```
The metadata will act as a reference to contextual data within the transactions table, making it easier to find information about Cycles Transactions. 

- `system`: refers to the system the data lives on, whether it's postgres or anything else.
- `relation`: corresponds to the postgres table where the transaction is from.
- `id`: will be used in the future to query additional data from the table such as Repls/bounty names.

Using this metadata, I was able to query and categorize transactions based on their table relations as you can see in the view. 

The new cycles transaction history will be rolled out to explorers today and will slowly rollout to everyone next week. Start making new transactions on replit to try it out at https://replit.com/cycles. 

This is only the start of the new Cycles Transaction History and I'm excited for the Replit team to continue building upon more features for this!

A few features I'm looking forward to the team adding: 
- Connecting the Repls you purchased your powerups for. This way you can easily see which Repl you spent it on
- Ability to see who you got tips from and include the link to their profile in your transaction
- Filtering by transaction categories and ability to view transactions in a specific date range

Overall this was a really fun internship and I learned a lot! Thanks so much Replit for the opportunity :) 