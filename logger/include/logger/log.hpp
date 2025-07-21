#pragma once

#include "logger_config.hpp"
#include "log_sink.hpp"

#include <vector>
#include <memory>
#include <string_view>
#include <source_location>

namespace logger {

class Logger {
public:
    static Logger& instance();

    void add_sink(std::shared_ptr<LogSink> sink);
    void set_log_level(LogLevel level);

    void log(LogLevel level, std::string_view msg, std::source_location loc = std::source_location::current());

private:
    Logger() = default;
    std::vector<std::shared_ptr<LogSink>> sinks_;
    LogLevel log_level_ = LogLevel::INFO;
};

} // namespace logger
