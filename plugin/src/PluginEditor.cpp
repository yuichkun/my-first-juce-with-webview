#include "JuceWebViewPlugin/PluginProcessor.h"
#include "JuceWebViewPlugin/PluginEditor.h"
#include <cstdio>
#include <optional>

//==============================================================================
namespace webview_plugin {
namespace {
    auto streamToVector (juce::InputStream& stream)
{
    using namespace juce;
    std::vector<std::byte> result ((size_t) stream.getTotalLength());
    stream.setPosition (0);
    [[maybe_unused]] const auto bytesRead = stream.read (result.data(), result.size());
    jassert (bytesRead == (ssize_t) result.size());
    return result;
}
const char* getMimeForExtension (const juce::String& extension)
{
    using namespace juce;
    static const std::unordered_map<String, const char*> mimeMap =
    {
        { { "htm"   },  "text/html"                },
        { { "html"  },  "text/html"                },
        { { "txt"   },  "text/plain"               },
        { { "jpg"   },  "image/jpeg"               },
        { { "jpeg"  },  "image/jpeg"               },
        { { "svg"   },  "image/svg+xml"            },
        { { "ico"   },  "image/vnd.microsoft.icon" },
        { { "json"  },  "application/json"         },
        { { "png"   },  "image/png"                },
        { { "css"   },  "text/css"                 },
        { { "map"   },  "application/json"         },
        { { "js"    },  "text/javascript"          },
        { { "woff2" },  "font/woff2"               }
    };

    if (const auto it = mimeMap.find (extension.toLowerCase()); it != mimeMap.end())
        return it->second;

    jassertfalse;
    return "";
}
}

AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
    AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(&p), processorRef(p),
      webView(juce::WebBrowserComponent::Options{}.withResourceProvider(
          [this](const auto &url) { return getResource(url); }
        )
    )
{
    juce::ignoreUnused (processorRef);

    addAndMakeVisible(webView);
    webView.goToURL(webView.getResourceProviderRoot());
    setResizable(true, true);
    setSize (200, 200);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================

void AudioPluginAudioProcessorEditor::resized()
{
    webView.setBounds(getLocalBounds());
}

auto AudioPluginAudioProcessorEditor::getResource(const juce::String& url) -> std::optional<Resource> {
    static const auto resourceFileRoot =
        juce::File("/Users/yuichkun/workspace/my-first-juce-with-webview/plugin/src/ui/public");

    const auto resourceToRetrieve = url == "/" ? "index.html" : url.fromFirstOccurrenceOf("/", false, false);

    const auto resource = resourceFileRoot.getChildFile(resourceToRetrieve).createInputStream();

    if (resource) {
      const auto extension = resourceToRetrieve.fromLastOccurrenceOf(".", false, false);
      return Resource{streamToVector(*resource), getMimeForExtension(extension)};
    }

    return std::nullopt;
}

}
