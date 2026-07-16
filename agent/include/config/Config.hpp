#pragma once

#include "LogLevel.hpp"
#include <string>
#include <cstdint>
namespace config {

struct AgentSettings {
    int interval;
};

struct TransportSettings {
    std::string host;
    uint16_t port;
    
};

struct LoggingSettings {
    LogLevel loglevel;
};

struct Config {
    AgentSettings agent;
    TransportSettings transport;
    LoggingSettings logging;
};

}