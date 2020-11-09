//
// Created by Himatya on 2020/11/08.
//

#pragma once

#include "../Models/AudioProcessorModel.hpp"
#include "../Models/BufferModel.hpp"

class PassBlock {
public:
    std::weak_ptr<const MultiBuffer<float>> process(const std::weak_ptr<const MultiBuffer<float>>& buffer) {
        return buffer;
    }
};
