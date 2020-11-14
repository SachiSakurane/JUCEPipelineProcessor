//
// Created by Himatya on 2020/11/09.
//

#pragma once

#include <tuple>
#include <utility>

#include "Concepts/Connectable.hpp"
#include "Concepts/Processable.hpp"
#include "Concepts/ReadableBus.hpp"

template <class ConnectionType, class UnaryArgType>
class ProcessableBinder {
public:
    explicit ProcessableBinder(ConnectionType&& connection, UnaryArgType arg) :
        connection {std::forward<ConnectionType>(connection)},
        arg {std::forward<UnaryArgType>(arg)} {
    }

    decltype(auto) process() {
        return std::forward<ConnectionType>(connection).process(
            std::forward<UnaryArgType>(arg));
    }

private:
    ConnectionType&& connection;
    UnaryArgType&& arg;

};

template <class ConnectionType, Processable ProcessableType> requires ProcessConnectable<ConnectionType, ProcessableType>
class ProcessableBinder<ConnectionType, ProcessableType> {
public:
    ProcessableBinder(ConnectionType&& connection, ProcessableType&& processable) :
        connection {std::forward<ConnectionType>(connection)},
        processable {std::forward<ProcessableType>(processable)} {
    }

    decltype(auto) process() {
        return std::forward<ConnectionType>(connection).process(
            std::forward<ProcessableType>(processable).process());
    }

private:
    ConnectionType&& connection;
    ProcessableType&& processable;

};

template <class ConnectionType, class UnaryArgType> requires ArgsConnectable<ConnectionType, UnaryArgType>
ProcessableBinder(ConnectionType&&, UnaryArgType&&) -> ProcessableBinder<ConnectionType, UnaryArgType>;

template <class ConnectionType, Processable ProcessableType> requires ProcessConnectable<ConnectionType, ProcessableType>
ProcessableBinder(ConnectionType&&, ProcessableType&&) -> ProcessableBinder<ConnectionType, ProcessableType>;

// left.process(right)と等価
template <class Type, class ConnectionType> requires ArgsConnectable<ConnectionType, Type>
inline decltype(auto) operator | (Type&& right, ConnectionType&& left) {
    return ProcessableBinder {std::forward<ConnectionType>(left), std::forward<Type>(right)};
}

// left.process(right.process())と等価
template <Processable ProcessableType, class ConnectionType> requires ProcessConnectable<ConnectionType, ProcessableType>
inline decltype(auto) operator | (ProcessableType&& right, ConnectionType&& left) {
    return ProcessableBinder {std::forward<ConnectionType>(left), std::forward<ProcessableType>(right)};
}
