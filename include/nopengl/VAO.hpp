// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include <string_view>
#include <utility>

#include "nopengl_config.hpp"
#include "glc.hpp"
#include "gltypes.hpp"
#include "fwd.hpp"

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

    // Related functions.

    void enable_vao_attribute_array(std::uint32_t index) noexcept {
        glEnableVertexAttribArray(index); GLC();
    }

    inline void vao_attribute_pointer(const std::uint32_t index, const std::uint32_t size, const GLenum type, const bool normalized, const std::size_t stride, const std::size_t offset) noexcept {
        glVertexAttribPointer(index, size, type, normalized, (GLsizei)stride, (void *)offset); GLC();
    }

    inline void vao_attribute_pointer(const Program &program, const std::string_view name, const std::size_t stride, const std::size_t offset) noexcept {
        const auto index = attribute_location(program, name);
        GLint asize{};
        GLenum atype{};
        glGetActiveAttrib(*program, index, 0, nullptr, &asize, &atype, nullptr); GLC();
        auto [type, size] = type_and_size(atype);
        vao_attribute_pointer(index, size, type, false, stride, offset);
        enable_vao_attribute_array(index);
    }

    inline void vao_attribute_pointer(const std::string_view name, const std::size_t stride, const std::size_t offset) noexcept {
        const auto program = current_program_weak_copy();
        vao_attribute_pointer(program, name, stride, offset);
    }



} // namesapce nopengl.