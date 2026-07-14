#include "JsonSerializer.hpp"
#include <string>
#include <nlohmann/json.hpp>

std::string protocol::serialize(const MetricsMessage &msg) {
    return nlohmann::json{
        {"type", msg.type},
        {"timestamp", msg.timestamp},
        {"metrics", {
            {"uptime", msg.metrics.uptime},
            {"cpuUsage", msg.metrics.cpuUsage},
            {"ramTotal", msg.metrics.ramTotal},
            {"ramUsed", msg.metrics.ramUsed},
            {"diskUsage", msg.metrics.diskUsage}
        }}
    }.dump();
}