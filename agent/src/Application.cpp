#include "Application.hpp"
#include "Agent.hpp"
#include "Logger.hpp"
#include <csignal>

static Application* g_app_instance = nullptr;

void Application::handleInterrupt(int /*signum*/) {
    if (g_app_instance) {
        g_app_instance->m_running.store(false);
    }
}

Application::Application(): m_transport("192.168.0.104", 8080), m_agent(m_running, m_transport){
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