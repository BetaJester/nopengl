// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include "nopen_config.hpp"
#include "logging.hpp"

namespace nopengl {

    inline void check_errors(const int line = 0) noexcept {

        for (auto error = glGetError(); error != GL_NO_ERROR; error = glGetError()) {

            switch (error) {
            case GL_NO_ERROR: NOPENGL_LOGGER("Line {}: GL_NO_ERROR got into switch somehow...", line); break;
            case GL_INVALID_ENUM: NOPENGL_LOGGER("Line {}: GL_INVALID_ENUM detected", line); break;
            case GL_INVALID_VALUE: NOPENGL_LOGGER("Line {}: GL_INVALID_VALUE detected", line); break;
            case GL_INVALID_OPERATION: NOPENGL_LOGGER("Line {}: GL_INVALID_OPERATION detected", line); break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: NOPENGL_LOGGER("Line {}: GL_INVALID_FRAMEBUFFER_OPERATION detected", line); break;
            case GL_OUT_OF_MEMORY: NOPENGL_LOGGER("Line {}: GL_OUT_OF_MEMORY detected", line); break;
            default: NOPENGL_LOGGER("Line {}: Unknown gl error detected", line); break;
            }
        }
    }
} // namespace nopengl.

#ifdef NDEBUG
#define GLC()
#else
#define GLC() nopengl::check_errors(__LINE__)
#endif