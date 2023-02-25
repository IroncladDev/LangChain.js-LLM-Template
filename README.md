# LangChain.js LLM Template

This is a LangChain LLM template that allows you to train your own custom AI model on any data you want.

## Setup
1. Provide all the information you want your LLM to be trained on in the `training` directory in markdown files.  Folder depth doesn't matter.
2. Add your OpenAI API key in environment vars via the kay `OPENAI_API_KEY`.
3. Run `node initializeStore.js` to set up your vector store.
4. Modify the base prompt in `lib/basePrompt.js`
5. Run index.js, and start playing around with it!

Source code: https://github.com/Conner1115/LangChain.js-LLM-Template

[![Run on Repl.it](https://replit.com/badge/github/Conner1115/LangChain.js-LLM-Template)](https://replit.com/new/github/Conner1115/LangChain.js-LLM-Template)