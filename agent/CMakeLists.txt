cmake_minimum_required(VERSION 3.16)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(nodepilot-agent LANGUAGES CXX)

# НАЧАЛО блока с зависимостями
include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2 # Актуальная стабильная версия
)

FetchContent_MakeAvailable(nlohmann_json)
# КОНЕЦ

set(SOURCES
    src/main.cpp
    src/Application.cpp
    src/Agent.cpp
    src/MetricsCollector.cpp
    src/protocol/JsonSerializer.cpp
    src/transport/ConsoleTransport.cpp
    src/transport/TSPTransport.cpp
    src/logging/Logger.cpp
    src/network/TCPClient.cpp
    )

# Создаем исполняемый файл из исходников
add_executable(nodepilot-agent ${SOURCES})

# Указываем стандарт языка
target_compile_features(nodepilot-agent PRIVATE cxx_std_20)

# Добавляем папку include, чтобы можно было писать #include "Agent.hpp"
target_include_directories(nodepilot-agent
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/protocol
    ${PROJECT_SOURCE_DIR}/include/transport
    ${PROJECT_SOURCE_DIR}/include/logging
    ${PROJECT_SOURCE_DIR}/include/network
)

# Привязываем библиотеку к цели
target_link_libraries(nodepilot-agent PRIVATE nlohmann_json::nlohmann_json)