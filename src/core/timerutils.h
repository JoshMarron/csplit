#pragma once

#include <chrono>
#include <string>

namespace csplit {
namespace core {
namespace timerutils {

std::string microseconds2string(std::chrono::microseconds input, bool displayMicroseconds=false);


} // end namespace timerutils
} // end namespace core
} // end namespace csplit