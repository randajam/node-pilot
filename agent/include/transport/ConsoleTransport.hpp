#pragma once

#include "ITransport.hpp"
#include <string>

namespace transport {

class ConsoleTransport: public ITransport {
    void connect() override;
    void disconnect() override;
    void send(const std::string& msg) override;
};

}