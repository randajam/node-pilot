#pragma once

#include <string>
#include "LogLevel.hpp"

namespace logging {

void log(const std::string& msg, LogLevel level, LogCategory category); 

void setLevel(const LogLevel level);


}