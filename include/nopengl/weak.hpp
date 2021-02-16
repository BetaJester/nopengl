// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include <cstdint>

namespace nopengl {

    [[nodiscard]]
    inline constexpr std::uint32_t weaken(const std::uint32_t value) noexcept {
        return value & 0x0000FFFF;
    }

    [[nodiscard]]
    inline constexpr std::uint32_t strengthen(const std::uint32_t value) noexcept {
        return (value << 16) | value;
    }

    [[nodiscard]]
    inline constexpr std::uint32_t clean(const std::uint32_t value) noexcept {
        return value >> 16;
    }

} // namespace nopengl.