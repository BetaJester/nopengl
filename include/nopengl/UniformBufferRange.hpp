// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include <array>
#include <string>
#include <cstdint>

#include "nopengl_config.hpp"
#include "nopengl.hpp"

namespace nopengl {

    template<typename T, std::size_t N>
    class [[nodiscard]] UniformBufferRange final {

        std::array<T, N> m_data;
        const GLuint m_binding;
        nopengl::Buffer m_buffer;
        const std::string m_name;
        std::size_t m_current{};
        const std::size_t m_size_each;

        // Maths courtesy of https://stackoverflow.com/a/23928177
        template<typename T>
        [[nodiscard]] static constexpr std::size_t size_for_alignment(const std::size_t alignment) noexcept {
            return ((sizeof(T) + alignment - 1) / alignment) * alignment;
        }

    public:

        [[nodiscard]] UniformBufferRange(const GLuint binding, const std::string& name, const std::size_t alignment) noexcept
            : m_binding{ binding }, m_name{ name }, m_size_each{ size_for_alignment<T>(alignment) }
        {
            nopengl::bind(GL_UNIFORM_BUFFER, m_buffer);
            glBindBufferBase(GL_UNIFORM_BUFFER, m_binding, *m_buffer); GLC();
            glBufferData(GL_UNIFORM_BUFFER, m_size_each*N, nullptr, GL_DYNAMIC_DRAW); GLC();
        }
        UniformBufferRange(UniformBufferRange&&) noexcept = default;
        UniformBufferRange& operator=(UniformBufferRange&&) noexcept = default;
        UniformBufferRange(const UniformBufferRange&) = delete;
        UniformBufferRange& operator=(const UniformBufferRange&) = delete;

        void bind_to_program(const nopengl::Program &program) noexcept {
            const GLuint index = glGetUniformBlockIndex(*program, m_name.c_str()); GLC();
            if (index == GL_INVALID_INDEX) {
                NOPENGL_LOGGER("Program has no uniform block {}", m_name);
            }
            glUniformBlockBinding(*program, index, m_binding); GLC();
        }

        [[nodiscard]] T& data() noexcept { return m_data[m_current]; }
        [[nodiscard]] T* operator->() noexcept { return &m_data[m_current]; }
        [[nodiscard]] T& operator*() noexcept { return m_data[m_current]; }

        void set_current(const std::size_t index) noexcept {
            m_current = index;
            nopengl::bind(GL_UNIFORM_BUFFER, m_buffer);
            glBindBufferRange(GL_UNIFORM_BUFFER, m_binding, *m_buffer, m_size_each * m_current, sizeof(T)); GLC();
        }

        void synch_current() noexcept {
            nopengl::bind(GL_UNIFORM_BUFFER, m_buffer);
            glBufferSubData(GL_UNIFORM_BUFFER, m_size_each * m_current, sizeof(T), &m_data[m_current]); GLC();
        }

    };

} // namespace nopengl.