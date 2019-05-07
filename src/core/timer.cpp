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

std::chrono::microseconds Timer::split()
{
    auto now = std::chrono::steady_clock::now();
    d_splits.push_back(now);
    spdlog::debug("Split made. Raw value: {}", now.time_since_epoch().count()); 
    return std::chrono::duration_cast<std::chrono::microseconds>(now - d_start);
}

std::chrono::microseconds Timer::elapsed() const
{
    auto now = std::chrono::steady_clock::now();
    spdlog::trace("Time elapsed since start: {}", now.time_since_epoch().count());
    return std::chrono::duration_cast<std::chrono::microseconds>(now - d_start);

}

std::chrono::microseconds Timer::elapsedSince(SteadyPoint point) const
{
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - point);
    spdlog::trace("Time elapsed since {}: {}", point.time_since_epoch().count(), duration.count());
    return duration;
}

} // end namespace core
} // end namespace csplit