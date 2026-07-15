#pragma once

#include "ITransport.hpp"
#include "TCPClient.hpp"

namespace transport
{
    
class TCPTransport: public ITransport {
public:
    TCPTransport(const std::string& host, std::uint16_t port);
    void connect() override;
    void disconnect() override;
    void send(const std::string& msg) override;
private:
    network::TCPClient m_client{};
    const std::string m_host;
    std::uint16_t m_port;
};

} // namespace transport
