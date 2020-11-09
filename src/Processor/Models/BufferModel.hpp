//
// Created by Himatya on 2020/11/01.
//

#pragma once

#include <mk2/container/fixed_array.hpp>

template <class Type>
struct MultiBuffer {
    mk2::container::fixed_array<mk2::container::fixed_array<Type>> buffer;
};
