// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include <utility>

#include "nopengl_config.hpp"
#include "glc.hpp"

namespace nopengl {

    class [[nodiscard]] FrameBuffer final {

        GLuint inner{};

    public:

        FrameBuffer(std::nullptr_t) noexcept {}

        FrameBuffer() noexcept {
            emplace();
        }
        ~FrameBuffer() noexcept {
            reset();
        }
        FrameBuffer(FrameBuffer &&other) noexcept {
            inner = std::exchange(other.inner, 0);
        }
        FrameBuffer& operator=(FrameBuffer &&other) noexcept {
            reset();
            inner = std::exchange(other.inner, 0);
            return *this;
        }
        FrameBuffer(const FrameBuffer&) = delete;
        FrameBuffer& operator=(const FrameBuffer&) = delete;

        [[nodiscard]] GLuint operator*() const noexcept {
            return inner;
        }

        void emplace() noexcept {
            reset();
            glGenFramebuffers(1, &inner); GLC();
        }

        void reset() noexcept {
            if (inner) {
                glDeleteFramebuffers(1, &inner); GLC();
            }
            inner = 0;
        }

    };

    // Related functions.

    inline void bind(const GLenum target, const FrameBuffer &frameBuffer) noexcept {
        glBindFramebuffer(target, *frameBuffer); GLC();
    }

} // namespace nopengl.