#include "ConsoleTransport.hpp"
#include "Logger.hpp"
#include <string>

void transport::ConsoleTransport::send(const std::string& msg) {
    logging::log(msg, LogLevel::Info, LogCategory::Transport);
}