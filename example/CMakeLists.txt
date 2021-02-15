# Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
# See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
# for details.

include(FetchContent)
FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 3.3.2
)
FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm.git
	GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glfw glm)

add_executable(ngl_example "example.cpp" "Context.hpp" "Cube.hpp" "ManInUniform.hpp" "Timer.hpp" "SimpleProgram.hpp")
target_compile_features(ngl_example PRIVATE cxx_std_20)
target_compile_options(ngl_example PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /wd4201 /permissive- /Zc:__cplusplus>
	$<$<CXX_COMPILER_ID:Clang,GNU>:-Wall -Wextra -Werror -pedantic-errors -Wno-gnu-inline-cpp-without-extern>
)
target_link_libraries(ngl_example PRIVATE nopengl glfw glm)