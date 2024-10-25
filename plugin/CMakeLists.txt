juce_add_plugin(JuceWebViewPlugin
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    PLUGIN_MANUFACTURER_CODE Ymoo
    PLUGIN_CODE Ywvp
    FORMATS AU VST3 Standalone
)

target_sources(JuceWebViewPlugin
    PRIVATE
      src/PluginProcessor.cpp
      src/PluginEditor.cpp
)

target_include_directories(JuceWebViewPlugin
    PRIVATE
      include
)

target_link_libraries(JuceWebViewPlugin
  PRIVATE
    juce::juce_audio_utils
  PUBLIC
      juce::juce_recommended_config_flags
      juce::juce_recommended_lto_flags
      juce::juce_recommended_warning_flags
)

target_compile_definitions(JuceWebViewPlugin
  PUBLIC
    JUCE_WEB_BROWSER=1
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)
