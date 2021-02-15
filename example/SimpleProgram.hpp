// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include <nopengl/nopengl.hpp>

class [[nodiscard]] SimpleProgram final {

public:

    struct [[nodiscard]] ShaderLocations final {
        std::uint32_t a_position{};
        std::uint32_t a_color{};
        std::uint32_t u_model_matrix{};
    };

private:

    nopengl::Program prog{ nullptr };
    ShaderLocations locations;

    static constexpr std::string_view vertex_source{
R"glsl(
#version 460
in vec3 a_position;
in vec3 a_color;
out vec3 v_color;
layout(std140) uniform ManInUniform {
 mat4 projection_matrix;
 mat4 view_matrix;
} stuff;
uniform mat4 u_model_matrix;
void main() {
 gl_Position = stuff.projection_matrix * stuff.view_matrix * u_model_matrix * vec4(a_position, 1.0);
 v_color = a_color;
}
)glsl"
    };

    static constexpr std::string_view fragment_source{
R"glsl(
#version 460
in vec3 v_color;
out vec4 o_color;
void main() {
 o_color = vec4(v_color, 1.0);
}
)glsl"
    };

public:

    struct [[nodiscard]] Vertex final {
        glm::vec3 position;
        glm::vec3 color;
    };

    SimpleProgram() noexcept {
        prog = nopengl::build_program(vertex_source, fragment_source);

        locations.a_position = nopengl::attribute_location(prog, "a_position");
        locations.a_color = nopengl::attribute_location(prog, "a_color");
        locations.u_model_matrix = nopengl::uniform_location(prog, "u_model_matrix");
    }

    [[nodiscard]]
    const ShaderLocations& shader_locations() const noexcept { return locations; }

    [[nodiscard]]
    const nopengl::Program &program() const noexcept {
        return prog;
    }

    void use() const noexcept {
        nopengl::validate_ifdebug(prog);
        nopengl::use_program(prog);
    }

};