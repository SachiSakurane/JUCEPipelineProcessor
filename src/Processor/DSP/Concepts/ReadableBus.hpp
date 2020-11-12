//
// Created by SachiP on 2020/11/12.
//

#pragma once

#include "BaseBus.hpp"

template <class ReadableBusType>
concept ReadableBus = BaseBus<ReadableBusType> && requires (const ReadableBusType& bus) {
    typename ReadableBusType::SampleType;
    {bus.getReadPointer()} -> owle::convertible_to<const typename ReadableBusType::SampleType*>;
};
