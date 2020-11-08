cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(SidechainMixer VERSION 0.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set_property(GLOBAL PROPERTY USE_FOLDERS YES)
option(JUCE_ENABLE_MODULE_SOURCE_GROUPS "Enable Module Source Groups" ON)

add_subdirectory(lib/JUCE)
add_subdirectory(lib/googletest)

include_directories("${gtest_SOURCE_DIR}/include")

option(JUCE_BUILD_EXTRAS "Build JUCE Extras" OFF)
option(JUCE_BUILD_EXAMPLES "Build JUCE Examples" OFF)

juce_add_plugin(${CMAKE_PROJECT_NAME}
        # VERSION ...                               # Set this if the plugin version is different to the project version
        # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
        # ICON_SMALL ...
        COMPANY_NAME "execute project"                          # Specify the name of the plugin's author
        IS_SYNTH FALSE                       # Is this a synth or an effect?
        NEEDS_MIDI_INPUT FALSE               # Does the plugin need midi input?
        NEEDS_MIDI_OUTPUT FALSE              # Does the plugin need midi output?
        IS_MIDI_EFFECT FALSE                 # Is this plugin a MIDI effect?
        EDITOR_WANTS_KEYBOARD_FOCUS FALSE    # Does the editor need keyboard focus?
        COPY_PLUGIN_AFTER_BUILD TRUE        # Should the plugin be installed to a default location after building?
        PLUGIN_MANUFACTURER_CODE mYdl               # A four-character manufacturer id with at least one upper-case character
        PLUGIN_CODE sALq                            # A unique four-character plugin id with at least one upper-case character
        FORMATS AU VST3 Standalone              # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
        PRODUCT_NAME ${CMAKE_PROJECT_NAME})                     # The name of the final executable, which can differ from the target name

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/mk2/include)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Application.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Editor/SidechainMixerAudioProcessorEditor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Processor/SidechainMixerAudioProcessor.cpp)

target_compile_definitions(${CMAKE_PROJECT_NAME}
        PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0)

# If your target needs extra binary assets, you can add them here. The first argument is the name of
# a new static library target that will include all the binary resources. There is an optional
# `NAMESPACE` argument that can specify the namespace of the generated binary data class. Finally,
# the SOURCES argument should be followed by a list of source files that should be built into the
# static library. These source files can be of any kind (wav data, images, fonts, icons etc.).
# Conversion to binary-data will happen when your target is built.

# juce_add_binary_data(AudioPluginData SOURCES ...)

# `target_link_libraries` links libraries and JUCE modules to other libraries or executables. Here,
# we're linking our executable target to the `juce::juce_audio_utils` module. Inter-module
# dependencies are resolved automatically, so `juce_core`, `juce_events` and so on will also be
# linked automatically. If we'd generated a binary data target above, we would need to link to it
# here too. This is a standard CMake command.

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        # AudioPluginData           # If we'd created a binary data target, we'd link to it here
        juce::juce_audio_utils)

add_executable(${CMAKE_PROJECT_NAME}_Test)

target_include_directories(${CMAKE_PROJECT_NAME}_Test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/mk2/include)

target_link_libraries(${CMAKE_PROJECT_NAME}_Test PRIVATE
        ${CMAKE_PROJECT_NAME}
        gtest_main
        gmock_main
        juce::juce_audio_utils)
