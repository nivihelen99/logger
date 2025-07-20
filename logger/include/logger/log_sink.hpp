#pragma once

#include <string_view>

namespace logger {

class LogSink {
public:
    virtual ~LogSink() = default;
    virtual void log(std::string_view msg) = 0;
};

} // namespace logger
