/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "AudioProcessorExtensions/Processor.hpp"
#include "DSP/ProcessBlockInput.hpp"
#include "DSP/PassBlock.hpp"

//==============================================================================
class SidechainMixerAudioProcessor : public AudioProcessorExtensions::Processor<> {
public:
    SidechainMixerAudioProcessor();

private:
    void prepareToPlay (double sampleRate, int samplesPerBlock) final;
    void releaseResources() final;
    void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) final;

    ProcessBlockInput input, sidechainInput;
    PassBlock pass;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SidechainMixerAudioProcessor)
};
