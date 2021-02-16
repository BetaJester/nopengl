// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include <utility>
#include <cstdint>

#include "nopengl_config.hpp"
#include "glc.hpp"

namespace nopengl {

    class [[nodiscard]] Program final {

        GLuint inner{};

        Program(const GLuint value) : inner{ value } {}

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
            return inner & 0x0000FFFF;
        }

        void emplace() noexcept {
            reset();
            inner = glCreateProgram(); GLC();
            inner = (inner << 16) | inner;
        }

        void reset() noexcept {
            if (inner) {
                glDeleteProgram(inner >> 16); GLC();
            }
            inner = 0;
        }

        [[nodiscard]]
        Program weak_copy() const noexcept {
            return Program(inner & 0x0000FFFF);
        }

        friend inline Program current_program_weak_copy() noexcept;

    };

    // Related functions.
    
    inline void use_program(const Program &program) noexcept {
        glUseProgram(*program); GLC();
    }

    inline void bind(const Program &program) noexcept {
        use_program(program);
    }

    [[nodiscard]]
    inline Program current_program_weak_copy() noexcept {
        GLint program{};
        glGetIntegerv(GL_CURRENT_PROGRAM, &program); GLC();
        if (program == -1) {
            NOPENGL_LOGGER("No current program for vao_attribute_pointer");
        }
        return Program(program);
    }

    [[nodiscard]]
    inline bool shader_compile_status(const std::uint32_t shader) noexcept {
        int returnValue;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &returnValue); GLC();
        return returnValue;
    }

    [[nodiscard]]
    inline bool program_link_status(const Program &program) noexcept {
        int returnValue;
        glGetProgramiv(*program, GL_LINK_STATUS, &returnValue); GLC();
        return returnValue;
    }

    [[nodiscard]]
    inline bool program_validation_status(const Program &program) noexcept {
        int returnValue;
        glGetProgramiv(*program, GL_VALIDATE_STATUS, &returnValue); GLC();
        return returnValue;
    }

    [[nodiscard]]
    inline std::string get_shader_info_log(const std::uint32_t shader) noexcept {
        int length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length); GLC();
        if (length > 1) {
            const auto realLength = static_cast<std::size_t>(length);
            std::string log(realLength, '\0');
            glGetShaderInfoLog(shader, length, nullptr, log.data()); GLC();
            return log;
        }
        return "No infolog";
    }

    [[nodiscard]]
    inline std::string get_program_info_log(const Program &program) noexcept {
        int length = 0;
        glGetProgramiv(*program, GL_INFO_LOG_LENGTH, &length); GLC();
        if (length > 1) {
            const auto realLength = static_cast<size_t>(length);
            std::string log(realLength, '\0');
            glGetProgramInfoLog(*program, length, nullptr, log.data()); GLC();
            return log;
        }
        return "No infolog";
    }

    [[nodiscard]]
    inline std::uint32_t build_shader(const std::uint32_t type, const std::string_view source) noexcept {
        const GLuint shader = glCreateShader(type); GLC();

        const GLchar *sourceGLchar[] = { source.data() };
        glShaderSource(shader, 1, sourceGLchar, nullptr); GLC();

        glCompileShader(shader); GLC();

        if (!nopengl::shader_compile_status(shader)) {

            const std::string log = nopengl::get_shader_info_log(shader);
            NOPENGL_LOGGER("Could not compile shader: {}", log);
            glDeleteShader(shader); GLC();

        }

        return shader;
    }

    inline void attach_shader(const Program &program, const std::uint32_t shader) noexcept {
        glAttachShader(*program, shader); GLC();
    };

    inline void link_program(const Program &program, const std::initializer_list<std::uint32_t> &shaders) noexcept {

        glLinkProgram(*program); GLC();
        if (!nopengl::program_link_status(program)) {

            const std::string log = nopengl::get_program_info_log(program);
            NOPENGL_LOGGER("Program linking failed: {}", log);
            glDeleteProgram(*program); GLC();

        }

        for (auto shader : shaders) {
            glDetachShader(*program, shader); GLC();
            glDeleteShader(shader); GLC();
        }

    }

    inline void validate_program(const Program &program) noexcept {
        glValidateProgram(*program); GLC();
        if (!nopengl::program_validation_status(program)) {

            const std::string log = nopengl::get_program_info_log(program);
            NOPENGL_LOGGER("Program validation failed: {}", log);
            glDeleteProgram(*program); GLC();

        }
    }

    inline void validate_ifdebug([[maybe_unused]] const Program &program) noexcept {
#ifndef NDEBUG
        validate_program(program);
#endif // !NDEBUG

    }

    [[nodiscard]]
    inline Program build_program(const std::string_view vertexSource, const std::string_view fragmentSource) noexcept {
        const auto vertexShader = nopengl::build_shader(GL_VERTEX_SHADER, vertexSource);
        const auto fragmentShader = nopengl::build_shader(GL_FRAGMENT_SHADER, fragmentSource);

        Program program;

        nopengl::attach_shader(program, vertexShader);
        nopengl::attach_shader(program, fragmentShader);

        nopengl::link_program(program, { vertexShader, fragmentShader });

        return program;
    }

    [[nodiscard]]
    inline std::uint32_t uniform_location(const Program &program, const std::string_view name) noexcept {
        const auto id = glGetUniformLocation(*program, name.data()); GLC();
        if (id == -1) {
            NOPENGL_LOGGER("Uniform {} is invalid", name);
        }
        return id;
    }

    [[nodiscard]]
    inline std::uint32_t attribute_location(const Program &program, const std::string_view name) noexcept {
        const auto id = glGetAttribLocation(*program, name.data()); GLC();
        if (id == -1) {
            NOPENGL_LOGGER("Attribute {} is invalid", name);
        }
        return id;
    }

} // namespace nopengl.