#include "Application.hpp"
#include "Agent.hpp"
#include "Logger.hpp"
#include "ConsoleTransport.hpp"
#include "TCPClient.hpp"
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
    
    network::TCPClient client;
    client.connect("192.168.0.104", 9000);
    
    std::signal(SIGINT, Application::handleInterrupt);
    logging::log("NodePilot Agent v0.1", LogLevel::Info);

    try {
        m_agent.start();
        m_agent.loop();
        m_agent.stop();
    } catch (const std::exception& err) {
        logging::log(err.what(), LogLevel::Error);
        return 1;
    }
    client.disconnect();
    return 0;
}
