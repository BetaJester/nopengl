// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include <type_traits>
#include "nopen_config.hpp"

namespace nopengl {

    template<typename T>
    [[nodiscard]]
    constexpr GLenum type_of() noexcept;

    [[nodiscard]]
    inline constexpr auto type_and_size(const GLenum attrtype) noexcept {
        struct ts { GLenum type; GLint size; };
        switch (attrtype) {
        case GL_FLOAT_VEC2: return ts{ GL_FLOAT, 2 };
        case GL_FLOAT_VEC3: return ts{ GL_FLOAT, 3 };
        case GL_FLOAT_VEC4: return ts{ GL_FLOAT, 4 };
        case GL_DOUBLE_VEC2: return ts{ GL_DOUBLE, 2 };
        case GL_DOUBLE_VEC3: return ts{ GL_DOUBLE, 3 };
        case GL_DOUBLE_VEC4: return ts{ GL_DOUBLE, 4 };
        case GL_INT_VEC2: return ts{ GL_INT, 2 };
        case GL_INT_VEC3: return ts{ GL_INT, 3 };
        case GL_INT_VEC4: return ts{ GL_INT, 4 };
        case GL_UNSIGNED_INT_VEC2: return ts{ GL_UNSIGNED_INT, 2 };
        case GL_UNSIGNED_INT_VEC3: return ts{ GL_UNSIGNED_INT, 3 };
        case GL_UNSIGNED_INT_VEC4: return ts{ GL_UNSIGNED_INT, 4 };
        case GL_BOOL_VEC2: return ts{ GL_BOOL, 2 };
        case GL_BOOL_VEC3: return ts{ GL_BOOL, 3 };
        case GL_BOOL_VEC4: return ts{ GL_BOOL, 4 };
        default: return ts{ attrtype, 1 };
        }
    }

    // One liners for brevity.
    template<> [[nodiscard]] constexpr GLenum type_of<float>() noexcept { return GL_FLOAT; }
    template<> [[nodiscard]] constexpr GLenum type_of<double>() noexcept { return GL_DOUBLE; }
    template<> [[nodiscard]] constexpr GLenum type_of<std::int8_t>() noexcept { return GL_BYTE; }
    template<> [[nodiscard]] constexpr GLenum type_of<std::uint8_t>() noexcept { return GL_UNSIGNED_BYTE; }
    template<> [[nodiscard]] constexpr GLenum type_of<std::int16_t>() noexcept { return GL_SHORT; }
    template<> [[nodiscard]] constexpr GLenum type_of<std::uint16_t>() noexcept { return GL_UNSIGNED_SHORT; }
    template<> [[nodiscard]] constexpr GLenum type_of<std::int32_t>() noexcept { return GL_INT; }
    template<> [[nodiscard]] constexpr GLenum type_of<std::uint32_t>() noexcept { return GL_UNSIGNED_INT; }

} // namespace nopengl.