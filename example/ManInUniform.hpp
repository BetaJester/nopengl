// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include <glm/mat4x4.hpp>

// Naming things is the hardest part.
struct [[nodiscard]] ManInUniform final {
    glm::mat4 projection_matrix{};
    glm::mat4 view_matrix{};
};