//
// Created by Himatya on 2020/10/26.
//

#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

struct PrepareToPlayParameter {
    double sampleRate;
    int samplesPerBlock;
};

struct ProcessBlockParameter {
    juce::AudioBuffer<float> mainInOut;
    juce::AudioBuffer<float> sideIn;
    juce::MidiBuffer& midiMessages;
};
