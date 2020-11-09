/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "AudioProcessorExtensions/Processor.hpp"
#include "Models/BufferModel.hpp"

//==============================================================================
class SidechainMixerAudioProcessor : public AudioProcessorExtensions::Processor<> {
public:
    SidechainMixerAudioProcessor();

private:
    void prepareToPlay (double sampleRate, int samplesPerBlock) final;
    void releaseResources() final;
    void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) final;


    std::shared_ptr<MultiBuffer<float>> sharedBuffer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SidechainMixerAudioProcessor)
};
