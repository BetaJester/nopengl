# Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
# See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
# for details.

add_executable(unittests "main_test.cpp" "weak_test.cpp")
target_compile_features(unittests PRIVATE cxx_std_20)
target_link_libraries(unittests PRIVATE nopengl Catch2::Catch2)
pwropt_target_compile_options(unittests PRIVATE pwr_wall pwr_werror)
catch_discover_tests(unittests)