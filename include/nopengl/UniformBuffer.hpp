// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include <string>

#include "nopen_config.hpp"
#include "Buffer.hpp"
#include "nopengl.hpp"
#include "logging.hpp"

namespace nopengl {

    template<typename T>
    class [[nodiscard]] UniformBuffer final {

        T m_data{};
        const GLuint m_binding;
        nopengl::Buffer m_buffer;
        const std::string m_name;

    public:

        [[nodiscard]] UniformBuffer(const GLuint binding, const std::string& name) noexcept
            : m_binding{ binding }, m_name{ name }
        {
            glBindBuffer(GL_UNIFORM_BUFFER, *m_buffer); GLC();
            glBindBufferBase(GL_UNIFORM_BUFFER, m_binding, *m_buffer); GLC();
            glBufferData(GL_UNIFORM_BUFFER, sizeof(T), nullptr, GL_DYNAMIC_DRAW); GLC();
        }
        UniformBuffer(UniformBuffer&&) noexcept = default;
        UniformBuffer& operator=(UniformBuffer&&) = default;
        UniformBuffer(const UniformBuffer&) = delete;
        UniformBuffer& operator=(const UniformBuffer&) = delete;

        void bind_to_program(const nopengl::Program &program) noexcept {
            const GLuint index = glGetUniformBlockIndex(*program, m_name.c_str()); GLC();
            if (index == GL_INVALID_INDEX) {
                NOPENGL_LOGGER("Program has no uniform block {}", m_name);
            }
            glUniformBlockBinding(*program, index, m_binding); GLC();
        }

        [[nodiscard]] T& data() noexcept { return m_data; }
        [[nodiscard]] T* operator->() noexcept { return &m_data; }
        [[nodiscard]] T& operator*() noexcept { return m_data; }

        void synch() noexcept {
            glBindBuffer(GL_UNIFORM_BUFFER, *m_buffer); GLC();
            glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(T), &m_data); GLC();
        }

    };

} // namespace nopengl.