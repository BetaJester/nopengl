// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include <string>
#include <string_view>
#include <cstdint>
#include "nopen_config.hpp"

namespace nopengl {

    class Program;
    class Buffer;
    class VAO;
    class Texture;
    class FrameBuffer;
    class RenderBuffer;

    [[nodiscard]]
    inline bool shader_compile_status(const std::uint32_t shader) noexcept;
    [[nodiscard]]
    inline bool program_link_status(const Program &program) noexcept;
    [[nodiscard]]
    inline bool program_validation_status(const Program &program) noexcept;
    [[nodiscard]]
    inline std::string get_shader_info_log(const std::uint32_t shader) noexcept;
    [[nodiscard]]
    inline std::string get_program_info_log(const Program &program) noexcept;
    inline void use_program(const Program &program) noexcept;
    [[nodiscard]]
    inline std::uint32_t build_shader(const std::uint32_t type, const std::string_view source) noexcept;
    inline void attach_shader(const Program &program, const std::uint32_t shader) noexcept;
    inline void link_program(const Program &program, const std::initializer_list<std::uint32_t> &shaders) noexcept;
    inline void validate_program(const Program &program) noexcept;
    inline void validate_ifdebug([[maybe_unused]] const Program &program) noexcept;
    [[nodiscard]]
    inline Program build_program(const std::string_view vertexSource, const std::string_view fragmentSource) noexcept;
    [[nodiscard]]
    inline std::uint32_t uniform_location(const Program &program, const std::string_view name) noexcept;
    [[nodiscard]]
    inline std::uint32_t uniform_buffer_offset_alignment() noexcept;
    [[nodiscard]]
    inline std::uint32_t attribute_location(const Program &program, const std::string_view name) noexcept;
    inline void bind(const Program &program) noexcept;
    inline void bind(const GLenum target, const Buffer &buffer) noexcept;
    inline void bind(const VAO &vao) noexcept;
    inline void bind(const GLenum target, const Texture &texture) noexcept;
    inline void bind(const GLenum target, const FrameBuffer &frameBuffer) noexcept;
    inline void bind(const GLenum target, const RenderBuffer &renderBuffer) noexcept;
    inline void viewport_scissor(const int x, const int y, const int width, const int height);

    // gltypes.hpp
    template<typename T>
    [[nodiscard]]
    constexpr GLenum type_of() noexcept;
    [[nodiscard]]
    inline constexpr auto type_and_size(const GLenum attrtype) noexcept;

} // namespace nopengl.