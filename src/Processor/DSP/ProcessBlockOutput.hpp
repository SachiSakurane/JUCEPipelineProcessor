//
// Created by Himatya on 2020/11/09.
//

#pragma once

#include "../Models/BufferModel.hpp"

class ProcessBlockOutput {
public:
    explicit ProcessBlockOutput(juce::AudioBuffer<float>& buffer) : audioBuffer {buffer} {}

    void process(const std::weak_ptr<const MultiBuffer<float>>& buffer) {
        decltype(auto) lockedBuffer = buffer.lock();

        if (!lockedBuffer) {
            return;
        }

        assert(audioBuffer.getNumChannels() == lockedBuffer->buffer.size());
        assert(audioBuffer.getNumSamples() == lockedBuffer->buffer[0].size());

        const size_t channels = audioBuffer.getNumChannels();
        for (size_t channel = 0; channel < channels; ++channel) {
            decltype(auto) pointer = audioBuffer.getWritePointer(channel);
            const size_t samples = audioBuffer.getNumSamples();

            for (size_t sample = 0; sample < samples; ++sample) {
                pointer[sample] = lockedBuffer->buffer[channel][sample];
            }
        }
    }

private:
    juce::AudioBuffer<float>& audioBuffer;
};