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
    m_agent(m_running, m_transport)
{
}

int Application::run() {
    g_app_instance = this;
    
    std::signal(SIGINT, Application::handleInterrupt);
    logging::log("NodePilot Agent v0.1", LogLevel::Info);

    try {
        start();
        m_agent.loop();
        stop();
    } catch (const std::exception& err) {
        logging::log(err.what(), LogLevel::Error);
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
}