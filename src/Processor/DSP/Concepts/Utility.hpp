//
// Created by Himatya on 2020/11/12.
//

#pragma once

#include <concepts>

namespace owle{
    template<class From, class To>
    concept convertible_to = std::is_convertible_v<From, To> && requires(std::add_rvalue_reference_t<From> (&f)()) {
        static_cast<To>(f());
    };
}
