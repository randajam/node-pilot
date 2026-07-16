#include "ConfigLoader.hpp"
#include "Config.hpp"
#include "LogLevel.hpp"
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>

namespace config {

Config ConfigLoader::load(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("Cannot open config file: " + path);
    }

    nlohmann::json j;
    file >> j; // автоматически парсит в json по полям

    return j.get<config::Config>();
}

inline LogLevel log_level_from_string(const std::string& s) {
    if (s == "WARNING") return LogLevel::Warning;
    if (s == "ERROR") return LogLevel::Error;
    if (s == "TRANSPORT") return LogLevel::Transport;
    if (s == "INFO") return LogLevel::Info;

    return LogLevel::Info;
}

void from_json(const nlohmann::json& j, AgentSettings& s) {
    j.at("interval").get_to(s.interval);
}

void from_json(const nlohmann::json& j, TransportSettings& s) {
    j.at("host").get_to(s.host);
    j.at("port").get_to(s.port);
}

void from_json(const nlohmann::json& j, LoggingSettings& s) {
    std::string log_level_str = j.at("level").get<std::string>();
    s.loglevel = log_level_from_string(log_level_str);
}

void from_json(const nlohmann::json& j, Config& cfg) {
    j.at("agent").get_to(cfg.agent);
    j.at("transport").get_to(cfg.transport);
    j.at("logging").get_to(cfg.logging);
}

}