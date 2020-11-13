//
// Created by Himatya on 2020/11/13.
//

#pragma once

#include <cassert>

#include "Concepts/ReadableBus.hpp"
#include "Concepts/WritableBus.hpp"

template <class = void>
class Invert {
public:
    Invert() = default;

    template <class BusType> requires ReadableBus<BusType> && WritableBus<BusType>
    BusType& process(BusType& bus) {
        for (size_t channel = 0; channel < bus.getNumChannels(); ++channel) {
            for (size_t sample = 0; sample < bus.getNumSamples(); ++sample) {
                bus.getWritePointer(channel)[sample] = bus.getReadPointer(channel)[sample];
            }
        }
        return bus;
    }
};

template <WritableBus BufferType>
class Invert<BufferType> {
public:
    explicit Invert(BufferType&& buffer) : buffer {std::forward<BufferType>(buffer)} {}

    template <ReadableBus BusType>
    BufferType&& process(const BusType& bus) {
        assert(bus.getNumChannels() == buffer.getNumChannels());
        assert(bus.getNumSamples() == buffer.getNumSamples());
        for (size_t channel = 0; channel < bus.getNumChannels(); ++channel) {
            for (size_t sample = 0; sample < bus.getNumSamples(); ++sample) {
                buffer.getWritePointer(channel)[sample] = bus.getReadPointer(channel)[sample];
            }
        }
        return std::forward<BufferType>(buffer);
    }

private:
    BufferType&& buffer;
};

template <WritableBus BufferType>
Invert(BufferType&&) -> Invert<BufferType>;
