// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include <chrono>
#include <concepts>

template<std::floating_point T>
class [[nodiscard]] Timer final {

    std::chrono::high_resolution_clock::time_point timeLast{ std::chrono::high_resolution_clock::now() };
    std::chrono::duration<T> timeElapsed;

public:

    void tick() noexcept {
        std::chrono::high_resolution_clock::time_point timeNow = std::chrono::high_resolution_clock::now();
        timeElapsed = timeNow - timeLast;
        timeLast = timeNow;
    }

    T elapsed() const noexcept {
        return timeElapsed.count();
    }


};