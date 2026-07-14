#pragma once

#include "MetricsCollector.hpp"
#include <cstdint>
#include <string>


namespace protocol {

struct MetricsMessage {
    std::string type;
    SystemMetrics metrics;
    uint64_t timestamp;
};  

};