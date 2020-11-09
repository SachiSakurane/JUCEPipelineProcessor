//
// Created by SachiP on 2020/11/09.
//

#pragma once

template <class ProcessorType>
concept Connectable = requires (ProcessorType& processor) {
    typename ProcessorType::ArgType;
    processor.process(std::declval<typename ProcessorType::ArgType>());
};
