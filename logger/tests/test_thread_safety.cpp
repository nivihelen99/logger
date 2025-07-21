#include <gtest/gtest.h>
#include "logger/log.hpp"
#include "logger/log_macros.hpp"
#include "logger/console_sink.hpp"
#include <thread>
#include <vector>

void log_messages(int num_messages) {
    for (int i = 0; i < num_messages; ++i) {
        LOG_INFO("Thread %d, message %d", std::this_thread::get_id(), i);
    }
}

TEST(LoggerTest, ThreadSafety) {
    auto console_sink = std::make_shared<logger::ConsoleSink>();
    logger::Logger::instance().add_sink(console_sink);
    logger::Logger::instance().set_log_level(logger::LogLevel::INFO);

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(log_messages, 100);
    }

    for (auto& t : threads) {
        t.join();
    }
}
