---
title: Anyone Can Code - Week 6
author: Brittany Pirkle
date: 2020-12-3
cover: https://blog.repl.it/images/anyone-can-code/6.0.png
categories: projects
---
Here we are at week six and the web page is essentially done! That wasn’t so bad, was it? (Here is what I have done the last five weeks). The final step is to create a customized domain. This final step is optional because Repl.it does provide a domain name when a web page is created. However, for something more personalized, a customized domain name can be purchased. The cool part about this is when a domain name is purchased, you can call it whatever you want (as long as the name’s available), you own it, and no one else can use it.

We went over the definition of a domain earlier, but let’s quickly review. The domain is the name of a website. Sometimes, it is referred to as the URL or web address. For example, “repl.it” is the domain name for Replit, Inc. as this is what is typed into the search bar when looking for this website. Sometimes, the “www.” is a part of a domain, but in this case it is not. 

My current domain for my web page is: 

![Domain](https://blog.repl.it/images/anyone-can-code/6.1.png)

This is the domain that was given to me when I started my repl. However, I want to create a customized domain. There are many options, but Domain.com is the one of the best places to start.

It was so simple to purchase a domain. All I did was type in the domain name of my choice and a list of options was generated (or I was told the domain name was not available). I also could determine for how many years I wanted to own this domain name (anywhere from 1-5 years). Hint: domain.com will automatically renew the domain ownership when the determined time ends, so set a reminder to cancel auto-renewal if needed. 

![Pirkle Family](https://blog.repl.it/images/anyone-can-code/6.2.png)

This is what is shown if the domain is not available for purchase as it is already owned by someone else:

![unavailable](https://blog.repl.it/images/anyone-can-code/6.3.png)

Now let’s talk privacy. When purchasing a domain, there is the option to purchase the privacy protection as well. Normally websites need to list the name, address, and contact information of the owner, but you can purchase privacy and domain.com will hide your personal information and replace it with generic corporate contact info.

While we’re on the topic of privacy, there’s also SSL (secure sockets layer). You may have heard of it but I’ll explain how SSL encrypts requests to your website (just the basics!). We have all seen a movie where the smart hacker tracks down the hero on the run, right? Well, if data is sent to a website and it is not encrypted, then this could happen. Anyone “listening in” like the government, the nosy neighbors trying to tap into your wi-fi, or even the wireless company can tap into your network and steal credit card information, passwords, and more. Scary, huh? 

That is why website encryption is important. Go look up a domain. It doesn’t matter which one. Do you see the “https://” at the beginning of the web address? This identifies the website as encrypted; there is a special encryption process the website has automatically set up so hackers cannot snoop on you. All anyone would be able to see when looking at your requests is gibberish. All this to say, encryption is important for keeping private information, well, private. The lock and “https://” tells me I am on an encrypted website which gives peace of mind since I gave my credit card information to this website when purchasing my domain. 

![url](https://blog.repl.it/images/anyone-can-code/6.4.png)

Don’t worry though, Repl.it handles SSL for you automatically! If you want to read more about the technical details, this is a [good overview](https://letsencrypt.org/how-it-works/).

Let’s go back to the domain purchase. Once the domain has been purchased, it can be added as a customized domain in the repl. Here’s a [quick tutorial on Repl.it](https://docs.repl.it/repls/web-hosting), but I’ll also walk you through step-by-step.

Click on the pencil at the top right, add the purchased domain name, copy the auto-generated “CNAME” (I will talk about this in a minute) and press “next.” It will take a day or two for repl.it to reach the domain. 

![linking](https://blog.repl.it/images/anyone-can-code/6.5.png)


A CNAME (in case you are wondering...it stands for Canonical Name) is used to create an alias from one domain name to another which is exactly what I want to do here. Like many hosted services, repl.it provides the subdomain (the one I was given at the very start) and I can use a CNAME to point to my customized domain that I purchased. 

The last step, adding the CNAME to the domain registrar, needs to be done while the previous step is processing. I didn’t realize that at first and my website would not link because I didn’t do these steps simultaneously. So in this case, domain.com is my registrar. Find the section that allows for DNS records to be added on your domain registrar website. Add a new entry. The type is “CNAME.” The name or host name is the website domain purchased. It is best to type this in with “@.” as your host name. TTL should be “1 hour.” The “content” is the CNAME I copied from before. 

![Edit Dns](https://blog.repl.it/images/anyone-can-code/6.6.png)

Once the DNS record has been updated, Repl.it should be able to connect the two domains. Click “link domain” and tada….everything should be connected! 

![linking 2](https://blog.repl.it/images/anyone-can-code/6.7.png)

![linkedUrl](https://blog.repl.it/images/anyone-can-code/6.9.png)

Here is my final website link: https://pirklefamilyholiday2020.com 

You notice I do not have “www.” at the beginning. This is a totally optional part that you can add to your domain as a sub-domain if you wish. Just look on your domain registrar for how to add a sub-domain. Want to know more about why some websites use www and why some do not (like repl.it)? The [bottom line](https://www.sitepoint.com/domain-name-www-or-not/) is it is mostly a vanity thing. 

The lucky part for you is you don’t have to make my mistakes and can learn from what I did wrong in this process. After creating everything with a working link, I decided to add the “www” as a sub-domain. I asked for help from the experts at Replit and reached out to the tech support at domain.com. It took some configuring, trial and error, and extra research, but I finally figured out the best way to add “www” to my domain. 

I ended up starting over in a sense. I “unlinked domain” and then changed my domain name to have “www” at the start. 

![repl serve](https://blog.repl.it/images/anyone-can-code/6.8.png)

In the domain registrar, I deleted this CNAME 

![Edit Dns](https://blog.repl.it/images/anyone-can-code/6.6.png)

and created a new one with “www” as the name and the new CNAME that was created when I added “www” to the “content” name. 

![edit dns 2](https://blog.repl.it/images/anyone-can-code/6.10.png)

Now my holiday card is available at both https://www.pirklefamilyholiday20202.com and https://pirklefamilyholiday2020.com.

[Next week] (https://blog.repl.it/anyone-can-code-week7) is the final week of this project. I plan to share my pitfalls and wins and just reflect on the whole experience. Remember, Repl.it is FREE to use and easy to sign up. See you next week for the conclusion to my journey!
