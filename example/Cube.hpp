// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include <array>
#include <string_view>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <nopengl/nopengl.hpp>
#include "SimpleProgram.hpp"


class [[nodiscard]] Cube final {

    using Vertex = SimpleProgram::Vertex;

    nopengl::VAO vao{ nullptr };
    nopengl::Buffer vbo{ nullptr };
    nopengl::Buffer vio{ nullptr };

    glm::mat4 model{ glm::identity<glm::mat4>() };
    std::uint32_t u_model_matrix{};

    static constexpr std::array<Vertex, 8> cube_strip{
        Vertex{{ 1.0f,  1.0f,  1.0f,}, {1.0f, 1.0f, 1.0f,}},
        Vertex{{-1.0f,  1.0f,  1.0f,}, {0.0f, 1.0f, 1.0f,}},
        Vertex{{ 1.0f,  1.0f, -1.0f,}, {1.0f, 1.0f, 0.0f,}},
        Vertex{{-1.0f,  1.0f, -1.0f,}, {0.0f, 1.0f, 0.0f,}},
        Vertex{{ 1.0f, -1.0f,  1.0f,}, {1.0f, 0.0f, 1.0f,}},
        Vertex{{-1.0f, -1.0f,  1.0f,}, {0.0f, 0.0f, 1.0f,}},
        Vertex{{-1.0f, -1.0f, -1.0f,}, {0.0f, 0.0f, 0.0f,}},
        Vertex{{ 1.0f, -1.0f, -1.0f,}, {1.0f, 0.0f, 0.0f,}},
    };

    static constexpr std::array<GLushort, 14> cube_elements{
        3, 2, 6, 7, 4, 2, 0,
        3, 1, 6, 5, 4, 1, 0,
    };

public:

    Cube(const nopengl::Program &program) noexcept {

        u_model_matrix = nopengl::uniform_location(program, "u_model_matrix");

        vbo.emplace();
        nopengl::bind(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * cube_strip.size(), cube_strip.data(), GL_STATIC_DRAW); GLC();


        vao.emplace();
        nopengl::bind(vao);
        nopengl::vao_attribute_pointer(program, "a_position", sizeof(Vertex), offsetof(Vertex, position));
        nopengl::vao_attribute_pointer(program, "a_color", sizeof(Vertex), offsetof(Vertex, color));

        vio.emplace();
        nopengl::bind(GL_ELEMENT_ARRAY_BUFFER, vio);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * cube_elements.size(), cube_elements.data(), GL_STATIC_DRAW); GLC();
    }

    void update([[maybe_unused]] const float time_elapsed) noexcept {
        model = glm::rotate(model, glm::radians(40.0f) * time_elapsed, { 0.8f, 1.0f, 0.2f });
    }

    void draw() noexcept {
        nopengl::bind(vao);
        glUniformMatrix4fv(u_model_matrix, 1, false, glm::value_ptr(model)); GLC();
        glDrawElements(GL_TRIANGLE_STRIP, (GLsizei)cube_elements.size(), GL_UNSIGNED_SHORT, nullptr); GLC();
    }
};