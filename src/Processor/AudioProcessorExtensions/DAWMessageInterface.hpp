//
// Created by Himatya on 2020/10/26.
//

#pragma once

namespace AudioProcessorExtensions {
    struct DAWMessageInterface {
        virtual ~DAWMessageInterface() = default;
        virtual double getTailLengthSeconds() const = 0;
    };
}