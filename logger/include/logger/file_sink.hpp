#pragma once

#include "logger/log_sink.hpp"
#include <string>
#include <fstream>

namespace logger {

class FileSink : public LogSink {
public:
    FileSink(const std::string& filename);
    void log(std::string_view msg) override;

private:
    std::ofstream file_;
};

} // namespace logger
