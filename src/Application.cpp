//
// Created by Himatya on 2020/10/29.
//

#include "Processor/SidechainMixerAudioProcessor.hpp"
#include "Editor/SidechainMixerAudioProcessorEditor.hpp"

class TopLevelAudioProcessor final : public SidechainMixerAudioProcessor {
private:
    bool hasEditor() const final {
        return true;
    }

    juce::AudioProcessorEditor* createEditor() final {
        return new SidechainMixerAudioProcessorEditor(this);
    }
};

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TopLevelAudioProcessor();
}