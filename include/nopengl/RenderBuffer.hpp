// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include <utility>

#include "nopengl_config.hpp"
#include "glc.hpp"

namespace nopengl {

    class [[nodiscard]] RenderBuffer final {

        GLuint inner{};

    public:

        RenderBuffer(std::nullptr_t) noexcept {}

        RenderBuffer() noexcept {
            emplace();
        }
        ~RenderBuffer() noexcept {
            reset();
        }
        RenderBuffer(RenderBuffer &&other) noexcept {
            inner = std::exchange(other.inner, 0);
        }
        RenderBuffer& operator=(RenderBuffer &&other) noexcept {
            reset();
            inner = std::exchange(other.inner, 0);
            return *this;
        }
        RenderBuffer(const RenderBuffer&) = delete;
        RenderBuffer& operator=(const RenderBuffer&) = delete;

        [[nodiscard]] GLuint operator*() const noexcept {
            return inner;
        }

        void emplace() noexcept {
            reset();
            glGenRenderbuffers(1, &inner); GLC();
        }

        void reset() noexcept {
            if (inner) {
                glDeleteRenderbuffers(1, &inner); GLC();
            }
            inner = 0;
        }

    };

} // namespace nopengl.