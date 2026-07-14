#include "Application.hpp"
#include "Agent.hpp"
#include "Logger.hpp"
#include "ConsoleTransport.hpp"
#include <csignal>

static Application* g_app_instance = nullptr;

void Application::handleInterrupt(int /*signum*/) {
    if (g_app_instance) {
        g_app_instance->m_running.store(false);
    }
}

Application::Application(): m_transport(), m_agent(m_running, m_transport){
}

int Application::run() {
    g_app_instance = this;

    std::signal(SIGINT, Application::handleInterrupt);
    logging::log("NodePilot Agent v0.1", LogLevel::Info);

    try {
        m_agent.start();
        m_agent.loop();
        m_agent.stop();
    } catch (const std::exception& err) {
        // std::cerr << "[ERROR] " << err.what() << std::endl;
        logging::log(err.what(), LogLevel::Error);
        return 1;
    }
    return 0;
}
