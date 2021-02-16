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
    inline std::uint32_t uniform_buffer_offset_alignment() noexcept {
        int align{};
        glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &align); GLC();
        return align;
    }

    inline void viewport_scissor(const int x, const int y, const int width, const int height) {
        glViewport(x, y, width, height); GLC();
        glScissor(x, y, width, height); GLC();
    }

} // namespace nopengl.