

# `requirements.md` — Modern C++ Logging System

## 1. Overview

This document defines the functional and non-functional requirements for implementing a **modern, high-performance, flexible logging system in C++**, incorporating the best features of existing libraries like `spdlog`, `glog`, and `Boost.Log`.

The system must support both **modern usage patterns** and **legacy-style printf formatting**, while also embracing C++20 features like `std::source_location`.

---

## 2. Goals

* Support modern and legacy logging styles.
* Enable high-performance, thread-safe, and lock-free logging when possible.
* Capture contextual metadata using `std::source_location`.
* Support multiple output backends (console, file, syslog, ring buffer).
* Enable filtering by log level, module, or category.
* Allow compile-time configuration of log behavior and log stripping for production builds.
* Minimize overhead in performance-critical paths.

---

## 3. Target Environment

| Item                | Value                                     |
| ------------------- | ----------------------------------------- |
| Language            | C++20 (or newer)                          |
| Platform            | POSIX and Linux-focused                   |
| Build System        | CMake                                     |
| Logging Usage Style | Macro-based and function-based            |
| Performance Profile | High-throughput, lock-free where possible |

---

## 4. Functional Requirements

### 4.1 Logging Macros and Format Support

| ID  | Requirement                                                                                         |
| --- | --------------------------------------------------------------------------------------------------- |
| FR1 | Provide logging macros: `LOG_DEBUG`, `LOG_INFO`, `LOG_WARN`, `LOG_ERROR`, `LOG_FATAL`               |
| FR2 | Support both modern formatting (`fmt::format`) and legacy formatting (`printf`-style)               |
| FR3 | Enable macro-style usage compatible with legacy systems: `LA_PRINTF(LA_DEBUG, ("message %d", val))` |
| FR4 | Provide variadic macro support that wraps around internal formatters                                |
| FR5 | Allow compile-time disabling of log levels (e.g., strip `DEBUG` in production builds)               |

### 4.2 Contextual Information and Source Location

| ID  | Requirement                                                                              |
| --- | ---------------------------------------------------------------------------------------- |
| FR6 | Automatically capture file name, line number, function name using `std::source_location` |
| FR7 | Include timestamps and thread IDs in each log line                                       |
| FR8 | Support optional log categories or modules (e.g., `"net.stack"` or `"db.replication"`)   |

### 4.3 Output and Backend Support

| ID   | Requirement                                                                    |
| ---- | ------------------------------------------------------------------------------ |
| FR9  | Support logging to: console (stderr), file, syslog, and in-memory ring buffers |
| FR10 | Support pluggable backends via interface-based architecture                    |
| FR11 | Allow simultaneous multi-backend output (e.g., console + file)                 |
| FR12 | Support log file rotation, size limits, and timestamped filenames              |
| FR13 | Allow async logging via a lock-free or thread-pooled queue system              |

### 4.4 Configuration and Filtering

| ID   | Requirement                                                                               |
| ---- | ----------------------------------------------------------------------------------------- |
| FR14 | Log level filtering at runtime and compile-time (e.g., disable verbose in release builds) |
| FR15 | Allow filtering by module name, category, or tag                                          |
| FR16 | Support environment-variable or config-file based initialization (`LOG_LEVEL=INFO`)       |
| FR17 | Allow per-sink log level customization (e.g., INFO to console, DEBUG to file)             |

### 4.5 Formatting & Presentation

| ID   | Requirement                                                                                   |
| ---- | --------------------------------------------------------------------------------------------- |
| FR18 | Support customizable log message formats (template: `[LEVEL] [timestamp] [file:line] msg`)    |
| FR19 | Color-coded output to console based on log severity (configurable ANSI colors)                |
| FR20 | Optional JSON log formatting for integration with structured log collectors (e.g., ELK stack) |

---

## 5. Non-Functional Requirements

| ID   | Requirement                                                                                            |
| ---- | ------------------------------------------------------------------------------------------------------ |
| NFR1 | Logging should add **<1µs** per log call in typical INFO-level scenarios                               |
| NFR2 | Logging system must be **thread-safe and lock-free** for common operations (e.g., ring buffer enqueue) |
| NFR3 | Macros must compile away completely for disabled levels (no side effects)                              |
| NFR4 | Build should produce minimal additional dependencies; external libraries like `fmt` are acceptable     |
| NFR5 | Portable to Linux, WSL, and containerized environments                                                 |
| NFR6 | Unit test coverage must include all major log levels, formatting types, and concurrency scenarios      |

---

## 6. Optional Advanced Features

| Feature               | Description                                                                         |
| --------------------- | ----------------------------------------------------------------------------------- |
| Dynamic Log Level     | Change log levels on-the-fly without restart                                        |
| Tagging System        | Add arbitrary tags to log messages for filtering (`LOG(INFO, "net", "connection")`) |
| Metrics Integration   | Track number of messages per level/module for Prometheus, statsd, etc.              |
| Signal-safe Logging   | Support minimal logging even from signal handlers or fatal crash states             |
| External Sink Plugins | Allow custom log sink plugins (e.g., Kafka, gRPC, Elasticsearch)                    |

---

## 7. Example Usage

### 7.1 Modern Style

```cpp
LOG_INFO("Connected to server {}:{}", host, port);
```

### 7.2 Legacy-Compatible Style

```cpp
LOG_PRINTF(TRACE_DBG, ("Connected to server  %s %d", host_name, port));
```

### 7.3 Context-Aware Output

```
[INFO] [2025-07-18 14:12:03.123] [main.cpp:45][connect()] Connection established to 192.168.1.1:443
```

---

## 8. Deliverables

* `log.hpp` / `log.cpp` – main logging interface and implementation
* `log_backend.hpp` – abstract sink interface
* `log_console_sink.cpp`, `log_file_sink.cpp`, `log_syslog_sink.cpp`
* `log_macros.hpp` – macro definitions with `source_location`
* Sample app: `examples/basic_logger.cpp`
* Unit tests: `tests/test_log.cpp`
* Benchmarks: `bench/bench_log_perf.cpp`
* README with build and usage instructions

---

## 9. Libraries to Consider

* [ConcurrentQueue](https://github.com/cameron314/concurrentqueue): For lock-free queues
* [spdlog](https://github.com/gabime/spdlog): As a reference and potential backend


