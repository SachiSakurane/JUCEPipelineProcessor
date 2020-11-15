//
// Created by SachiP on 2020/11/12.
//

#pragma once

#include "BaseBus.hpp"

template <class ReadableBusType>
concept ReadableBus = BaseBus<ReadableBusType> && requires (const ReadableBusType& bus) {
    typename std::remove_cvref_t<ReadableBusType>::SampleType;
    {bus.getReadPointer(std::declval<int>())} ->
        owle::convertible_to<const typename std::remove_cvref_t<ReadableBusType>::SampleType*>;
};
