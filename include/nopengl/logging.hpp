// Copyright (C) 2021 Glenn Duncan <betajester@betajester.com>
// See README.md, LICENSE, or go to https://github.com/BetaJester/nopengl
// for details.

#pragma once

#include "nopen_config.hpp"

#if NOPENGL_ENABLE_LOGGING()

#include <string_view>
#include <utility>
#include <fmt/format.h>

namespace nopengl::logging {

    using logging_f = void(*)(std::string_view str);

    void stdout_logger(std::string_view str);
    static inline logging_f logger_function = stdout_logger;

    void quicklog(std::string_view str) {
        if (logger_function) {
            logger_function(str);
        }
    }

    template<typename Str, typename ...Args>
    void logger(const Str &str, Args &&...args) {
        quicklog(fmt::format(str, std::forward<Args>(args)...));
        quicklog("\n");
    }

    void stdout_logger(std::string_view str) {
        std::fputs(str.data(), stdout);
    }

    void set_logger(logging_f f) {
        logger_function = f;
    }
    

} // namespace nopengl::logging.

#define NOPENGL_LOGGER(msg, ...) nopengl::logging::logger(msg, ## __VA_ARGS__)

#else

    #define NOPENGL_LOGGER(msg, ...)

#endif