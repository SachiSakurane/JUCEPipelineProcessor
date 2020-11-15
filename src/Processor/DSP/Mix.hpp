//
// Created by Himatya on 2020/11/15.
//

#pragma once

#include "Concepts/WritableBus.hpp"

template <ReadableBus BufferType>
class Mix {
public:
    Mix (BufferType&& wet, typename std::remove_cvref_t<BufferType>::SampleType mix) :
        wet{ std::forward<BufferType>(wet) }, mix {mix} {
    }

    template <class BusType> requires ReadableBus<BusType> && WritableBus<BusType>
    BusType&& process(BusType&& bus) {
        for (size_t channel = 0; channel < bus.getNumChannels(); ++channel) {
            for (size_t sample = 0; sample < bus.getNumSamples(); ++sample) {
                bus.getWritePointer(channel)[sample] = std::lerp(
                    bus.getReadPointer(channel)[sample],
                    wet.getReadPointer(channel)[sample],
                    mix);
            }
        }
        return std::forward<BusType>(bus);
    }

private:
    BufferType&& wet;
    typename std::remove_cvref_t<BufferType>::SampleType mix;
};

template <ReadableBus BufferType>
Mix(BufferType&&, typename std::remove_cvref_t<BufferType>::SampleType) -> Mix<BufferType>;
