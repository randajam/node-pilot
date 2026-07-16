#include "Application.hpp"
#include "Agent.hpp"
#include "Logger.hpp"
#include "Config.hpp"
#include <csignal>

static Application* g_app_instance = nullptr;

void Application::handleInterrupt(int /*signum*/) {
    if (g_app_instance) {
        g_app_instance->m_running.store(false);
    }
}

Application::Application(const config::Config& config):
    m_config(config),
    m_transport(config.transport.host, config.transport.port),
    m_agent(m_running, m_transport, config.agent.interval)
{
}

int Application::run() {
    g_app_instance = this;

    logging::setLevel(m_config.logging.loglevel);
    logging::log("Configuration loaded successfully", LogLevel::Info, LogCategory::Config);
    
    std::signal(SIGINT, Application::handleInterrupt);
    logging::log("NodePilot Agent v0.1", LogLevel::Info, LogCategory::General);

    try {
        start();
        m_agent.loop();
        stop();
    } catch (const std::exception& err) {
        logging::log(std::string("Fatal error: ") + err.what(), LogLevel::Error, LogCategory::General);
        return 1;
    }
    return 0;
}

void Application::start() {
    m_transport.connect();
    m_agent.start();
}

void Application::stop() {
    m_agent.stop();
    m_transport.disconnect();
}