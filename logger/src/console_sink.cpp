#include "logger/console_sink.hpp"
#include <iostream>

namespace logger {

void ConsoleSink::log(std::string_view msg) {
    std::cout << msg << std::endl;
}

} // namespace logger
