cmake_minimum_required(VERSION 3.12)
project(DateTimeTests)

# Указываем пути
include_directories(
    ${CMAKE_SOURCE_DIR}/DateTime
)

# Основной код
add_library(DateTimeCore STATIC
    DateTime/DateTime.cpp
    DateTime/DateTime.h
)

# Тесты
find_package(GTest REQUIRED)
add_executable(DateTimeTests
    DateTimeTests/DateTimeTests.cpp
)
target_link_libraries(DateTimeTests
    PRIVATE
    DateTimeCore
    GTest::GTest
    GTest::Main
)
