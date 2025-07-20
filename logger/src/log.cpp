#include "logger/log.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace logger {

Logger& Logger::instance() {
    static Logger instance;
    return instance;
}

void Logger::add_sink(std::shared_ptr<LogSink> sink) {
    sinks_.push_back(sink);
}

void Logger::set_log_level(LogLevel level) {
    log_level_ = level;
}

void Logger::log(LogLevel level, std::string_view msg, std::source_location loc) {
    if (level < log_level_) {
        return;
    }

    std::stringstream ss;
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    ss << "[" << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") << "]";
    ss << " [" << loc.file_name() << ":" << loc.line() << "]";
    ss << " [" << loc.function_name() << "] ";

    switch (level) {
        case LogLevel::TRACE:
            ss << "[TRACE] ";
            break;
        case LogLevel::DEBUG:
            ss << "[DEBUG] ";
            break;
        case LogLevel::INFO:
            ss << "[INFO] ";
            break;
        case LogLevel::WARN:
            ss << "[WARN] ";
            break;
        case LogLevel::ERROR:
            ss << "[ERROR] ";
            break;
        case LogLevel::FATAL:
            ss << "[FATAL] ";
            break;
    }

    ss << msg;

    for (auto& sink : sinks_) {
        sink->log(ss.str());
    }
}

} // namespace logger
