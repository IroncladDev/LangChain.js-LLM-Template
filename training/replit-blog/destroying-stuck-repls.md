---
title: Destroying Stuck Repls
author: Connor Brewster
categories: infra
---

**NOTE**: I am splitting this into some smaller posts.

Outline:
  * What is a stuck repl?
    * Different kinds
    * How often this happened
  * First step is to start tracking it
    * Unable to proxy log entries
    * Tracking unable to proxy errors in prom/grafana
    * Used a repl to scrape the logs and look for repls that have proxy errors over a span of time
    * Aggegrate these stuck repls into buckets of "time stuck"
    * Export these metrics to prometheus
    * Add a nice graph in Grafana
  * Core Invariant of Repl.it
    * Only ever 0-1 container alive for a repl
    * Essential for things like multiplayer to work
    * Really bad things can happen if this invariant is broken
  * Fixing repls that get stuck for hours
  * Fixing stuck repls due to slow container destroys on shutdown
    * Preemptible machines
      * Why?
      * Causes 100-200 repl containers to be destroyed at once
    * Maybe talk about systemd dependencies since docker was shutting at the same time as conman?
    * Docker is slow to kill this many containers
      * `docker destroy` vs `docker kill`
        * Destroy is graceful, gives time for container to shutdown gracefully
        * Kill should be immediate
      * Why isn't kill immediate?
        * Docker probably isn't designed to immediately kill hundreds of containers in a few seconds
        * Custom docker install
        * Lock contention
        * Waiting for cleanup of network interfaces
        * Serial interface of netlink was a bottleneck
      * What can we do about it?
        * Kill the container's pid ourselves
        * Since pid1 is the init process in its namespace, killing that kills all processes in the namespace
  * Where are we now?
    * We track both stuck repls and new session error rates
      * New session error rate comfortably below 0.5%
      * Stuck repl rate is very low, the ones that are stuck are only stuck for ~5 sec

[TODO: Come up with a more inspiring intro?]
You may have heard that we recently squashed a gnarly bug on our platform, but you may be curious about what was causing this issue and how we went about fixing it.

[TODO: Include a gif of a stuck repl]

<div style="display: flex; justify-content: center;">
<blockquote class="twitter-tweet"><p lang="en" dir="ltr">One of the worst bugs on our platform SQUASHED.<br><br>SMASHED.<br><br>E R A D I C A T E D<br><br>Ahem... so yeah, it&#39;s just gone now. <a href="https://t.co/4z8djrtDW6">pic.twitter.com/4z8djrtDW6</a></p>&mdash; Repl.it (@replit) <a href="https://twitter.com/replit/status/1318777999789969408?ref_src=twsrc%5Etfw">October 21, 2020</a></blockquote> <script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script> 
</div>

We had heard numerous reports of repls that would get stuck in an endless reconnecting loop. Sometimes the repls would be stuck for a couple minutes, other times they could be stuck in this look for multiple hours. This was no good; especially if you were needing to work on a homework assignment or were excited to work on your side project only to find out you can't connect. This is why we spent some time focusing on stability to make sure you can always access your repls.

When we would get reports of stuck repls, it was difficult to figure out the precise root cause. Sometimes the repls would already be working again by the time we went to diagnose the issue. This was clearly a problem, but the root cause was hard to identify. We needed to take a different approach to tracking down these issues.

One of the best things to do is to collect more metrics. Since this issue causes infinite reconnect loops, that means connections to the backend evaluation server were failing for some reason. In our effort to improve stability, successful connection rate was the first metric we started tracking. While adding new metrics is great, sometimes it uncovers some unfortunate realities that weren't aparent before. In our case, we discovered that our connection failure rate was around 3% [TODO: Verify this number, finding a graph would be great too] with occasional spikes that could go up to 10% or more.

## Breaking it down

While the failure rate was much disappointingly than we expected, it meant that we had room for improvement. We got right to work and began to break the problem down.

While overall failure rate is a great metric to have, it doesn't really tell us the full story. Is the connection failure happening across all repls? Is it due to a smaller set of repls that are continually having connection errors?

To answer these questions, we needed to drill further into the problem. There's no better place to do this than to dig into the logs of a repl that has failed connection attempts. We have nice indexed logs which allow us to quickly investigate a handful of these repls and look for any patterns.

