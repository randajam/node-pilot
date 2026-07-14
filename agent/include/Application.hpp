# pragma once

#include "Agent.hpp"
#include "ConsoleTransport.hpp"
#include <atomic>


class Application {
    private:
    std::atomic<bool> m_running{true};
    transport::ConsoleTransport m_transport;
    Agent m_agent;

    static void handleInterrupt(int signum);

public:
    explicit Application();
    int run(); // возвращает код завершения
};