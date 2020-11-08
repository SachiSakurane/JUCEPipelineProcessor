//
// Created by Himatya on 2020/11/08.
//

#pragma once

#include "../Models/AudioProcessorModel.hpp"
#include "../Models/BufferModel.hpp"

class PassBlock {
public:
    using ArgType = std::weak_ptr<const MultiBuffer<float>>;
    using ReturnType = std::weak_ptr<const MultiBuffer<float>>;

    const ReturnType& process(const ArgType& buffer) {
        return buffer;
    }
};