It became clear that there were 2 different classes of stuck repls:
 * Repls that were stuck for less than 2 minutes
 * Repls that were stuck for an hour or more

Manually reading the logs can only get you so far. With the volume of logs and the number of repls we run, it's difficult to tell how frequent these different classes stuck repls occur. Our logging solution provides some basic aggregation tools, but it doesn't allow us to look at consecutive errors for a specific repl over time.

At repl.it we love using our own product to build tools to make our jobs easier. It's kind of a super power.

To determine how many stuck repls we have, I dumped some logs from the past 24 hours into a repl and began writing a script to crunch the log messages and spit out a nice table and bar graph of stuck repls bucketed by how long they have been stuck.

__Example output from my stuck repl finder__
```
Tue Oct 06 2020 00:00:00 GMT+0000 (Coordinated Universal Time)
Log Interval: 24.00 hours
Total stuck: 7427

Bucketed by time stuck (bucket name = max time in seconds)
     10 | ############################################################ | 2894
     15 | ############################################                 | 2125
     20 | ###############                                              | 722
     25 | ####################                                         | 941
     30 | #####                                                        | 238
     40 | ####                                                         | 169
     60 | ####                                                         | 207
     90 | ##                                                           | 92
    120 |                                                              | 13
    180 |                                                              | 14
    240 |                                                              | 4
    360 |                                                              | 2
    600 |                                                              | 0
   1200 |                                                              | 0
   3600 |                                                              | 2
  10000 |                                                              | 3
```

With this log-crunching repl, the data informed us that thousands of repls were stuck for less than 2 minutes per day and 5-10 repl would be stuck for almost and hour or more.

Frustration may ensue while waiting almost a minute to access your repl, but imagine not being able to access your repl for over an hour. We need to figure out why these repls are getting stuck for so long and fix the underlying cause, pronto!

## Fixing **Really** Stuck Repls

Armed with our new information, I set out to find the root cause of the forever-stuck-repls. Since there are so few of these, going back to the logs is a good place to see where it all went wrong.

> Digging through logs can be quite fun and provides good insight into how a system actually works.

First, we need to filter down the logs we want to look at. This is critical because we have a massive volume of log messages. Just in the past 15 minutes of writing this, over 4 million log messages were recorded!

Luckily, the stuck repl finder spits out a few repls that were stuck for over an hour. Using the repl IDs in this list, we can filter the logs down to only entries that are relevant to that repl.

Most of these repls had a recurring log entry: `session exited unexpectedly startup lock took too long for`

So, what is a startup lock and why is taking so long to get one? I'll go more into detail of our infrastructure in a bit. For now all you need to know is we use a locking mechanism to ensure that only one container ever exists at one time for a repl.

Seeing this log message repeatedly for over an hour likely means one thing: a **deadlock**.

We have a couples to determine how these deadlocks occur:
 * If we catch one in the act, we can dump the goroutines and look for goroutines blocked on things like `semacquire`.
 * Add more log messages and look at the order of events to determine if that could lead to a deadlock.

Unfortunately, there were a few different race conditions that lead to deadlocks that we had to track down and each one could have a blog post of its own.

[TODO: Maybe talk about chaos for writing tests to prevent regressions. That would be a cool blog post for Zach to write.]

## Leveling up our tools
While the repl I wrote earlier to crunch the logs messages worked, I still had to manually run the thing every day to get the results for the past 24 hours. This was starting to get old and Dan wanted to see how the metric was changing over time.

[TODO: Can we make this image smaller?]

![Dan suggests making this better](images/destroying-stuck-repls/dan_msg.png)

> If you find yourself doing the same manual task over and over, it's a sign that it might need to be automated.

