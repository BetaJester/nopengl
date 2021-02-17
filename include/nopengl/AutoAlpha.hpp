// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include "nopengl_config.hpp"
#include "glc.hpp"

namespace nopengl {

    class [[nodiscard]] AutoAlpha final {

    public:

        [[nodiscard]] AutoAlpha(const GLenum srcfactor = GL_SRC_ALPHA, const GLenum dstfactor = GL_ONE_MINUS_SRC_ALPHA) noexcept {
            glEnable(GL_BLEND); GLC();
            glDisable(GL_DEPTH_TEST); GLC();
            glBlendFunc(srcfactor, dstfactor); GLC();
        }

        ~AutoAlpha() noexcept {
            glDisable(GL_BLEND); GLC();
            glEnable(GL_DEPTH_TEST); GLC();
        }

        AutoAlpha(const AutoAlpha&) = delete;
        AutoAlpha(AutoAlpha&&) = delete;
        AutoAlpha& operator=(const AutoAlpha&) = delete;
        AutoAlpha& operator=(AutoAlpha&&) = delete;

    };

} // namespace nopengl.