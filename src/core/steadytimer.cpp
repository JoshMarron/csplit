#include "steadytimer.h"
#include "logging.h"

#include <spdlog/spdlog.h>

namespace csplit {
namespace core {

SteadyTimer::SteadyTimer()
: d_start()
{}

void SteadyTimer::start()
{
    d_start = std::chrono::steady_clock::now();
    spdlog::info("Timer started. Initial value: {}", d_start.time_since_epoch().count());
}

std::chrono::microseconds SteadyTimer::split() const
{
    auto now = std::chrono::steady_clock::now();
    SPDLOG_DEBUG("Split made. Raw value: {}", now.time_since_epoch().count());
    return std::chrono::duration_cast<std::chrono::microseconds>(now - d_start);
}

std::chrono::microseconds SteadyTimer::elapsed() const
{
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now - d_start);

}

std::chrono::microseconds SteadyTimer::elapsedSince(SteadyPoint point) const
{
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - point);
    return duration;
}

} // end namespace core
} // end namespace csplit