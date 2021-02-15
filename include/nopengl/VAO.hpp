// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include <utility>

#include "nopen_config.hpp"
#include "glc.hpp"

namespace nopengl {

    class [[nodiscard]] VAO final {

        GLuint inner{};

    public:
        VAO(std::nullptr_t) noexcept {}
        VAO() noexcept {
            emplace();
        }
        ~VAO() noexcept {
            reset();
        }
        VAO(VAO &&other) noexcept {
            inner = std::exchange(other.inner, 0);
        }
        VAO& operator=(VAO &&other) noexcept {
            reset();
            inner = std::exchange(other.inner, 0);
            return *this;
        }
        VAO(const VAO&) = delete;
        VAO& operator=(const VAO&) = delete;

        [[nodiscard]] GLuint operator*() const noexcept {
            return inner;
        }

        void emplace() noexcept {
            reset();
            glGenVertexArrays(1, &inner); GLC();
        }

        void reset() noexcept {
            if (inner) {
                glDeleteVertexArrays(1, &inner); GLC();
            }
            inner = 0;
        }

    };

} // namesapce nopengl.