# C++ Logger

A flexible and easy-to-use C++ logging library.

This is a header-only C++ logging library that provides a flexible and extensible way to log messages from your application. It supports multiple log levels, various sink types (console, file), and custom message formatting.

## Features

*   **Header-only:** No need to build or link against a separate library.
*   **Multiple Log Levels:** Supports `TRACE`, `DEBUG`, `INFO`, `WARN`, `ERROR`, and `FATAL` log levels.
*   **Multiple Sinks:** Log messages to the console, a file, or create your own custom sinks.
*   **Thread-safe:** Can be used in multi-threaded applications.
*   **Custom Formatting:** Customize the format of your log messages.
*   **Printf-style Formatting:** Use `printf`-style format strings for your log messages.

## Getting Started

To get started, you need to include the `logger/log.hpp` and `logger/console_sink.hpp` headers. Then, you can get the logger instance and add a console sink to it.

```cpp
#include "logger/log.hpp"
#include "logger/console_sink.hpp"

int main() {
    // Get the logger instance
    auto& logger = logger::Logger::instance();

    // Add a console sink
    logger.add_sink(std::make_shared<logger::ConsoleSink>());

    // Log a message
    LOG_INFO("Hello, world!");

    return 0;
}
```

## Building

This project uses CMake to build the library and its tests.

### Prerequisites

*   CMake 3.10 or later
*   A C++17 compliant compiler (e.g., GCC 7 or later, Clang 6 or later)

### Building the Library and Tests

```bash
mkdir build
cd build
cmake ..
make
```

### Running the Tests

```bash
./logger_tests
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Configuration

### Setting the Log Level

You can set the minimum log level for the logger. Messages with a lower log level will be ignored.

```cpp
#include "logger/log.hpp"

int main() {
    auto& logger = logger::Logger::instance();

    // Set the log level to DEBUG
    logger.set_log_level(logger::LogLevel::DEBUG);

    // This message will be logged
    LOG_DEBUG("This is a debug message.");

    // This message will not be logged
    LOG_TRACE("This is a trace message.");

    return 0;
}
```

### Adding Sinks

You can add multiple sinks to the logger. Each sink will receive all log messages that pass the log level filter.

#### Console Sink

The console sink logs messages to the standard output.

```cpp
#include "logger/log.hpp"
#include "logger/console_sink.hpp"

int main() {
    auto& logger = logger::Logger::instance();
    logger.add_sink(std::make_shared<logger::ConsoleSink>());
    LOG_INFO("This message will be logged to the console.");
    return 0;
}
```

#### File Sink

The file sink logs messages to a file.

```cpp
#include "logger/log.hpp"
#include "logger/file_sink.hpp"

int main() {
    auto& logger = logger::Logger::instance();
    logger.add_sink(std::make_shared<logger::FileSink>("my_log.txt"));
    LOG_INFO("This message will be logged to my_log.txt.");
    return 0;
}
```

## Examples

### Logging to Multiple Sinks

You can log messages to multiple sinks at the same time.

```cpp
#include "logger/log.hpp"
#include "logger/console_sink.hpp"
#include "logger/file_sink.hpp"

int main() {
    auto& logger = logger::Logger::instance();

    // Add a console sink and a file sink
    logger.add_sink(std::make_shared<logger::ConsoleSink>());
    logger.add_sink(std::make_shared<logger::FileSink>("my_log.txt"));

    // This message will be logged to the console and to my_log.txt
    LOG_INFO("This is a test message.");

    return 0;
}
```

### Using Different Log Levels

You can use different log levels to indicate the severity of a message.

```cpp
#include "logger/log.hpp"
#include "logger/console_sink.hpp"

int main() {
    auto& logger = logger::Logger::instance();
    logger.add_sink(std::make_shared<logger::ConsoleSink>());

    LOG_TRACE("This is a trace message.");
    LOG_DEBUG("This is a debug message.");
    LOG_INFO("This is an info message.");
    LOG_WARN("This is a warning message.");
    LOG_ERROR("This is an error message.");
    LOG_FATAL("This is a fatal message.");

    return 0;
}
```

### Using Printf-style Formatting

You can use `printf`-style format strings to format your log messages.

```cpp
#include "logger/log.hpp"
#include "logger/console_sink.hpp"

int main() {
    auto& logger = logger::Logger::instance();
    logger.add_sink(std::make_shared<logger::ConsoleSink>());

    int a = 42;
    double b = 3.14;
    const char* c = "hello";

    LOG_INFO("The values are: a = %d, b = %f, c = %s", a, b, c);

    return 0;
}
```
