#pragma once

#include <chrono>
#include <string>

namespace csplit {
namespace core {

struct TimerUtils
{
    static std::string microseconds2string(std::chrono::microseconds input, bool displayMicroseconds=false);
};

} // end namespace core
} // end namespace csplit