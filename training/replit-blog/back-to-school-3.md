---
title: "Back to School 101: Mastery-Based Programming Tasks"
author: Sarah Strong
date: 2021-11-19T00:00:00.000Z
cover:  https://blog.replit.com/images/teams_edu/back-to-school-robot.jpg
categories: edu
---

*Part 3 of our back-to-school series.* 

# Mastery-Based Programming Tasks with Replit Teams for Education

## What are mastery-based tasks?

Mastery-based tasks evaluate whether students have mastered a small set of specific skills. These tasks are evaluated on a binary scale (e.g. complete/incomplete). If students have not demonstrated mastery on their first attempt, they keep trying until they demonstrate mastery.

## Why use mastery-based tasks?

Mastery-based tasks have [significant benefits](https://docs.google.com/document/d/1AoPmcMs9ITVZXLcUy9iCKQweXeV-qcq-RpN6loeCoJI/edit?usp=sharing) over tasks that are graded using a percentage mark or an achievement level.

- They promote learning over grades.
- They provide multiple opportunities for learning. If students don't get it the first time, they keep trying.
- They are less stressful for students. Students don't need to worry about perfection and can redo them if they didn't demonstrate mastery the first time.
- They help increase student confidence. They remind students that they can learn challenging concepts.
- They allow students to self-evaluate themselves before they submit. Their marks should not be a surprise to them if they check through their tasks before submitting them.
- They take less time to mark for teachers. Each task can take as little as 30 seconds to mark. 
- They are returned to students quicker so students can receive feedback soon after they submit them.

## How mastery-based tasks fit into course planning

- Mastery-based tasks can be used to fill in learning gaps from previous years. Students can focus on mastering the most important skills that they missed learning in previous years before moving on to new skills.
- Mastery-based tasks can be used to help new students catch up. Students can fast-track through what they missed by focusing on mastering the most important skills they need.
- Mastery-based tasks can be used as prerequisites for more challenging tasks such as self-directed/inquiry-based projects. This can ensure that they are ready for these projects.
- The course plan can be entirely made of mastery-based tasks. In this case, each student's final mark is determined by how many skills they mastered.

## How to use Replit Teams to create a mastery-based programming task

### Step 1 – Decide on the skills

Decide which skill(s) you want students to master. These skills should build on skills that students have already mastered. There shouldn't be too many skills evaluated at once. 

### Step 2 – Write the instructions

Write the instructions for the program. Before you finalize it, do a Google-check to ensure that the full solution cannot be easily found online. If the instructions are simple, I recommend putting a strange *twist* into it to reduce incidents of plagiarism and cheating.

### Step 3 – Create the tests

Create the I/O tests or unit tests. This will help students check to ensure their program works before they submit it and will help you quickly check to ensure the program does what it's supposed to do. Create enough tests to convince yourself that students who pass all the tests have a perfectly working program, assuming they didn't just hardcode the test cases. Include all the edge cases you can think of!

### Step 4 – Determine the criteria for a pass

Decide what criteria will be used to determine a pass. Creating a working program should be necessary but not sufficient towards demonstrating mastery. 

Here are some suggestions beyond having a working program:

- Including line comments and/or a separate write-up to show they understand exactly what their program does.
- Following programming conventions such as descriptive variable names, correct casing, and proper spacing. 
- Showing evidence of testing beyond the teacher-made I/O tests or unit tests.
- Citing sources so that you have a record of who students are getting help from and/or what online sources they are using beyond the resources you are providing them.

## Example – [Even Product](https://replit.com/@MissStrong/Even-Product)

### Step 1 – Decide on the skills

I choose *cumulative algorithms* as the skill for students to master. I will assign the task to students once they have mastered basic conditionals, basic list operations and methods, and basic *for* loops.

### Step 2 – Write the instructions

Write a Python function called `even_product()` that takes a list of integers called `int_list` and returns the product of all the even integers in the list. If there are no integers in the list, the function returns `0`. If there are no even integers but there is at least one odd integer, the function returns `1`. Do not import any modules.

### Step 3 – Create the tests

I will make unit tests to cover the following cases: an empty list, a list with one odd integer and no even integers, a list with one even integer and no odd integers, a list with only odd integers, a list with only even integers, a small list with mix of integers, a large list with mix of integers, a small list with duplicate integers, and a large list with duplicate intergers. I will also have a unit test that reads through their source code to ensure they didn't import any modules.

### Step 4 – Determine the criteria for a pass

To pass this task, students must demonstrate mastery by following the instructions carefully, passing the unit tests without reverse engineering them, using meaningful and self-explanatory variable names, follow Python conventions (e.g. snake_case for variable names and function names), including a line comment in the function to clarify or elaborate on the algorithm, and acknowledging all sources (including people who helped) in the attached document *sources.md*.

Here's the result:

![replit unit test](https://raw.githubusercontent.com/MissStrong/ICS3U_Semester_1_2021-2022/main/Images/Even_Product_Example.png)

## Giving feedback on mastery-based programming tasks

A simple "You pass!" or "Not quite... please retry." usually isn't very satisfying for a student. You should still provide descriptive feedback, and the [annotations feature on Replit](https://blog.replit.com/annotations-for-education) is a great way to do that. Here are some ideas:

**Pass** (mastery has been demonstrated)

- Praise the usefulness of the line comments.
- Praise descriptive variable names.
- Praise the code structure.
- Praise thorough testing.
- Prase the cleverness of an algorithm.

**Not-pass-yet** (mastery has not been demonstrated yet)

- Ask for elaboration on an unhelpful line comment.
- Remind them that variable names should be self-explanatory.
- If there are spacing issues, remind them to press the auto-format button before they submit.
- Point out a case that's missing.
- Point out a line that's causing an issue.

You can also give overall feedback using the [chat box](https://blog.replit.com/threads) in the bottom-right corner. This is a useful way to communicate whether the student has passed the task. If they didn't pass, you can also [unsubmit the project](https://docs.replit.com/teams/reviewing-submissions), which sends a notification to the student saying their project has been returned to them.

### About the Author
**Sarah Strong** is a high school math and computer science teacher in the Waterloo Region in Ontario, Canada and a Replit Teacher Ambassador. She has been teaching since 2015 and using Replit since 2019. Miss Strong currently teaches Grade 10 computer studies with P5.js, Grade 11 computer science with Python, and Grade 12 computer science with Java. [Find Miss Strong's curriculum in the Replit Curriculum Hub!](https://replit.com/curriculum/Intro-to-CS-with-Python-ICS3U)
