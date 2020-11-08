//
// Created by Himatya on 2020/10/26.
//

#pragma once

#include <juce_core/juce_core.h>

namespace AudioProcessorExtensions {
    struct StateInformationInterface {
        virtual ~StateInformationInterface() = default;
        virtual void getStateInformation (juce::MemoryBlock& destData) = 0;
        virtual void setStateInformation (const void* data, int sizeInBytes) = 0;
    };
}