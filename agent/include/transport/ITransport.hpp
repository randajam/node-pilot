#pragma once

#include <string>

namespace transport {

class ITransport {
public:
    virtual ~ITransport() = default;
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual void send(const std::string& msg) = 0;
};

}