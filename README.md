# LangChain.js LLM Template

This is a LangChain LLM template that allows you to train your own custom AI model on any data you want.

## Setup
1. Provide all the information you want your LLM to be trained on in the `training` directory in markdown files.  Folder depth doesn't matter.
2. Add your OpenAI API key in environment vars via the kay `OPENAI_API_KEY`.
3. Run `yarn train` or `npm train` to set up your vector store.
4. Modify the base prompt in `lib/basePrompt.js`
5. Run index.js, and start playing around with it!

Source code: https://github.com/Conner1115/LangChain.js-LLM-Template

[![Run on Replit](https://user-images.githubusercontent.com/50180265/221977287-4622854b-8c89-4f75-81af-eee6058a20fa.png)](https://replit.com/@IroncladDev/LangChainjs-LLM-Template?v=1)
