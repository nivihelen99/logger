#pragma once

#include <cstdint>

namespace logger {

enum class LogLevel : uint8_t {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

} // namespace logger
