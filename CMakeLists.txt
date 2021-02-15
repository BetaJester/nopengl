# Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
# See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
# for details.

cmake_minimum_required(VERSION 3.18)

project(nopengl LANGUAGES CXX C)

include(CMakeDependentOption)
option(NOPENGL_USE_INCLUDED_GLAD "Use the included version of glad" ON)
option(NOPENGL_ENABLE_LOGGING "Log errors add_custom_command warnings" ON)
cmake_dependent_option(NOPENGL_USE_FETCHED_FMT "Get, supply, and use libfmt/fmt" ON "NOPENGL_ENABLE_LOGGING" OFF)
cmake_dependent_option(NOPENGL_BUILD_EXAMPLE "Build a simple example application" OFF "NOPENGL_ENABLE_LOGGING;NOPENGL_USE_FETCHED_FMT;NOPENGL_USE_INCLUDED_GLAD" OFF)

if (${NOPENGL_USE_INCLUDED_GLAD})
	add_library(glad STATIC "thirdparty/glad/src/glad.c")
	target_include_directories(glad PUBLIC "thirdparty/glad/include")
endif()

if (${NOPENGL_USE_FETCHED_FMT})
	include(FetchContent)
	FetchContent_Declare(
		fmt
		GIT_REPOSITORY https://github.com/fmtlib/fmt.git
		GIT_TAG 7.1.3
	)
	FetchContent_MakeAvailable(fmt)
endif()

add_library(nopengl INTERFACE)
target_sources(nopengl INTERFACE
	"include/nopengl/AutoAlpha.hpp"
	"include/nopengl/Buffer.hpp"
	"include/nopengl/FrameBuffer.hpp"
	"include/nopengl/glc.hpp"
	"include/nopengl/logging.hpp"
	"include/nopengl/nopengl.hpp"
	"include/nopengl/Program.hpp"
	"include/nopengl/RenderBuffer.hpp"
	"include/nopengl/Texture.hpp"
	"include/nopengl/VAO.hpp"
	)
target_compile_features(nopengl INTERFACE cxx_std_20)
target_compile_options(nopengl INTERFACE /W4 /WX /permissive-)
configure_file("include/nopengl_config.hpp.in" "${PROJECT_BINARY_DIR}/nopengl/nopengl_config.hpp")
target_include_directories(nopengl INTERFACE "include" "${PROJECT_BINARY_DIR}/nopen")
if (${NOPENGL_USE_INCLUDED_GLAD})
	target_link_libraries(nopengl INTERFACE glad)
endif()
if (${NOPENGL_ENABLE_LOGGING})
	target_link_libraries(nopengl INTERFACE fmt::fmt)
endif()

if (${NOPENGL_BUILD_EXAMPLE})
	add_subdirectory("example")
endif()