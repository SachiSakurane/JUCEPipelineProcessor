//
// Created by Himatya on 2020/11/08.
//

#pragma once

#include "../Models/AudioProcessorModel.hpp"
#include "../Models/BufferModel.hpp"

class ProcessBlockInput {
public:
    using ArgType = juce::AudioBuffer<float>;
    using ReturnType = std::weak_ptr<const MultiBuffer<float>>;

    PrepareToPlayParameter prepare(const PrepareToPlayParameter& parameter) {
        std::lock_guard<std::mutex> lock {mutex};

        buffer = std::make_shared<MultiBuffer<float>>(
            MultiBuffer<float>{{2,
                                mk2::container::fixed_array<float>(
                                    static_cast<size_t>(parameter.samplesPerBlock),
                                    0.f)}});

        return parameter;
    }

    ReturnType process(const ArgType& audio_buffer) {
        decltype(auto) lock = std::unique_lock<std::mutex>(mutex, std::try_to_lock);

        if (!lock) {
            return {};
        }

        const size_t channels = audio_buffer.getNumChannels();
        for (size_t channel = 0; channel < channels; ++channel) {
            decltype(auto) pointer = audio_buffer.getReadPointer(channel);
            const size_t samples = audio_buffer.getNumSamples();

            for (size_t sample = 0; sample < samples; ++sample) {
                buffer->buffer[channel][sample] = pointer[sample];
            }
        }
        return buffer;
    }

private:
    std::mutex mutex;
    std::shared_ptr<MultiBuffer<float>> buffer;
};
