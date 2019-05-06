#include "timer.h"

#include <spdlog/spdlog.h>
#include <iomanip>

namespace csplit {
namespace core {

Timer::Timer()
: d_start()
{}

void Timer::start()
{
    d_start = std::chrono::steady_clock::now();
    spdlog::info("Timer started. Initial value: {}", d_start.time_since_epoch().count());
}

} // end namespace core
} // end namespace csplit