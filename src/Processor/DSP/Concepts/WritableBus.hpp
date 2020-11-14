//
// Created by SachiP on 2020/11/12.
//

#pragma once

#include "BaseBus.hpp"

template <class WritableBusType>
concept WritableBus = BaseBus<WritableBusType> && requires (WritableBusType& bus) {
    typename WritableBusType::SampleType;
    {bus.getWritePointer(std::declval<int>())} -> owle::convertible_to<typename WritableBusType::SampleType*>;
};
