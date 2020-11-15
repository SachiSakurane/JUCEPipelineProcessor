//
// Created by Himatya on 2020/11/15.
//

#pragma once

#include "Concepts/BaseBus.hpp"

namespace owle {
    template <BaseBus LeftBusType, BaseBus RightBusType>
    inline bool isEqualitySize(const LeftBusType& left, const RightBusType& right) {
        return (left.getNumChannels() == right.getNumChannels()) &&
            (left.getNumSamples() == right.getNumSamples());
    }
}