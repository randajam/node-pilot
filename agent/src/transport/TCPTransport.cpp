#include "TCPTransport.hpp"
#include "LogLevel.hpp"
#include "Logger.hpp"

transport::TCPTransport::TCPTransport(const std::string& host, std::uint16_t port):
m_host(host), m_port(port)
{}

void transport::TCPTransport::connect() {
    logging::log("TCP client connecting to " + std::string(m_host) + ":" + std::to_string(m_port), LogLevel::Info, LogCategory::Transport);

    m_client.connect(m_host, m_port);
    
    logging::log("TCP client connected", LogLevel::Info, LogCategory::Transport);
}

void transport::TCPTransport::disconnect() {
    m_client.disconnect();
    logging::log("TCP client disconnected", LogLevel::Info, LogCategory::Transport);
}

void transport::TCPTransport::send(const std::string& msg) {
    m_client.send(msg);
}