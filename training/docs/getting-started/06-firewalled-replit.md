# Firewalled Replit

Replit offers an alternative domain, [firewalledreplit.com](https://firewalledreplit.com), that provides a more restricted user experience. By logging into Replit from this domain rather than our main domain, the following restrictions are applied:

- A firewall is used to prevent repls from accessing the Internet (apart from a small number of software package repositories).
- Replit’s community and search features are hidden.

No registration is needed to use firewalledreplit.com, and there is no need to migrate your user account or repls to the new domain. Users are free to switch between using [firewalledreplit.com](https://firewalledreplit.com) and our original domain [replit.com](https://replit.com) at any time.

Most repls will function normally on firewalledreplit.com, but those that depend on being able to access the external internet might not function as expected.

For IT administrators who may wish to enforce the use of firewalledreplit.com rather than replit.com, [this document]/teams-edu/it-administrators-toolkit) provides guidance on how that can be done.

_Read more about this change at [our blog post](https://blog.replit.com/computing-superpower-at-school). Also, see our [commitment to user safety.](https://replit-docs-images.util.repl.co/images/teamsForEducation/Our%20Commitment%20to%20User%20Safety.pdf)_

## FAQ

**What is different about firewalledreplit.com?**

The new domain firewalledreplit.com is more strictly filtered to eliminate any avenue for students to create web proxies and, therefore, bypass school filters and reach inappropriate content. Additionally, there will be no community, search, or spotlight features. Students will not be able to view any public repls that are shared within the broader Replit community. They can only see projects and repls that are created inside the Teams for Education organization.

**Why is this change happening?**

We take trust and safety seriously. While we want students to have the opportunity to experience the full power of Replit and coding, some schools have asked for stronger guarantees that their students will not be able to access adult or inappropriate content. We’ve listened, and that’s why we’re providing firewalledreplit.com as a new option for those schools.

**Will I still be able to access the same Teams for Education features?**

Yes. There will be no change to the education-focused features.

**Can my students still collaborate with other students that are a part of our organization?**

Yes, [students can still work with other students]/teams-edu/group-projects) who are a part of the same project (as organized by the teacher). Students will NOT be able to view community repls or comments and can only interact with other students that are a part of their team.

**How is this solution different from blocking repl.co?**

Previously, we advised schools that wanted to prevent students from accessing proxies to block the repl.co domain. However, this had the side-effect of also preventing them from coding functional web applications on Replit. In contrast, the new domain firewalledreplit.com allows students to work on web applications that are fully functional except that they cannot access the broader Internet. Additionally, firewalledreplit.com hides community sharing and commenting features so that students can focus on coding.

**How do I know students will not be able to access proxies or bypass school filters on firewalledreplit.com too?**

Every method that students have used in the past to bypass school filters relies on repls being able to access the Internet. On firewalledreplit.com, repls are completely blocked from accessing the Internet, apart from repositories of well-known, trusted software libraries that are needed for coding. These include pypi.org for Python, npmjs.org for NodeJS and maven.org for Java. This blocking is enforced deep within our network, and there is no way for students to bypass it while using the firewalledreplit.com domain.

**What can I do if students are still accessing replit.com and I want to prevent this?**

After switching your students over to use firewalledreplit.com, you do have the option of blocking replit.com and repl.co to fully ensure students cannot bypass the new domain and the additional safeguards that it provides. However, blocking these domains will also eliminate the ability for students to see trending/popular repls posted in the community which can act as inspiration and creativity for students.

**Can I ask for additional websites from the Internet to be permitted for access from firewalledreplit.com?**

Sorry, but to ensure the security of firewalledreplit.com, we do not have plans to allow additional websites to be accessed through firewalledreplit.com. Only access to a limited number of well-known software library repositories will be allowed.

**Will this limit the languages I can use or access?**

No. You can still create projects in the same languages as replit.com.

**Will my speed be affected?**

No. You will still have access to the same dedicated cluster for Teams for Education that has more speed and storage.

**Do I need to transfer projects/repls from replit.com to firewalledreplit.com?**

No. Since the projects are attached to the organization/account and not the website domain, they will be made available on firewalledreplit.com automatically.

**Can our district request our own sub-domain or for specific content to be further filtered?**

With this new domain, firewalledreplit.com, there will be no access to the Internet through repls and the exclusion of community. Both of these features essentially create an environment where the focus is solely on coding and collaborating with only those the teacher allows. Therefore, there would be no added benefit to further filtering and no need to create a district-specific subdomain.
