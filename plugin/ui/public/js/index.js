import * as juce from './juce/index.js';

console.log('JUCE SDK loaded', juce)

window.__JUCE__.backend.addEventListener(
  "exampleEvent",
  (event) => {
    console.log('exampleEvent received', event)
  }
)