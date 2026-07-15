# pragma once

#include "Agent.hpp"
#include "ConsoleTransport.hpp"
#include "TCPTransport.hpp"
#include <atomic>


class Application {
private:
    std::atomic<bool> m_running{true};
    transport::TCPTransport m_transport;
    Agent m_agent;

    static void handleInterrupt(int signum);

public:
    explicit Application();
    void start();
    void stop();
    int run(); // возвращает код завершения
};