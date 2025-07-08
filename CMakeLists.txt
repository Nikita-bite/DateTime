cmake_minimum_required(VERSION 3.12)
project(DateTimeTests)

# Указываем пути к исходникам
include_directories(
    ${CMAKE_SOURCE_DIR}/DateTime
)

# Основной код
add_library(DateTimeCore STATIC
    ${CMAKE_SOURCE_DIR}/DateTime/DateTime.cpp
    ${CMAKE_SOURCE_DIR}/DateTime/DateTime.h
)

# Тесты
find_package(GTest REQUIRED)
add_executable(DateTimeTests
    ${CMAKE_SOURCE_DIR}/DateTimeTests/DateTimeTests.cpp
)
target_link_libraries(DateTimeTests
    PRIVATE
    DateTimeCore
    GTest::GTest
    GTest::Main
)

enable_testing()
add_test(NAME DateTimeTests COMMAND DateTimeTests)
