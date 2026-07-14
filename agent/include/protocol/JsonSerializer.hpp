#pragma once

#include "MetricsMessage.hpp"
#include <string>

namespace protocol {

std::string serialize(const MetricsMessage& msg);

}