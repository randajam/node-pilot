#include "Logger.hpp"
#include "LogLevel.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <mutex> // Обязательно для защиты cout

namespace logging {

static const char* to_string(LogLevel level) {
    switch (level) {
        case LogLevel::Info: return "INFO";
        case LogLevel::Warning: return "WARNING";
        case LogLevel::Error: return "ERROR";
        case LogLevel::Transport: return "TRANSPORT"; // Для сетевых событий
        default: return "UNKNOWN";
    }
}

// Глобальный мьютекс для синхронизации вывода
static std::mutex log_mutex; 

void log(const std::string& msg, LogLevel level) {
    // RAII-блокировка: замок снимется сам при выходе из области видимости
    std::lock_guard<std::mutex> guard(log_mutex);

    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    
    // Используем printf-подобный синтаксис или оператор << последовательно
    std::cout << "[" << std::put_time(std::localtime(&t), "%F %T") << "] "
              << "[" << to_string(level) << "] "
              << msg << std::endl;
}

}