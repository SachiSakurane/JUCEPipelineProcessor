//
// Created by Himatya on 2020/11/07.
//

#pragma once

#include <tuple>
#include <utility>

#include "Connectable.hpp"

template <class ProcessorType>
concept Processable = requires (ProcessorType& processor) {
    processor.process();
};

template <class Type, class... Args>
class ProcessableBinder {
public:
    explicit ProcessableBinder(Type&& processable, Args&&... args) :
        parent {std::forward<Type>(processable)},
        tuple {std::forward<Args>(args)...} {
    }

    decltype(auto) process() {
        // bindだとplaceholderが必要
        // return std::bind(&std::remove_reference_t<Type>::process, &std::forward<Type>(parent));
        // return std::apply(std::bind(&std::remove_reference_t<Type>::process, &std::forward<Type>(parent)), tuple);
    }

private:
    Type&& parent;
    std::tuple<Args...> tuple;
};

template <class Type, class... Args>
ProcessableBinder(Type&&, Args&&...) -> ProcessableBinder<Type, Args...>;
