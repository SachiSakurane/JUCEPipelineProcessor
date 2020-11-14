//
// Created by Himatya on 2020/11/07.
//

#pragma once

template <class ProcessableType>
concept Processable = requires (ProcessableType& processable) {
    processable.process();
};
