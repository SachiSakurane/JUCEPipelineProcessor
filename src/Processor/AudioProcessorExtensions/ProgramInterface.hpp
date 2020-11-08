//
// Created by Himatya on 2020/10/26.
//

#pragma once

#include <juce_core/juce_core.h>

namespace AudioProcessorExtensions {
    struct ProgramInterface {
        virtual ~ProgramInterface() = default;
        virtual int getNumPrograms() = 0;
        virtual int getCurrentProgram() = 0;
        virtual void setCurrentProgram (int index) = 0;
        virtual const juce::String getProgramName (int index) = 0;
        virtual void changeProgramName (int index, const juce::String& newName) = 0;
    };
}