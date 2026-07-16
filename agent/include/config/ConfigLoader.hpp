#pragma once

#include "Config.hpp"
#include <nlohmann/json.hpp>
namespace config {

class ConfigLoader {
public:
    static Config load(const std::string& path);
};

void from_json(const nlohmann::json& j, AgentSettings& s);
void from_json(const nlohmann::json& j, TransportSettings& s);
void from_json(const nlohmann::json& j, LoggingSettings& s);
void from_json(const nlohmann::json& j, Config& cfg);

}