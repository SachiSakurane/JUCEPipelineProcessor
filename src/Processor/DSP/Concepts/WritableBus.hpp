//
// Created by SachiP on 2020/11/12.
//

#pragma once

#include "BaseBus.hpp"

template <class WritableBusType>
concept WritableBus = BaseBus<WritableBusType> && requires (WritableBusType& bus) {
    typename std::remove_cvref_t<WritableBusType>::SampleType;
    {bus.getWritePointer(std::declval<int>())} ->
        owle::convertible_to<typename std::remove_cvref_t<WritableBusType>::SampleType*>;
};
