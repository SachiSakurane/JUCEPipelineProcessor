//
// Created by Himatya on 2020/11/09.
//

#pragma once

#include <utility>

template <class ConnectableType, class... Args>
concept ArgsConnectable = requires (ConnectableType &connectable) {
    connectable.process(std::declval<Args>()...);
};

template <class ConnectionType, class ProcessableType>
concept ProcessConnectable = requires (ConnectionType& connectable, ProcessableType& processable) {
    connectable.process(processable.process());
};
