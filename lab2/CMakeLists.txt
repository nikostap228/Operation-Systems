cmake_minimum_required(VERSION 3.10)
project(ProcessLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создаем библиотеку
add_library(process_runner STATIC
    src/process_runner_unix.cpp
    src/process_runner_win.cpp
)

target_include_directories(process_runner PUBLIC include)

# Создаем тестовую утилиту
add_executable(test_runner test/main.cpp)
target_link_libraries(test_runner PRIVATE process_runner)