juce_add_plugin(JuceWebViewPlugin
    COMPANY_NAME YMO
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    PLUGIN_MANUFACTURER_CODE Ymoo
    PLUGIN_CODE Ywvp
    FORMATS AU VST3 Standalone
)

get_target_property(PRODUCT_NAME JuceWebViewPlugin JUCE_PRODUCT_NAME)
get_target_property(COMPANY_NAME JuceWebViewPlugin JUCE_COMPANY_NAME)
target_compile_definitions(JuceWebViewPlugin
  PRIVATE
    JUCE_PRODUCT_NAME="${PRODUCT_NAME}"
    JUCE_COMPANY_NAME="${COMPANY_NAME}"
    JUCE_PLUGIN_VERSION="${PROJECT_VERSION}"
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

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../libs/juce/modules/juce_gui_extra/native/javascript/" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/ui/public/js/juce/")