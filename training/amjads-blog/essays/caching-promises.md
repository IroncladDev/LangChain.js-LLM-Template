{
  "title": "Caching and Promises",
  "date": "03/05/2016"
}
---

It's fascinating to me how something that can be described so simply can also be
tricky to implement. Caching is the idea of keeping around results of
computations or outside-world-reads so it's easily accessible the next time
around.

Complications arise when we have different modules at different times being
interested in the same data. And fetching something from memory (cached) is
fundamentally different from, for example, reading it from disk or a remote
host. In JavaScript, the latter is implemented as an asynchronous call. And
since we usually don't know the order of calls ahead of time we're left with
having to provide a consistent interface to all callers regardless of where the
data is being fetched from. You'd also need to handle cases where callers ask
for data concurrently. Meaning that we may get another call while we are still
fetching the data and now we're left to manage calling the clients back in the
right order that they called us in.

The good news is that we can use Promises to:

1. Not have to distinguish between first and subsequent calls
2. Provide a consistent async interface
3. Manage callbacks and error propagation

<script src="//repl.it/embed/BtUs/11.js"></script>

A more interesting example would be something that needs to change it's internal
state. However, we need to do it in a way that doesn't require synchronous and
mutative access to the data. One of our criteria is to blur the distinction between readily
available data and things we haven't fetched yet. We also don't want different
mutation calls to effect each other. Ideally, every call would get it's own copy
of the data that reflect the state of the world at the time of the call.

We can handle this by chaining promise calls that will result in new instances
of the data that will also be cached for future use. Regardless of whether calls
happen concurrently we maintain a strict order of execution and every call will
get a copy of the data without the changes that were made by other callers.

<script src="//repl.it/embed/BtUs/12.js"></script>

------------------------------------------------

### Stores and Loaders

Caching can be hard if we have to continually answer the question: Do we have
the data in memory or do we need to fetch it? We just showed how we can use
promises to simplify this. However, it doesn't take into account function
parameters. A robust caching system has to be able to associate results with
inputs, be it URLs, file names, or arbitrary function parameters. To this end we
can create a store abstraction that will store things in the form of key/values.
But this presents a new challenge of having to synchronize fetching data and
storing it.

You can imagine two `get` calls to the stores for something we don't have a
result for yet. Then these two callers would go about concurrently trying to
compute or fetch the data and then come back and try to set it in the store. And
now we have a duplication of work and something akin to a race condition when it
comes to writing the result back to the store. We can add an `isFetching` flag
to the store but that brings us back to square one of having to manage
callbacks. Here again we can use promises to solve this problem. In addition
to managing callbacks for us they'll provide something which we can call the
"loader" interface.

<script src="//repl.it/embed/BtUs/9.js"></script>

So instead of having the callers arbitrarily check and set data on the store, we
can instead only expose a `get` method that will take a key and a loader
function that if called should return a promise for the value. That way the
first time the `Cache` class encounters a key it will call the loader function
and cache the promise for any subsequent caller.

### Memoization

So far we've seen how we can remove the burden of having to check whether something
is in memory or not at every turn. If we
generalize this a bit we can say that callers should *always* call functions
regardless of the current state. This is commonly referred to as
memoization and it allows us to build faster programs without compromising on
simplicity. That's partly why frameworks like React are popular -- it unburdens
the programmer from dealing with stateful objects like the DOM. You *always* render.
Just like you *always* call.

All the caching techniques powered by promises that we talked about here can
come in handy when building large programs that conceptually looks like
good old simple and stateless programs without compromising on performance.

My personal experience with this was with building the [React Native
Packager](https://github.com/facebook/react-native/tree/87245b2d40a865290fbeb4d8f5474fb8b5c1b891/packager)
and the [module resolver](https://github.com/facebook/node-haste).
One of our goals with React Native is to bring the fast feedback loop we're used
to in web development to native. However, when we looked at
bundlers in the wild we found that for any sizable project they took
10s of seconds to recompute the bundle after a single file change.
So we had to build our own with performance as the defining feature.

The entire system was built to be lazy and heavily cached using the techniques
outlined in this article. When we get a request for a bundle
we go through and  apply the module resolution algorithm
recursively while reading all the necessary files. And then we compile the files
in parallel and finally combine everything in a single bundle and generate the
sourcemaps. Everyone of those steps requires heavy computation and/or I/O. But
along the way we cache everything at a granular level. Then the next time we
fan-out in the tree of calls to generate the bundle most things will be cached
and the result is instantly returned from memory. The whole thing takes up to a
hundred milliseconds to execute.

When a file changes we invalidate the caches concerning that file and we simulate
a request that would go through entire process again but this time recomputing
parts of the process concerning the changed file (and any other artifacts
affected by it). This will take less than a second to
finish. And by the time the actual request comes in from the client we have
everything cached!
