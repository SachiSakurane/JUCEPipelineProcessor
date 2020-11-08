//
// Created by Himatya on 2020/11/08.
//

#pragma once

#include "Processable.hpp"

template <class ProcessorType>
concept Connectable = requires (ProcessorType& processor) {
    typename ProcessorType::ArgType;
    typename ProcessorType::ReturnType;
    processor.process(std::declval<typename ProcessorType::ArgType>());
};

template <Processable InProcessableType, Connectable OutProcessableType>
class Connection {
public:
    Connection(InProcessableType& in_processable_type, OutProcessableType& out_processable_type) :
        in {in_processable_type},
        out {out_processable_type} {
    }

    decltype(auto) process() {
        return out.process(in.process());
    }

private:
    InProcessableType& in;
    OutProcessableType& out;
};

template <Processable InProcessableType, Connectable OutProcessableType>
Connection(InProcessableType& , OutProcessableType& ) -> Connection<InProcessableType, OutProcessableType>;

/*
template <Processable ProcessableType, Connectable ConnectableType>
inline decltype(auto) operator | (ProcessableType&& right, ConnectableType&& left) {
    return Connection{std::forward<ProcessableType>(right), std::forward<ConnectableType>(left)};
}*/

template <class Type, Connectable ConnectableType>
inline decltype(auto) operator | (Type&& right, ConnectableType& left) {
    return ProcessableBinder{left, std::forward<Type>(right)};
}
