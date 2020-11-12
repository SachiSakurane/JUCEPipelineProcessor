//
// Created by SachiP on 2020/11/12.
//

#pragma once

#include "Bus.hpp"

template <class ReadableBusType>
concept ReadableBus = requires Bus<ReadableBusType> && (ReadableBusType& bus) {
    //
};
