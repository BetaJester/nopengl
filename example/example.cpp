// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#include <nopengl/UniformBuffer.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Context.hpp"
#include "Cube.hpp"
#include "ManInUniform.hpp"
#include "Timer.hpp"
#include "SimpleProgram.hpp"

int main() {

    Context::Config config{
        .samples = 4,
        .window_title = "nopen example",
    };

    Context context{ config };

    if (!context.good()) {
        NOPENGL_LOGGER("Failed to build context");
        return 1;
    }

    glClearColor(0.8f, 0.7f, 0.6f, 1.0f); GLC();
    glEnable(GL_DEPTH_TEST); GLC();
    glEnable(GL_CULL_FACE); GLC();

    SimpleProgram simple_program;
    Cube cube(simple_program.program());

    const float aspect_ratio = static_cast<float>(config.window_width) / config.window_height;
    const float fov = 45.0f;

    nopengl::UniformBuffer<ManInUniform> uniforms(0, "ManInUniform");
    uniforms.data().projection_matrix = glm::perspective(fov, aspect_ratio, 0.1f, 100.0f);
    uniforms.data().view_matrix = glm::lookAt(glm::vec3{ 2.0f, 3.0f, 3.0f }, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{ 0.0f, 1.0f, 0.0f });
    uniforms.bind_to_program(simple_program.program());
    uniforms.synch();

    Timer<float> timer;

    simple_program.use();
    while (!context.should_close()) {
        context.process_events();
        timer.tick();

        cube.update(timer.elapsed());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GLC();
        cube.draw();

        context.swap_buffers();
    }
}