/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <juce_audio_utils/juce_audio_utils.h>

//==============================================================================
/**
*/
class SidechainMixerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit SidechainMixerAudioProcessorEditor (juce::AudioProcessor*);
    ~SidechainMixerAudioProcessorEditor() override = default;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SidechainMixerAudioProcessorEditor)
};
