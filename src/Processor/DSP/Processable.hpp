//
// Created by Himatya on 2020/11/07.
//

#pragma once

#include <tuple>
#include <utility>

template <class ProcessorType>
concept Processable = requires (ProcessorType& processor) {
    processor.process();
};

template <class Type, class... Args>
class ProcessableBinder {
public:
    explicit ProcessableBinder(Type&& processable, Args&&... args) :
        parent {std::forward<Type>(processable)},
        tuple {std::forward<Args>(args)...} {}

    decltype(auto) process() {
        return std::apply([this](Args&&...args){
            return std::forward<Type>(parent).process(std::forward<Args>(args)...);
        }, tuple);
    }

private:
    Type&& parent;
    std::tuple<Args...> tuple;
};

template <class Type, class... Args>
ProcessableBinder(Type&&, Args&&...) -> ProcessableBinder<Type, Args...>;
