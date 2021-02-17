# Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
# See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
# for details.

# This simply tests that each header file can be ideally be used in isolation.

function(ngl_standalone name)
	set(app ${name}_standalone)
	file(WRITE "standalone.cpp" "#include <nopengl/${name}.hpp>")
	add_library(${app} "standalone.cpp")
	target_compile_features(${app} PRIVATE cxx_std_20)
	target_compile_definitions(${app} PRIVATE STANDALONE_HEADER=${name})
	pwropt_target_compile_options(${app} PRIVATE pwr_wall pwr_werror)
	target_link_libraries(${app} PRIVATE nopengl)
endfunction()

file(GLOB headers "../../include/nopengl/*.hpp")
foreach(header ${headers})
	get_filename_component(cleanheader "${header}" NAME_WE)
	ngl_standalone(${cleanheader})
endforeach()