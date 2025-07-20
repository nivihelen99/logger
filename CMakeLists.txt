cmake_minimum_required(VERSION 3.10)
project(logger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- GoogleTest ---
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
# --- End GoogleTest ---


enable_testing()

# --- logger library ---
add_library(logger STATIC
    logger/src/log.cpp
    logger/src/console_sink.cpp
    logger/src/file_sink.cpp
)
target_include_directories(logger PUBLIC logger/include)
# --- End logger library ---

# --- Tests ---
add_executable(run_tests
    logger/tests/test_log.cpp
    logger/tests/test_thread_safety.cpp
)
target_link_libraries(run_tests gtest_main logger)
add_test(NAME run_tests COMMAND run_tests)
# --- End Tests ---

# --- Examples ---
add_executable(example_basic logger/examples/example_basic.cpp)
target_link_libraries(example_basic logger)

add_executable(example_legacy_macro logger/examples/example_legacy_macro.cpp)
target_link_libraries(example_legacy_macro logger)
# --- End Examples ---
