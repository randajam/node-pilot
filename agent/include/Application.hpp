# pragma once

#include "Agent.hpp"
#include "ConfigLoader.hpp"
#include "ConsoleTransport.hpp"
#include "TCPTransport.hpp"
#include <atomic>


class Application {
private:
    std::atomic<bool> m_running{true};
    config::Config m_config;
    transport::TCPTransport m_transport;
    Agent m_agent;

    static void handleInterrupt(int signum);

public:
    explicit Application(const config::Config& config);
    void start();
    void stop();
    int run(); // возвращает код завершения
};