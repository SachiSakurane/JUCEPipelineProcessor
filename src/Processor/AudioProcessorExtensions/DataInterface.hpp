//
// Created by Himatya on 2020/10/26.
//

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

namespace AudioProcessorExtensions {
    struct DataInterface {
        virtual ~DataInterface() = default;
        virtual const juce::String getName() const = 0;
        virtual juce::StringArray getAlternateDisplayNames() const = 0;
        virtual bool acceptsMidi() const = 0;
        virtual bool producesMidi() const = 0;
        virtual bool isMidiEffect() const = 0;
        virtual bool isBusesLayoutSupported (const juce::AudioProcessor::BusesLayout& layouts) const = 0;
    };
}