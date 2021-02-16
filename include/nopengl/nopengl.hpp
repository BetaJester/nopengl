// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include <string>
#include <string_view>
#include <cstdint>

#include "nopengl_config.hpp"
#include "Buffer.hpp"
#include "FrameBuffer.hpp"
#include "fwd.hpp"
#include "glc.hpp"
#include "gltypes.hpp"
#include "Program.hpp"
#include "RenderBuffer.hpp"
#include "Texture.hpp"
#include "VAO.hpp"
#include "logging.hpp"

namespace nopengl {

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

    inline void use_program(const Program &program) noexcept {
        glUseProgram(*program); GLC();
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

    inline void link_program(const Program &program, const std::initializer_list<std::uint32_t>& shaders) noexcept {

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
    inline std::uint32_t uniform_buffer_offset_alignment() noexcept {
        int align{};
        glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &align); GLC();
        return align;
    }

    [[nodiscard]] 
    inline std::uint32_t attribute_location(const Program &program, const std::string_view name) noexcept {
        const auto id = glGetAttribLocation(*program, name.data()); GLC();
        if (id == -1) {
            NOPENGL_LOGGER("Attribute {} is invalid", name);
        }
        return id;
    }

    inline void bind(const Program &program) noexcept {
        use_program(program);
    }

    inline void bind(const GLenum target, const Buffer &buffer) noexcept {
        glBindBuffer(target, *buffer); GLC();
    }

    inline void bind(const VAO &vao) noexcept {
        glBindVertexArray(*vao); GLC();
    }

    inline void bind(const GLenum target, const Texture &texture) noexcept {
        glBindTexture(target, *texture); GLC();

    }

    inline void bind(const GLenum target, const FrameBuffer &frameBuffer) noexcept {
        glBindFramebuffer(target, *frameBuffer); GLC();
    }

    inline void bind(const GLenum target, const RenderBuffer &renderBuffer) noexcept {
        glBindRenderbuffer(target, *renderBuffer); GLC();
    }

    inline void viewport_scissor(const int x, const int y, const int width, const int height) {
        glViewport(x, y, width, height); GLC();
        glScissor(x, y, width, height); GLC();
    }

} // namespace nopengl.