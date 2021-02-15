// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include <string_view>
#include <utility>
#include <nopengl/nopengl.hpp>
#include <GLFW/glfw3.h>

// A simple RAII wrapper for GLFW.
class [[nodiscard]] Context final {

    GLFWwindow *window{};

public:

    // A concise way to configure a Context.
    struct [[nodiscard]] Config final {
        int version_major{ 3 };
        int version_minor{ 3 };
        int samples{ 0 };
        int window_width{ 800 };
        int window_height{ 600 };
        std::string_view window_title{ "nopengl application" };
    };

    // Construct a context from a configuration.
    Context(const Config &config) noexcept {
        if (!glfwInit()) {
            NOPENGL_LOGGER("Could not init GLFW");
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.version_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.version_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, config.samples);

        window = glfwCreateWindow(config.window_width, config.window_height, config.window_title.data(), nullptr, nullptr);
        if (window == nullptr) {
            NOPENGL_LOGGER("GLFW window could not be created");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            NOPENGL_LOGGER("OpenGL loader failed");
            glfwDestroyWindow(window);
            glfwTerminate();
            window = nullptr;
            return;
        }
    }

    ~Context() noexcept {
        // Always safe to destoy nullptr if construction fails.
        glfwDestroyWindow(window);
        // Always safe to call if GLFW isn't inited sucessfully.
        glfwTerminate();
    }

    // We don't want copies of this.
    Context(const Context &) = delete;
    Context& operator=(const Context &) = delete;

    Context(Context &&other) noexcept {
        window = std::exchange(other.window, nullptr);
    }

    Context& operator=(Context &&other) noexcept {
        window = std::exchange(other.window, nullptr);
        return *this;
    }

    // Should the window/context close.
    [[nodiscard]]
    bool should_close() const noexcept { 
        return glfwWindowShouldClose(window); 
    }
    
    // Check the validity of the context.
    [[nodiscard]]
    bool good() const noexcept { 
        return window != nullptr; 
    }

    // Process events. Necessary in main loop.
    void process_events() noexcept {
        glfwPollEvents();
    }

    // Swap buffers, if that's your jam.
    void swap_buffers() noexcept {
        glfwSwapBuffers(window);
    }

};