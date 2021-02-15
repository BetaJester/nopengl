// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include <utility>

#include "nopen_config.hpp"
#include "glc.hpp"

namespace nopengl {

    class [[nodiscard]] Program final {

        GLuint inner{};

    public:
        Program(std::nullptr_t) noexcept {}
        
        Program() noexcept {
            emplace();
        }
        ~Program() noexcept {
            reset();
        }
        Program(Program &&other) noexcept {
            inner = std::exchange(other.inner, 0);
        }
        Program& operator=(Program &&other) noexcept {
            reset();
            inner = std::exchange(other.inner, 0);
            return *this;
        }
        Program(const Program&) = delete;
        Program& operator=(const Program&) = delete;

        [[nodiscard]] GLuint operator*() const noexcept {
            return inner;
        }

        void emplace() noexcept {
            reset();
            inner = glCreateProgram(); GLC();
        }

        void reset() noexcept {
            if (inner) {
                glDeleteProgram(inner); GLC();
            }
            inner = 0;
        }

    };

} // namespace nopengl.