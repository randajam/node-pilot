#pragma once

#include "ITransport.hpp"
namespace transport
{
    
class TСPTransport : public ITransport {
    void send(const std::string& msg) override;
};

} // namespace transport
