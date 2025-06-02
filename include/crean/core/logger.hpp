#pragma once

#include "crean/core/types.hpp"

#include <format>
#include <print>
#include <sstream>

#define CR_LOG_WARN_ENABLED
#define CR_LOG_INFO_ENABLED

#ifdef CR_DEBUG_MODE
    #define CR_LOG_DEBUG_ENABLED
    #define CR_LOG_TRACE_ENABLED
#endif

namespace crean
{
    enum class LogLevel : usize
    {
        Fatal = 0,
        Error = 1,
        Warn  = 2,
        Info  = 3,
        Debug = 4,
        Trace = 5,
    };

    template<typename... Args>
    std::string format(const char *message, Args &&...args)
    {
        const static auto to_string = [](const auto &value) -> std::string
        {
            std::ostringstream oss;
            oss << value;
            return oss.str();
        };

        auto string_args = std::make_tuple(to_string(std::forward<Args>(args))...);

        return std::vformat(message,
                            std::apply([](auto &&...s_args)
                            {
                                return std::make_format_args(s_args...);
                            },
                            std::move(string_args)));
    }

    template <typename... Args>
    void log(LogLevel level, const char *file_path, int line, const char *message, Args &&...args)
    {
        static const char *tags[6] = {"FATAL", "ERROR", "WARN", "INFO", "DEBUG", "TRACE"};

        const auto get_file_name = [](const char *file_path) -> const char *
        {
            const char *file_name = std::strrchr(file_path, '/');
            if (file_name == nullptr)
            {
                file_name = std::strrchr(file_path, '\\');
            }
            return file_name == nullptr ? file_path : file_name + 1;
        };

        const char *tag = tags[static_cast<int>(level)];

        const std::string formatted_message = format(message, std::forward<Args>(args)...);

        #ifndef _WIN32
            constexpr auto color_red = "\033[31m";
            constexpr auto color_yellow = "\033[33m";
            constexpr auto color_reset = "\033[0m";
        #else
            constexpr auto color_red = "";
            constexpr auto color_yellow = "";
            constexpr auto color_reset = "";
        #endif

        auto color = [level, color_red, color_yellow, color_reset]
        {
            switch (level)
            {
            case LogLevel::Fatal:
            case LogLevel::Error:
                return color_red;
            case LogLevel::Warn:
                return color_yellow;
            default:
                return color_reset;
            }
        }();

        std::println("{}[{}] {}({}): {}{}", color, tag, get_file_name(file_path), line, formatted_message, color_reset);
    }
}

#define CR_FATAL(message, ...) crean::log(crean::LogLevel::Fatal, __FILE__, __LINE__, message, ##__VA_ARGS__)
#define CR_ERROR(message, ...) crean::log(crean::LogLevel::Error, __FILE__, __LINE__, message, ##__VA_ARGS__)

#ifdef CR_LOG_WARN_ENABLED
    #define CR_WARN(message, ...) crean::log(crean::LogLevel::Warn, __FILE__, __LINE__, message, ##__VA_ARGS__)
#else
    #define CR_WARN(message, ...)
#endif

#ifdef CR_LOG_INFO_ENABLED
    #define CR_INFO(message, ...) crean::log(crean::LogLevel::Info, __FILE__, __LINE__, message, ##__VA_ARGS__)
#else
    #define CR_INFO(message, ...)
#endif

#ifdef CR_LOG_DEBUG_ENABLED
    #define CR_DEBUG(message, ...) crean::log(crean::LogLevel::Debug, __FILE__, __LINE__, message, ##__VA_ARGS__)
#else
    #define CR_DEBUG(message, ...)
#endif

#ifdef CR_LOG_TRACE_ENABLED
    #define CR_TRACE(message, ...) crean::log(crean::LogLevel::Trace, __FILE__, __LINE__, message, ##__VA_ARGS__)
#else
    #define CR_TRACE(message, ...)
#endif

#define CR_ASSERT(condition, message, ...) \
    if (!(condition))                      \
    {                                      \
        CR_FATAL(message, ##__VA_ARGS__);  \
        std::abort();                      \
    }

#ifdef CR_DEBUG_MODE
#define CR_DEBUG_ASSERT(condition, message, ...) \
    if (!(condition))                            \
    {                                            \
        CR_FATAL(message, ##__VA_ARGS__);        \
        std::abort();                            \
    }
#else
    #define CR_DEBUG_ASSERT(condition, message, ...)
#endif

#define CR_PANIC(message, ...)        \
    CR_FATAL(message, ##__VA_ARGS__); \
    std::abort();
