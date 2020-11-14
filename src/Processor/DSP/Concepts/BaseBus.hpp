//
// Created by SachiP on 2020/11/12.
//

#pragma once

#include <type_traits>

#include "Utility.hpp"

template <class BaseBusType>
concept BaseBus = requires (const BaseBusType& bus) {
    {bus.getNumChannels()} -> owle::convertible_to<size_t>;
    {bus.getNumSamples()} -> owle::convertible_to<size_t>;
};
