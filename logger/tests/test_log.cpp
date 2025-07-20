#include <gtest/gtest.h>
#include "logger/log.hpp"
#include "logger/log_macros.hpp"
#include "logger/console_sink.hpp"
#include "logger/file_sink.hpp"

TEST(LoggerTest, BasicLog) {
    auto console_sink = std::make_shared<logger::ConsoleSink>();
    logger::Logger::instance().add_sink(console_sink);
    logger::Logger::instance().set_log_level(logger::LogLevel::TRACE);

    LOG_INFO("This is an info message");
    LOG_WARN("This is a warning message with a number: %d", 123);
}

TEST(LoggerTest, FileLog) {
    auto file_sink = std::make_shared<logger::FileSink>("test.log");
    logger::Logger::instance().add_sink(file_sink);
    logger::Logger::instance().set_log_level(logger::LogLevel::DEBUG);

    LOG_DEBUG("This should be in the file");
    LOG_PRINTF(LA_ERROR, ("This is a legacy error message: %s", "some error"));
}
