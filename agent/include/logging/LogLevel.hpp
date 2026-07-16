#pragma once

enum class LogLevel {
    Info = 0,
    Warning = 1,
    Error = 2
};

enum class LogCategory {
    General,
    Transport,
    Metrics,
    Config,
    Protocol
};

namespace ansi { // Цвета вывода
    inline const char* RESET   = "\033[0m";
    inline const char* BOLD    = "\033[1m";
    
    // Текст
    inline const char* BLACK   = "\033[30m";
    inline const char* RED     = "\033[31m";
    inline const char* GREEN   = "\033[32m";
    inline const char* YELLOW  = "\033[33m";
    inline const char* BLUE    = "\033[34m";
    inline const char* MAGENTA = "\033[35m";
    inline const char* CYAN    = "\033[36m";
    inline const char* WHITE   = "\033[37m";
}