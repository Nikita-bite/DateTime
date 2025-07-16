cmake_minimum_required(VERSION 3.15)
project(DateTime)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройка путей вывода
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Создаем папки для выходных файлов
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

# Настройка SFML
set(SFML_PATH "C:/SFML-2.6.2")  # Проверьте путь!
set(SFML_DIR "${SFML_PATH}/lib/cmake/SFML")
find_package(SFML 2.6 REQUIRED COMPONENTS system)

# Основное приложение
add_executable(DateTimeApp
    DateTime/main.cpp
    DateTime/DateTime.cpp
)

# Добавляем include-директорию для основного приложения
target_include_directories(DateTimeApp PRIVATE 
    ${CMAKE_SOURCE_DIR}
    ${SFML_INCLUDE_DIR}
)

target_link_libraries(DateTimeApp sfml-system)

# Включение тестирования
enable_testing()

# Подключение GoogleTest
if(EXISTS ${CMAKE_SOURCE_DIR}/libs/googletest)
    add_subdirectory(libs/googletest)
    
    if(TARGET gtest_main)
        # Создание исполняемого файла тестов
        add_executable(DateTimeTests
            DateTime/DateTimeTests/Tests.cpp
            DateTime/DateTime.cpp
        )
        
        # Настройки компиляции для тестов
        target_include_directories(DateTimeTests PRIVATE 
            ${CMAKE_SOURCE_DIR}
            ${gtest_SOURCE_DIR}/include
            ${gmock_SOURCE_DIR}/include
            ${SFML_INCLUDE_DIR}
        )
        
        target_link_libraries(DateTimeTests
            gtest_main
            sfml-system
        )
        
        # Явная регистрация теста
        add_test(
            NAME DateTimeTests
            COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DateTimeTests.exe
            WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        )
        
        message(STATUS "GoogleTest configured successfully")
    else()
        message(WARNING "GoogleTest targets not found")
    endif()
else()
    message(WARNING "GoogleTest directory not found")
endif()

# Копирование DLL (Windows)
if(WIN32)
    # Функция для копирования DLL
    function(copy_sfml_dll target)
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
            COMMAND ${CMAKE_COMMAND} -E copy
                "${SFML_PATH}/bin/sfml-system-2.dll"
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
            COMMENT "Copying SFML DLL for ${target}"
            VERBATIM
        )
    endfunction()

    copy_sfml_dll(DateTimeApp)
    
    if(TARGET DateTimeTests)
        copy_sfml_dll(DateTimeTests)
    endif()
endif()

# Включение цветного вывода для CTest
if(WIN32)
    add_definitions(/DGTEST_COLOR=1)
else()
    add_definitions(-DGTEST_COLOR=1)
endif()

# Передача переменных окружения для цветного вывода
set_property(TEST DateTimeTests PROPERTY ENVIRONMENT "GTEST_COLOR=yes")

# Вывод информации о конфигурации
message(STATUS "Project configuration:")
message(STATUS "  SFML found at: ${SFML_DIR}")
message(STATUS "  Binaries output: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "  Tests executable: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DateTimeTests.exe")