---
title: "Python for Beginners: Interpreting My Amazon Spending with a Repl, Part Three"
author: Brittany Pirkle
date: 2022-
categories: edu
---

I know you have been on the edge of your seats wondering why in the world a repl is better than a spreadsheet to calculate so much data?! In case you need a refresher, I analyzed my Amazon spending for 2021 using a [Python repl](https://blog.replit.com/python-for-beginners) and with just a few lines of code I could discern a variety of answers about my spending. Not only did I find out that I am spending *way* too much money on Amazon, but I also came to the conclusion of *why* a repl is better than a spreadsheet (read to the bottom to find out).

Just to recap, I used Pandas as the [package manager](https://docs.replit.com/programming-ide/installing-packages) to easily import a csv file and analyze the data on a myriad of data points. The last component to evaluate is spending over time by analyzing how much money was spent on a given day through a bar graph. The bar graph will show the amount spent and the corresponding order date. First, the order dates need to be converted (from my csv) into a format that Python can recognize. Once again, Pandas makes this easy.

First, write `.pd.to_datetime()` and then add the column to be modified. In this case, 'order date.'


'Order Date' is now in a format compatible with Python. However, I noticed that the time stamp was also included. For this purpose, I do not want the timestamp. I need to convert ‘datetime’ to ‘date' using `.dt.date`.


Next is writing the code that creates the bar graph with a simple `df.plot.bar` and setting the x (horizontal) and y (vertical) coordinates. The ‘x’ is the date the order was placed and ‘y’ is the amount spent. I also want to ensure I have the rotation set to 90.

`df.plot.bar(x='Order Date', y='Item Total', rot=90,)`

However, the graph is very small and essentially illegible. This can be fixed by adding a figure size that will adjust the width and height of the graph with `figsize()`.  I started with 10 as the width and 20 as the height and then did some trial and error to determine `figsize=(14,30)` was the best size for this data set.



The final step to add more organization is to group the orders that were purchased on the same day into one data point. Remember, the goal is to map how much money was spent each *day*. Once again, Pandas is perfect for this with the built-in function: `df.groupby()`. I want to group all data from the ‘Order Date’ into a single column on the bar graph. To do this, I find the sum of the `Item Total` for each `Order Date`. For example, if I purchased three items on August 23, I can group all three item totals into a single value to display on the graph. I am grouping the data by ‘Order Date’ so I will write `df.groupby('Order Date')`. Next, find the sum of the ‘Item Total’ by writing `.sum()["Item Total"]`. Of course, add a variable. ‘Daily_Orders.df’ works fine.



With the dates correctly reflected without the timestamp and the orders grouped by day, the graph can be re-created by changing `df.plot.bar` to `daily_orders.plot.bar` to depict a much cleaner graph that can be used for data interpretation.

## Lessons Learned:

At the beginning of this project, I posed the question that most people are probably thinking. **“That seems like too much work. Why not just use a spreadsheet?”** 

Here is why I think a repl is a better option for data analysis:


- **Coding is more powerful**: Excel formulas can easily become overwhelming and convoluted. Most of the time, I am not sure what the formulas mean and am mindlessly typing numbers and symbols. With coding, I can see the patterns and easily decipher the data as “if/then” statements, instead of random formulas. I actually know what I am looking at and what the code is expected to do to the data set.

- **Coding is transferable**: Now that I have created this project, I can use the code as a template for other data sets. And of course, the beauty of Replit allows me to fork this repl. I can easily upload a different .csv file and now this code can be transferred to the new data set. I could analyze my grocery spending or water bill with little changes to the code.

- **Coding is better for multiple data sets**: There is no need to copy/paste and merge various spreadsheets into one or have multiple tabs and data sheets. Information can easily get misconstrued, omitted, or duplicated. Imagine the headache that comes with trying to merge multiple data sets into one graph?!

- **Coding is quicker**. Obviously, the first time around takes longer, but now I can easily use this same process with other data.

- **Coding is more intuitive**: There is way less opportunity for human error with a repl. If there is a syntax error (caused by my human error), I am alerted. If my code is written incorrectly, my repl will not run. Yes, you can also get error messages with formulas within a spreadsheet, but it is much more difficult to pinpoint where the error is and what is wrong. 

- **Coding is way more fun**: Have you had flashbacks to computer class in school where you had to merge data, use formulas, create graphs, etc. and it all seemed so confusing, dull, and pointless?! Replit takes away the confusion and with each new line of code you can easily track your progress. And isn't it much more fun to brag about lines of code you wrote instead of a boring spreadsheet. 


What other projects would you like to see to help you develop coding superpowers?



