#pragma once

#include <cstdint>
#include <string>

namespace network {

class TCPClient {
public:
    TCPClient();
    ~TCPClient();

    void connect(const std::string& host, std::uint16_t port);
    void send(const std::string& data);
    void disconnect();
    bool isConnected() const;

private:
    int m_socket{-1};
};

}