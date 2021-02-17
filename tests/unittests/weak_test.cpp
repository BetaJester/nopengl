// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#include <catch2/catch.hpp>
#include <nopengl/weak.hpp>

TEST_CASE("Weakening works", "[weak]") {

    const std::uint32_t start{ 5 };

    REQUIRE(nopengl::strengthen(start) != 5);
    REQUIRE(nopengl::weaken(nopengl::strengthen(start)) == 5);
    REQUIRE(nopengl::clean(nopengl::strengthen(start)) == 5);
    REQUIRE(nopengl::clean(start) == 0);


}