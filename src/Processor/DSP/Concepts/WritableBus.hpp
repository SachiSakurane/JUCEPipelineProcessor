//
// Created by SachiP on 2020/11/12.
//

#pragma once

template <class WritableBusType>
concept WritableBus = requires (WritableBusType& bus) {
    //
};
