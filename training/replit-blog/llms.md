---
title: Productizing Large Language Models
author: Amjad Masad, Samip Dahal, Luis Héctor Chávez
date: 2022-09-21
cover: https://blog.replit.com/images/ai/ghost.png
categories: product,ai
---
\
Large Language Models (LLMs) are known for their near-magical ability to learn from very few examples -- as little as zero -- to create language wonders. LLMs can chat, write poetry, write code, and even do basic [arithmetic](https://arxiv.org/abs/2205.11916). However, the same properties that make LLMs magical also make them challenging from an engineering perspective.

At Replit we have deployed transformer-based language models of all sizes: ~100m parameter models for search and spam, 1-10B models for a code autocomplete product we call [GhostWriter](https://blog.replit.com/ai), and 100B+ models for features that require a higher reasoning ability. In this post we'll talk about what we've learned about building and hosting large language models.

<video src="https://blog.replit.com/images/ai/aimode.mp4"  class="css-3qjkrt" autoplay muted playsinline loop controls></video>

## Nonsense

Any sufficiently advanced bullshit is indistinguishable from intelligence, or so the LLM thought. LLMs are super suggestible -- in fact, the primary way to interact with LLMs is via ["prompting."](https://en.wikipedia.org/wiki/Prompt_engineering) Basically, you give the LLM a string of text and it generates a response, mostly in text form although some models can also generate audio or even images. The problem is, you can prompt the LLM with nonsense and it will generate nonsense. Garbage in, garbage out. Also, LLMs tend to get stuck in loops, repeating the same thing over and over again, since they have a limited attention span when dealing with some novel scenarios that were not present during training.

Luckily, there are some controls to make these two problems more manageable. The first is tweaking the so called ["temperature"](https://nlp.stanford.edu/blog/maximum-likelihood-decoding-with-rnns-the-good-the-bad-and-the-ugly/) of the model. This is a parameter that affects the likelihood of the model picking a less likely word. The higher the temperature, the more random the output. The lower the temperature, the more likely the model is to generate words that are similar to the words it has seen before. Setting the temperature to zero makes the LLM more predictable.

The second control is the frequency penalty. This parameter affects the likelihood of the model picking a word that it has seen a lot. The higher the frequency penalty, the less likely the model is to generate words that it has previously generated. The lower the frequency penalty, the more likely the model is to generate words that it has previously generated.

However, both parameters, up to a certain point, can start degrading the model's performance. For some applications, you'd want the model to be more "creative" therefore, a zero temperature doesn't cut it. And for other apps, repetition can make sense, for example, when the model is writing poetry or code.

We've found a few other methods to be helpful when filtering out nonsense:
* Cycle detection: When the model goes into an obvious loop and starts repeating itself, we can simply truncate the output or intervene somehow via the prompt to get a different completion.
* Sampling: We can sample the output of the model at different "temperatures" and pick the one that makes the most sense. This is especially helpful when the model is stuck at a local minimum.
* Layering another model: We can use an LLM to generate a set of candidates and then use a different model to pick the best one. This is helpful when the LLM is generating multiple candidates that are all valid but you only want one.
* Training to break the loop: Repetitions are often self-reinforcing (i.e. the probability of repetitions increase with no. of repetitions). We can train LLMs to break such loop of repetitions by [penalizing repetitions](https://arxiv.org/pdf/2206.02369v1.pdf) on synthetic data.
* Finetuning on user feedback: We can use feedback from users to finetune the model to better match the user's preferences.

## Quality Assurance

When iterating on the model it's really easy to accidentally regress on performance, and unlike classical programs where input/output are largely determinstic, it's really hard to tell when an LLM has regressed. We've found it helpful to run the model against a standard benchmark dataset and track the performance on that benchmark over time. Currently, we are using OpenAI's [HumanEval](https://github.com/openai/human-eval) benchmark to evaluate quality of the model over time. We also track how often the model gets stuck in loops and how often it produces nonsense.

We also use A/B testing to compare different models and make sure that the changes we're making are actually improvements. 

## Performance

Large Language Model means billions (approaching trillions) of parameters, which means they are slow to train and slow to run. We've found it helpful to use a combination of techniques to speed up both training and inference. Here is what we did for GhostWriter:

* [FasterTransformer](https://github.com/NVIDIA/FasterTransformer):  We've found that the transformer architecture used by most LLMs can be made faster without sacrificing too much accuracy by making some changes to the architecture. FasterTransformer, for example, sports a highly-optimized decoder blocks with the possibility of extending to distributed, multi-GPU fashion with tensor or pipeline parallelism. Their computational and memory optimizations make inference much faster than popular frameworks like PyTorch or Tensorflow, especially when running on NVIDIA hardware.
* Knowledge Distillation: We can use a smaller model to "distill" the knowledge of a larger model. This gives us a model that is both faster and more accurate. For example see [DistilBERT](https://github.com/huggingface/transformers/tree/main/examples/research_projects/distillation).
* Quantization:  We can use techniques like [quantization](https://en.wikipedia.org/wiki/Quantization_(signal_processing)) to compress the model by using different data types to represent all or a subset of the model parameters and input activations (float32 -> float16 or even int8) and make it simultaneously smaller and faster without sacrificing too much accuracy.

## Prompt engineering

One way to think about running the model is like running your Apache webserver -- once you've configured it correctly, you still have to write the business logic of your application. 

The same thing goes for LLMs, the prompt is what defines your application. And prompts are not just static things you write and forget about:

* Prompts change with context: For GhostWriter, prompts consisted of telling the model what language we're using, what file we're on, and the file's content up to the cursor. But that's only scratching the surface, it's been shown that you can generate prompts that capture the context of the [entire project](https://arxiv.org/abs/2206.12839).
* Track prompts in version control as you would code: Prompts are essentially natural language "code," so it makes sense to use the same tools for storing, versioning, and diffing them.
* Prompts can be generated by another model: We've found that you can chain models to create better prompts. In one example, we used one model to clean up the prompt before passing it into the generative model.

## Deployment & monitoring

We run GhostWriter on GPUs in the cloud. Those GPUs are expensive, so we want to be able to have each of those GPUs serve as many requests as possible. But realistically we can never achieve 100% utilization of those GPUs: if we model the inference system as a queue, and that queue is already going as fast as it possibly can, whenever there is _any_ change in the arrival rate of requests, the queue would start growing unboundedly since the rate of departure of responses cannot go any faster. This means that requests would start timing out and user experience would degrade very quickly. In order to mitigate this, we currently are targeting for 70-80% utilization of the GPUs to leave a small buffer for small variations in request rate, and also allow for the system to spin up new GPUs when we're running close to the limit. This leads us to be very close to a cost and latency optimum simultaneously.

We already had experience with running most of our other services in [Kubernetes](https://kubernetes.io/), so it was very easy to create one more container to run GhostWriter in it. During our initial ramp-up we are running the GhostWriter inference servers geographically closer to where our servers are running (in the US). When we continue with our push to have more [worldwide Repls](https://blog.replit.com/geo-part-1-controlplane), we will start pushing the servers closer to where our users are, reducing latency by up to 200ms in the very worst case (Delhi-US roundtrip).

And of course all of this wouldn't really matter unless we knew the health of the system. We have monitoring on both the server and client sides in addition to system-level monitoring in Kubernetes for latency, availability, request rates, and other leading indicators of health.

To help mesure the quality of each model, we also store what suggestions were accepted and rejected, and track when GhostWriter completed something or the user typed it. This data is then used for fine-tuning and further training.

<script>
  window.addEventListener('load', videoScroll);
window.addEventListener('scroll', videoScroll);

function videoScroll() {

  if ( document.querySelectorAll('video[autoplay]').length > 0) {
    var windowHeight = window.innerHeight,
        videoEl = document.querySelectorAll('video[autoplay]');

    for (var i = 0; i < videoEl.length; i++) {

      var thisVideoEl = videoEl[i],
          videoHeight = thisVideoEl.clientHeight,
          videoClientRect = thisVideoEl.getBoundingClientRect().top;

      if ( videoClientRect <= ( (windowHeight) - (videoHeight*.5) ) && videoClientRect >= ( 0 - ( videoHeight*.5 ) ) ) {
        thisVideoEl.play();
      } else {
        thisVideoEl.pause();
      }

    }
  }

}
</script>