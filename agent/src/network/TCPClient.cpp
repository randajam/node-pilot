#pragma once

#include "TCPClient.hpp"
#include <string>

bool network::TCPClient::connect(const std::string& host, std::uint32_t port) {
    return true;
}

bool network::TCPClient::send(const std::string& data) {
    return true;
}