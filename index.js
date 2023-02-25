import generateResponse from "./generateResponse.js";
import promptSync from 'prompt-sync';

const prompt = promptSync();

const conversationHistory = [];

while (true) {
  const question = prompt("Ask a question >");
  const answer = await generateResponse({
    prompt: question,
    history: conversationHistory
  });

  console.log(`Amjad Masad: ${answer}\n`);
  
  conversationHistory.push(`Human: ${question}`, `Amjad Masad: ${answer}`)
}