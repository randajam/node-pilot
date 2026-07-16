#include "Logger.hpp"
#include "LogLevel.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <mutex> // Обязательно для защиты cout
#include <atomic>
#include <unistd.h>

namespace logging {

static const char* to_string(LogLevel level) {
    switch (level) {
        case LogLevel::Info: return "INFO";
        case LogLevel::Warning: return "WARNING";
        case LogLevel::Error: return "ERROR";
        default: return "UNKNOWN";
    }
}

static const char* to_string(LogCategory category) {
    switch (category) {
        case LogCategory::General: return "GENERAL";
        case LogCategory::Transport: return "TRANSPORT";
        case LogCategory::Metrics: return "METRICS";
        case LogCategory::Config: return "CONFIG";
        case LogCategory::Protocol: return "PROTOCOL";
        default: return "UNKNOWN";
    }
}

static const char* get_color(LogLevel level) {
    switch (level) {
        case LogLevel::Info: return ansi::GREEN;
        case LogLevel::Warning: return ansi::YELLOW;
        case LogLevel::Error: return ansi::RED;
        default: return ansi::WHITE;
    }
} 


bool should_use_colors() {
    return isatty(fileno(stdout)); // Возвращает true, если stdout - это терминал
}

// Глобальный мьютекс для синхронизации вывода
static std::mutex log_mutex; 

// Минимальный уровень логирования
static std::atomic<LogLevel> g_current_level{LogLevel::Info};

void log(const std::string& msg, LogLevel level, LogCategory category) {
    if (static_cast<int>(level) < static_cast<int>(g_current_level.load())) {
        return;
    }
    // RAII-блокировка: замок снимется сам при выходе из области видимости
    std::lock_guard<std::mutex> guard(log_mutex);

    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);

    const char* color_code = should_use_colors() ? get_color(level) : "";
    const char* reset_code = should_use_colors() ? ansi::RESET : "";
    
    // Используем printf-подобный синтаксис или оператор << последовательно
    std::cout << "[" << std::put_time(std::localtime(&t), "%F %T") << "] "
              << "[" << color_code << to_string(level) << reset_code << "] "
              << "[" << to_string(category) << "] "
              << color_code << msg << reset_code << std::endl;
}

void setLevel(LogLevel level) {
    g_current_level.store(level);
}

} // namespace logging