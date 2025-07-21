#pragma once

#include "logger/log_sink.hpp"

namespace logger {

class ConsoleSink : public LogSink {
public:
    void log(std::string_view msg) override;
};

} // namespace logger
