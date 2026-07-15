#include "TCPTransport.hpp"
#include "LogLevel.hpp"
#include "Logger.hpp"

transport::TCPTransport::TCPTransport(const std::string& host, std::uint16_t port):
m_host(host), m_port(port)
{}

void transport::TCPTransport::connect() {
    logging::log("TCP client connecting...", LogLevel::Transport);

    logging::log("Host: " + m_host, LogLevel::Transport);
    logging::log("Port: " + std::to_string(m_port), LogLevel::Transport);

    m_client.connect(m_host, m_port);
    logging::log("TCP client connected", LogLevel::Transport);
}

void transport::TCPTransport::disconnect() {
    m_client.disconnect();
}

void transport::TCPTransport::send(const std::string& msg) {
    logging::log("Sending " + std::to_string(msg.size()) + " bytes",
                 LogLevel::Transport);

    m_client.send(msg);

    logging::log("Send finished",
                 LogLevel::Transport);
}