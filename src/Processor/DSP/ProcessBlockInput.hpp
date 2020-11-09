//
// Created by Himatya on 2020/11/08.
//

#pragma once

#include <utility>

#include "../Models/BufferModel.hpp"

class ProcessBlockInput {
public:
    explicit ProcessBlockInput(std::weak_ptr<MultiBuffer<float>> buffer) : buffer {std::move(buffer)} {}

    std::weak_ptr<const MultiBuffer<float>> process(const juce::AudioBuffer<float>& audio_buffer) {
        decltype(auto) lockedBuffer = buffer.lock();

        if (!lockedBuffer) {
            return buffer;
        }

        assert(audio_buffer.getNumChannels() == lockedBuffer->buffer.size());
        assert(audio_buffer.getNumSamples() == lockedBuffer->buffer[0].size());

        const size_t channels = audio_buffer.getNumChannels();
        for (size_t channel = 0; channel < channels; ++channel) {
            decltype(auto) pointer = audio_buffer.getReadPointer(channel);
            const size_t samples = audio_buffer.getNumSamples();

            for (size_t sample = 0; sample < samples; ++sample) {
                lockedBuffer->buffer[channel][sample] = pointer[sample];
            }
        }
        return buffer;
    }

private:
    std::weak_ptr<MultiBuffer<float>> buffer;
};