What I really wanted was a nice real time chart in grafana that shows stuck repls over time. After talking with my team, Mason, recommended turning the repl into a hosted repl which serves metrics that our prometheus instance could scrape. I refactored the repl to make use of [repl.it database](https://blog.repl.it/database) and to serve a web page for prometheus to scrape. With just a couple hours of work, we now had real-time metrics for stuck repls.

[TODO: Should I make the repl public and link it here?]

![Graph of stuck repls](images/destroying-stuck-repls/stuck_repls_graph.png)
> This is a recent screenshot of the graph, so it looks much better than it used to!

Not only does this metric help us make sure our patches are actually reducing the number of stuck repls, but it will also help us make sure we don't accidentally regress in the future.

[TODO: Maybe this is its own blog post]

## Fixing *Sorta* Stuck Repls
Now that we've patched up all the deadlocks we know about, it's time to shift our eyes to repls that get stuck for a minute or two.

With a dashboard full of new stability-related metrics, we are able to find interesting correlations. _Aha!_ There is a spike in session connection errors whenever a group of conman instances shut down at the same time.

> Hold up! What does any of this mean? What is conman? And why do they shutdown frequently?

To answer that, we need to take a quick detour and talk about how repl.it actually works behind the scenes.

Let's talk about the most fundamental atom in the repl.it universe: the repl. 

[TODO: What is a repl? What is a repl container?]

[TODO: Talk about the importance of single repl container per repl]

When you open up a repl in your browser you are connected to a repl container which is running on our infrastructure. These are custom docker containers that are packed with all sorts of development tools.

To run these docker containers, we need a host machine. This is where conman comes in; it's name is short for container manager. Since we have so many repls running at any given time, a single conman cannot run all of these docker containers. So we have a group of conman instances which manage all the repl containers. A loadbalancer is used to distribute containers across conman instances. It is not uncommon for a single conman instance to be running 100-200 repl docker containers.

We run the majority of our conman instances using Google Cloud's preemptible instances. These are machines that can be taken away from us at any time with 30 seconds notice. The important thing is that these machines have an 80% discounted cost. That's a massive savings, but it requires us to architect replit to be resilient to machines disappearing at any time with short notice.

With some foundational knowledge of our architecture, lets focus in on the failure mode that happens when a conman instance is shut down.

![Simplified diagram of repl.it conman architecture](images/destroying-stuck-repls/simplified_arch.png)

1. A user opens their repl which opens the IDE and attempts to connect to the backend evaluation server via a WebSocket.
2. The request hits a load balancer which selects a conman instance to proxy to based on CPU usage.
3. A healthy, living conman gets the request. Conman notices that the request is for a container that is living on a different conman and proxies the request there.
4. Sadly this conman is shutting down and rejects the WebSocket connection!

Requests will continue to fail until either:
1. The docker container is shut down and the repl container entry in the global store is removed.
2. Conman finishes shutting down and is no longer accessibly. In this case, the first conman will remove the old repl container entry and start a new container.

For some reason, the docker containers were not being shut down fast enough. Google Cloud Platform, provides 30 seconds for the instance to shutdown before it is forcefully shutdown. Unfortunately, destroying all the containers on an instance within the time limit was a rarity.

After adding some more logging and metrics around container shutdowns, it became clear that calls to `docker kill` were taking much longer than expected. `docker kill` usually took [TODO: track down this number] to kill a repl container during normal operation, but when killing 100-200 containers at the same time, `docker kill` would take 20+ seconds.

Docker offers two ways to stop a container: `docker stop` and `docker kill`. Docker stop sends a `SIGTERM` signal to the container and gives it a grace period to gracefully shutdown. If the container doesn't shutdown within the grace period, the container is sent `SIGKILL`. We don't care about gracefully shutting down the container and would rather shut it down as quickly as possible. `docker kill` sends `SIGKILL` which should kill the container immediately. For some reason, the theory did not match reality, `docker kill` shouldn't be taking on the order of seconds to complete just to send `SIGKILL` to the container. There must be something else going on.

To dig into this, here is a script which will create 200 docker containers and times how long it takes to kill them all at the same time.

```bash
#!/bin/bash

COUNT=200
echo "Starting $COUNT containers..."
for i in $(seq 1 $COUNT); do
    printf .
    docker run -d --name test-$i nginx > /dev/null 2>&1
done

echo -e "\nKilling $COUNT containers..."
time $(docker kill $(docker container ls -a --filter "name=test" --format "{{.ID}}") > /dev/null 2>&1)

echo -e "\nCleaning up..."
docker rm $(docker container ls -a --filter "name=test" --format "{{.ID}}") > /dev/null 2>&1
```

Here is output from running this on an n1-highmem-4 instance on GCE (this is what our production infrastructure uses):

```
Starting 200 containers...
................................<trimmed>
Killing 200 containers...

real    0m37.732s
user    0m0.135s
sys     0m0.081s

Cleaning up...
```

_Yikes!_ It takes over 30 seconds to kill 200 containers. It shouldn't take this long to send `SIGKILL` to all these containers.

Docker daemon has an option to [enable debug logging](https://docs.docker.com/config/daemon/#enable-debugging). These logs let us peak into what what's happening inside of dockerd and each entry has a timestamp so it might provide some insight into where all this time is being spent.

With debug logging enabled, let's rerun the script and look at dockerd's logs. This will output a lot of log messages since we are dealing with 200 container, so lets look some hand-selected portions of the logs.

```
2020-12-04T04:30:53.084Z	dockerd	Calling GET /v1.40/containers/json?all=1&filters=%7B%22name%22%3A%7B%22test%22%3Atrue%7D%7D
2020-12-04T04:30:53.084Z	dockerd	Calling HEAD /_ping
2020-12-04T04:30:53.468Z	dockerd	Calling POST /v1.40/containers/33f7bdc9a123/kill?signal=KILL
2020-12-04T04:30:53.468Z	dockerd	Sending kill signal 9 to container 33f7bdc9a1239a3e1625ddb607a7d39ae00ea9f0fba84fc2cbca239d73c7b85c
2020-12-04T04:30:53.468Z	dockerd	Calling POST /v1.40/containers/2bfc4bf27ce9/kill?signal=KILL
2020-12-04T04:30:53.468Z	dockerd	Sending kill signal 9 to container 2bfc4bf27ce93b1cd690d010df329c505d51e0ae3e8d55c888b199ce0585056b
2020-12-04T04:30:53.468Z	dockerd	Calling POST /v1.40/containers/bef1570e5655/kill?signal=KILL
2020-12-04T04:30:53.468Z	dockerd	Sending kill signal 9 to container bef1570e5655f902cb262ab4cac4a873a27915639e96fe44a4381df9c11575d0
...
```

Here we can see the requests to kill each container, and immediately sending `SIGKILL` to the container.

Heres the log entries seen around 30 seconds after executing `docker kill`:
```
...
2020-12-04T04:31:32.308Z	dockerd	Releasing addresses for endpoint test-1's interface on network bridge
2020-12-04T04:31:32.308Z	dockerd	ReleaseAddress(LocalDefault/172.17.0.0/16, 172.17.0.2)
2020-12-04T04:31:32.308Z	dockerd	Released address PoolID:LocalDefault/172.17.0.0/16, Address:172.17.0.2 Sequence:App: ipam/default/data, ID: LocalDefault/172.17.0.0/16, DBIndex: 0x0, Bits: 65536, Unselected: 65529, Sequence: (0xfa000000, 1)->(0x0, 2046)->(0x1, 1)->end Curr:202
2020-12-04T04:31:32.308Z	dockerd	Releasing addresses for endpoint test-5's interface on network bridge
2020-12-04T04:31:32.308Z	dockerd	ReleaseAddress(LocalDefault/172.17.0.0/16, 172.17.0.6)
2020-12-04T04:31:32.308Z	dockerd	Released address PoolID:LocalDefault/172.17.0.0/16, Address:172.17.0.6 Sequence:App: ipam/default/data, ID: LocalDefault/172.17.0.0/16, DBIndex: 0x0, Bits: 65536, Unselected: 65530, Sequence: (0xda000000, 1)->(0x0, 2046)->(0x1, 1)->end Curr:202
2020-12-04T04:31:32.308Z	dockerd	Releasing addresses for endpoint test-3's interface on network bridge
2020-12-04T04:31:32.308Z	dockerd	ReleaseAddress(LocalDefault/172.17.0.0/16, 172.17.0.4)
2020-12-04T04:31:32.308Z	dockerd	Released address PoolID:LocalDefault/172.17.0.0/16, Address:172.17.0.4 Sequence:App: ipam/default/data, ID: LocalDefault/172.17.0.0/16, DBIndex: 0x0, Bits: 65536, Unselected: 65531, Sequence: (0xd8000000, 1)->(0x0, 2046)->(0x1, 1)->end Curr:202
2020-12-04T04:31:32.308Z	dockerd	Releasing addresses for endpoint test-2's interface on network bridge
2020-12-04T04:31:32.308Z	dockerd	ReleaseAddress(LocalDefault/172.17.0.0/16, 172.17.0.3)
2020-12-04T04:31:32.308Z	dockerd	Released address PoolID:LocalDefault/172.17.0.0/16, Address:172.17.0.3 Sequence:App: ipam/default/data, ID: LocalDefault/172.17.0.0/16, DBIndex: 0x0, Bits: 65536, Unselected: 65532, Sequence: (0xd0000000, 1)->(0x0, 2046)->(0x1, 1)->end Curr:202
```

These logs don't give us a full picture of everything dockerd is doing, but this makes it seem like dockerd might be spending a lot of time releasing network addresses.

At this point in my adventure, I decided it was time to start digging into docker engine's source code and build my own version of dockerd with some extra logging.

I started out by looking for the codepath that handles container kill requests. I added some extra log messages with timings of different spans and eventually I found out where all this time was being spent:

`SIGKILL` is sent to the container and then before responding to the HTTP request, the engine waits for the container to no longer be running ([source](https://github.com/docker/engine/blob/ab373df1125b6002603456fd7f554ef370389ad9/daemon/kill.go#L174))

```
	<-container.Wait(context.Background(), containerpkg.WaitConditionNotRunning)
```

The `container.Wait` function returns a channel which receives the exit code and any error from the container. Unfortunately, to get the exit code and error, a lock on the interal container struct must be acquired. ([source](https://github.com/docker/engine/blob/ab373df1125b6002603456fd7f554ef370389ad9/container/state.go#L212-L233))

```go
  ...

	go func() {
		select {
		case <-ctx.Done():
			// Context timeout or cancellation.
			resultC <- StateStatus{
				exitCode: -1,
				err:      ctx.Err(),
			}
			return
		case <-waitStop:
		case <-waitRemove:
		}

		s.Lock() // <-- Time is spent waiting here
		result := StateStatus{
			exitCode: s.ExitCode(),
			err:      s.Err(),
		}
		s.Unlock()

		resultC <- result
	}()

	return resultC

  ...
```

As it turns out, this container lock is held while cleaning up network resources and the `s.Lock()` above ends up waiting for a long time. This happens inside [`handleContainerExit`](https://github.com/docker/engine/blob/ab373df1125b6002603456fd7f554ef370389ad9/daemon/monitor.go#L27-L103). The container lock is held for the duration of the function. This function calls the container's [`Cleanup`](https://github.com/docker/engine/blob/ab373df1125b6002603456fd7f554ef370389ad9/daemon/start.go#L226-L266) method which releases network resources.

So why does it take so long to cleanup network resources? The network resources are handled via [netlink](https://man7.org/linux/man-pages/man7/netlink.7.html). Netlink is used to communicate between user and kernel space which can be used to configure network interfaces. Unfortunately, netlink works via a serial interface. This means that all the operations to release the address of each container get bottlenecked by this serial interface.

Things started to feel a bit hopeless here. It didn't seem like there was anything we could do differently to escape waiting for network resources to be cleaned up. But, maybe we could bypass Docker altogether when killing containers.

As far as we are concerned, we want to kill the container but we don't want to wait for network resources to be cleaned up. The important thing is that the container will no longer produce any side effects. For example, we don't want the contain to take anymore snapshots.

The solution I went with was to bypass docker by killing the container's pid directly. Conman records the pid of the container after it is started and then sends `SIGKILL` to the container when it becomes time to be killed. Since a container forms a pid namespace, when the container's pid terminates, all other processes in the container/pid namespace also terminate.

From `pid_namespaces` [manual page](https://man7.org/linux/man-pages/man7/pid_namespaces.7.html):

> If the "init" process of a PID namespace terminates, the kernel terminates all of the processes in the namespace via a SIGKILL signal.

Given this, we can be reasonably confident that after sending `SIGKILL` to the container, that the container no longer produces any side effects.

After this change was applied, control of repls would be relinquished under a few seconds during shutdown. This was a massive improvement over the 30+ seconds before and brought our session connection error rate down from ~3% to well under 0.5%.

[TODO: Add graph of this]
