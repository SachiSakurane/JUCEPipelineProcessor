//
// Created by SachiP on 2020/11/12.
//

#pragma once

#include <mk2/concepts>

template <class BusType>
concept Bus = requires (BusType bus) {
    typename BusType::size_type;
    {bus.size()} -> mk2::convertable_to<typename BusType::size_type>;
};
