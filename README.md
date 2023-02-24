# LangChain.js LLM Template

This template allows you to make your own LLM, trained on custom data you provide.

This example is Amjad Masad, the CEO of Replit.  You can try the live demo at https://ai.repl.page

## Setup
1. Provide all the information you want your LLM to be trained on in the `training` directory in markdown files.  Folder depth doesn't matter.
2. Add your OpenAI API key in environment vars via the kay `OPENAI_API_KEY`.
3. Run `node initializeStore.js` to set up your vector store.
4. Run index.js, and you are finished ✨