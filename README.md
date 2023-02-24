# LangChain.js LLM Template

This is a LangChain LLM template that allows you to train your own custom AI LLM.  Setup is as easy as 1-2-3.

## Setup
1. Provide all the information you want your LLM to be trained on in the `training` directory in markdown files.  Folder depth doesn't matter.
2. Add your OpenAI API key in environment vars via the kay `OPENAI_API_KEY`.
3. Run `node initializeStore.js` to set up your vector store.
4. Run index.js, and you are finished ✨