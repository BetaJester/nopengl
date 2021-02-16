// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include <utility>

#include "nopengl_config.hpp"
#include "glc.hpp"

namespace nopengl {

    class [[nodiscard]] Buffer final {

        GLuint inner{};

    public:

        Buffer(std::nullptr_t) noexcept {}

        Buffer() noexcept {
            emplace();
        }
        ~Buffer() noexcept {
            reset();
        }
        Buffer(Buffer &&other) noexcept {
            inner = std::exchange(other.inner, 0);
        }
        Buffer& operator=(Buffer &&other) noexcept {
            reset();
            inner = std::exchange(other.inner, 0);
            return *this;
        }
        Buffer(const Buffer&) = delete;
        Buffer& operator=(const Buffer&) = delete;

        [[nodiscard]] GLuint operator*() const noexcept {
            return inner;
        }

        void emplace() noexcept {
            reset();
            glGenBuffers(1, &inner); GLC();
        }

        void reset() noexcept {
            if (inner) {
                glDeleteBuffers(1, &inner); GLC();
            }
            inner = 0;
        }

    };

} // namespace nopengl.