#include "TCPClient.hpp"
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <cerrno>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

network::TCPClient::TCPClient() {
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket == -1) {
        throw std::runtime_error(std::string("Socket creation failed: ") + std::strerror(errno));
    }
}

network::TCPClient::~TCPClient() {
    disconnect();
}

void network::TCPClient::disconnect() {
    if (isConnected()) {
        ::close(m_socket);
        m_socket = -1;
    }
}

bool network::TCPClient::isConnected() const {
    return m_socket != -1;
}

void network::TCPClient::connect(const std::string& host, std::uint16_t port) {
    struct sockaddr_in server_addr{};

    std::memset(&server_addr, 0, sizeof(server_addr)); // инициализируем нулями

    server_addr.sin_family = AF_INET; // Семейство протоколов
    server_addr.sin_port = htons(port); // преобразуем порт в сетевой порядок байтов
    int pton_result = inet_pton(AF_INET, host.c_str(), &server_addr.sin_addr); // текст в бинарный адрес

    if (pton_result != 1) {
        if (pton_result == 0) {
            throw std::invalid_argument("Invalid IP address format.");
        } else {
            throw std::runtime_error(std::string("IP conversion failed: ") + std::strerror(errno));
        }
    }

    if (::connect(m_socket, reinterpret_cast<const struct sockaddr*>(&server_addr), sizeof(server_addr)) < 0) {
        throw std::runtime_error(std::string("Connection to ") + host + ":" + std::to_string(port) + " failed: " + std::strerror(errno));
    }
}

void network::TCPClient::send(const std::string& data) {
 
}