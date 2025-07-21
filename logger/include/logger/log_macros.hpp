#pragma once

#include "logger/log.hpp"
#include <string>
#include <vector>
#include <cstdio>
#include <sstream>

namespace logger {

template<typename... Args>
std::string format_string(const char* format, Args... args) {
    int size = snprintf(nullptr, 0, format, args...);
    std::vector<char> buf(size + 1);
    snprintf(buf.data(), buf.size(), format, args...);
    return std::string(buf.data());
}

} // namespace logger

// Modern macros
#define LOG_TRACE(...) logger::Logger::instance().log(logger::LogLevel::TRACE, logger::format_string(__VA_ARGS__))
#define LOG_DEBUG(...) logger::Logger::instance().log(logger::LogLevel::DEBUG, logger::format_string(__VA_ARGS__))
#define LOG_INFO(...) logger::Logger::instance().log(logger::LogLevel::INFO, logger::format_string(__VA_ARGS__))
#define LOG_WARN(...) logger::Logger::instance().log(logger::LogLevel::WARN, logger::format_string(__VA_ARGS__))
#define LOG_ERROR(...) logger::Logger::instance().log(logger::LogLevel::ERROR, logger::format_string(__VA_ARGS__))
#define LOG_FATAL(...) logger::Logger::instance().log(logger::LogLevel::FATAL, logger::format_string(__VA_ARGS__))

// Legacy macro
#define LA_CRITICAL logger::LogLevel::FATAL
#define LA_ERROR logger::LogLevel::ERROR
#define LA_WARNING logger::LogLevel::WARN
#define LA_INFO logger::LogLevel::INFO
#define LA_DEBUG logger::LogLevel::DEBUG
#define LA_TRACE logger::LogLevel::TRACE

#define LOG_PRINTF(level, args) \
    do { \
        logger::Logger::instance().log(level, logger::format_string args); \
    } while (0)
