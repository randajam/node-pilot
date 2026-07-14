#pragma once

#include <cstdint>
#include <string>

namespace network {

class TCPClient {
public:
    TCPClient();
    ~TCPClient();

    bool connect(const std::string& host, std::uint32_t port);
    bool send(const std::string& data);
    void disconnect();
    bool isConnected() const;

private:
    int m_socket{-1};
};

}