If you've been using Replit for a while you might have noticed our multiplayer feature has gone through quite a few iterations. As it has evolved the infrastructure making it all work has been along for the ride. Each implementation unlocked important capabilities and pushed our infrastructure to be better.

Our very first implementation of multiplayer was intentionally kept simple. We reached for what we deemed well established and supported libraries in the community. This lead us to a stack with [our editor](linktomonacoblogpost) talking [operational transform](yep) to [sharejs](yep) backed by [mongodb](yep) to coordinate edits between clients. This meant supporting additional infrastructure but required very little code and no changes to what we were already running. There were some significant downsides though. Being purely client based multiplayer sessions would rely on the host for coordination and thus only live as long as the host. Clients needed to send file contents to their repls when they run. Lots of scaling issues. We wanted to preserve OT history efficiently. Probably more. Shit on mongo db a lil, i hear that's hot. It wasn't very stable right guys?

We were surprised to find what looked to be the state of the art open source collaborative editing appeared to have many serious flaws. After beginning to roll out multiplayer we found a myriad of bugs stemming from libraries we depended on. *talk a lil shit about sharejs n friends*! i forget what the issues were but we diverged and had catch up problems iirc?

To move forward we wanted to dramatically simplify the inner workings of multiplayer and own much more of the vertical. Although this meant more work up front, having simpler code we understood sounded a lot better than gluing together libraries we didn't. After surveying the existing technology we settle on a very simple version of unicode text based operational transform. OT, we found, was well understood, simpler than any alternatives, and most importantly we could wrap our heads around it. Collaborative editing was redesigned more like a regular desktop application to on top of our existing code evaluation infrastructure.

Some major protocol changes later making [natively concurrent and mutliseat](link to that blog post) and this was decidedly the way multiplayer should work.

But first you probably want some background on our code evaluation infrastructure. We call it Goval internally and it's awesome. It starts up hundreds of repls every second all day every day. But to be this awesome it has an important caveat: it can kill your repl at any time for any reason. If you decide you want to keep repling you'll have to boot the repl up from scratch and start again at the last checkpoint. This takes lots of careful consideration from the client to keep things moving along smoothly. Although a tricky trade off we've decided it's worth it.

Collaborative editing is build right in to your repl (actually packed into the init process), running right next to your `main.py` and [language server](yep). This poses some interesting technical problems as we need to follow the rules of userland. The trade-offs are easily worth it, the code is exceedingly simple and focused only on the task at hand. Code that runs in a repl needn't worry about scaling, servers, routing, or any other craziness the web often entails. That's already handled by our infrastructure for free. Once you get right down to it we're just dealing with a good ol' [unix system](memes).

When setting out on this journey we needed to face some unfortunate truths.  Writing correct code is hard. Writing correct code to do operation transform is *really* hard. To balance with human fallibility we put significant effort into error detection, reporting, and recovery. When things go wrong we try to crash as fast and loud as we can. This might not always lead to the best user experience 

Although we trusted our OT test suite was good, we also trusted our users to fuzz the shit out of us bro.

Before making any attempts to change stuff we've put a lot of work.

no multiplayer -> going live -> always multiplayer -> multiplayer native

coming soon: multiplayer native aka product catches up with infra

# NOOOTES

- everything was on the client, life was easy
- went multiplayer. read all about it here https://blog.repl.it/multi 
- life got a lot harder
- should we mention?: we regressed
- our infra is based on ephemeral stuff, we need to be highly crash recoverable
- scaling was $0
- ![ot ops graph](images/ot_ops_graph.png)
- ot in an ephemeral world is kinda tricky
- checksuming, sometimes you find bugs in you libs
- ot history mayb
- chipping away at all the possible states
  - ![crc32 mismatches](images/crc32_mismatch.png)
  - ![prompted percent](images/prompted_percent.png)
  - we found lots of dumb bugs
    - https://github.com/josephg/unicount/pull/1
    - https://github.com/protobufjs/protobuf.js/pull/1486
    - monaco's newline fuckery
      - monaco reports it as one character even on windows
      - the offsets are messed up!
      - monaco normalizes the buffer into a single type of newline
      - theycan say  the line endings are
      - user file content can container a mix
      - we need to report hte right 
      - we store the actual characters
      - when we see monacdo's characters we walk the characters to get the real offset
      - change monaco to always use \n
      - if the file actually was 
