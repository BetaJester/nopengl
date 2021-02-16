// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include <utility>

#include "nopengl_config.hpp"
#include "glc.hpp"

namespace nopengl {

    class [[nodiscard]] Texture final {

        GLuint inner{};

    public:
        Texture(std::nullptr_t) noexcept {}

        Texture() noexcept {
            emplace();
        }
        ~Texture() noexcept {
            reset();
        }
        Texture(Texture &&other) noexcept {
            inner = std::exchange(other.inner, 0);
        }
        Texture& operator=(Texture &&other) noexcept {
            reset();
            inner = std::exchange(other.inner, 0);
            return *this;
        }
        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        [[nodiscard]] GLuint operator*() const noexcept {
            return inner;
        }

        void emplace() noexcept {
            reset();
            glGenTextures(1, &inner); GLC();
        }

        void reset() noexcept {
            if (inner) {
                glDeleteTextures(1, &inner); GLC();
            }
            inner = 0;
        }

    };

    // Related functions.

    inline void bind(const GLenum target, const Texture &texture) noexcept {
        glBindTexture(target, *texture); GLC();
    }

} // namespace nopengl.