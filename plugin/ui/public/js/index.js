import * as juce from './juce/index.js';

console.log('JUCE SDK loaded', juce)

window.__JUCE__.backend.addEventListener(
  "exampleEvent",
  (event) => {
    console.log('exampleEvent received', event)
  }
)

const data = window.__JUCE__.initialisationData;

document.getElementById('vendor').innerHTML = data.vendor;
document.getElementById('pluginName').innerHTML = data.pluginName;
document.getElementById('pluginVersion').innerHTML = data.pluginVersion;
