//
// Created by Himatya on 2020/11/09.
//

#pragma once

#include <tuple>
#include <utility>

#include "Connectable.hpp"
#include "Processable.hpp"

template <class ConnectionType, class... Args>
class ProcessableBinder {
public:
    explicit ProcessableBinder(ConnectionType&& connection, Args&&... args) :
        connection {std::forward<ConnectionType>(connection)},
        tuple {std::forward_as_tuple(std::forward<Args>(args)...)} {
    }

    decltype(auto) process() {
        return std::apply(&std::remove_cvref_t<ConnectionType>::process,
                          std::tuple_cat(
                              std::forward_as_tuple(std::forward<ConnectionType>(connection)),
                              tuple));
    }

private:
    ConnectionType&& connection;
    std::tuple<Args...> tuple;

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

template <class ConnectionType, class... Args> requires ArgsConnectable<ConnectionType, Args...>
ProcessableBinder(ConnectionType&&, Args&&...) -> ProcessableBinder<ConnectionType, Args...>;

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