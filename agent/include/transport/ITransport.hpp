#pragma once

#include <string>

namespace transport {

class ITransport {
public:
    virtual ~ITransport() = default;
    virtual void send(const std::string& msg) = 0;
};

}