# Managing your repls

To manage and keep track of all your repls, head to your Repls Dashboard. You can find it on your account by clicking on the 'My Repls' tab on the left-hand side.

Repls are listed in order of when they were created, with the most recent first. Each repl has its own three-dot menu at the far right. Bringing up this menu will allow you to:

- Edit the repl (change its name and description)
- View its history
- Fork the repl
- Move the repl
- Pin it to your profile
- Delete the repl
- Toggle privacy settings (subscribers only)

## Public/Private Repls

By default all Repls created are 'public'. This means that anyone on Replit may discover and view the source code for these Repls. Users will be able to publish these Repls to the community and others will be able to view on comment on the Repl.

Users with Hacker plan subscriptions or cycles may elect to make their Repl 'private'. This means that only the creator (and any one they explicitly invite) to the Repl may view the source code. This also means that the Repl will not be available to share to the community.

Note: Private Repls will be inaccessible to other users on Replit, however, if the Repl is hosted (eg: HTML, Node.js, Django) the output of those Repls may still be accessible on the internet. If you are hosting sensitive information please use a non-hosted Repl (eg: Nix) to ensure complete privacy.

## Starring Repls

You can "star" a Repl to mark it as a favorite. This means you can then easily filter your dashboard to show only your starred Repls by clicking on the star slider at the top of your dashboard. There is no limit to how many Repls you can star. Only you can see which Repls you have starred; this info will not appear in your profile.

## Searching

### Basic Search

To search your repls, click on the search bar. You will be presented with the options "+ New" and "Search". Click "Search" and start typing keywords. This will filter repls whose title or language match any of the keywords (separated by spaces).

Repls only need to match one of the keywords in order to be included in the results.

Example:

**Search Query:** `draft repl python3`

**Returns:**
All repls that satisfy one or more of the following conditions:

- has `draft` in the title
- has `repl` in the title
- is a `python3` repl

### Search by Language

You can search for repls in a specific language by using the `language:` filter.
Typing in `language:` followed by the language you want to filter by will prompt
you with language suggestions.

Your search term will need to be the language name we use internally, which is why
we suggest selecting from the provided list. For example, to search for all C++11
languages, you would search `language:cpp11`. To search for HTML, CSS, JS repls,
you would search `language:html`. This filter is case sensitive.

### Search by Title

Since plain searches include results with matching languages, you can search within repl titles only using the `title:` filter. Your search term may not include spaces.
This filter is case insensitive.

Example:

**Search Query:** `title:best project`

**Returns:**
Repls that satisfy one or more of the following conditions:

- has `best` in the title
- has `project` in the title
