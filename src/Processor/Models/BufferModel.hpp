//
// Created by Himatya on 2020/11/01.
//

#pragma once

#include <mk2/container/fixed_array.hpp>

struct InputBufferInfo {
    double sampleRate;
    int samplesPerBlock;
    size_t bufferLength;
};

template <class Type>
struct MultiBuffer {
    mk2::container::fixed_array<mk2::container::fixed_array<Type>> buffer;
};
