#include "logger/file_sink.hpp"

namespace logger {

FileSink::FileSink(const std::string& filename) {
    file_.open(filename, std::ios::app);
}

void FileSink::log(std::string_view msg) {
    if (file_.is_open()) {
        file_ << msg << std::endl;
    }
}

} // namespace logger
