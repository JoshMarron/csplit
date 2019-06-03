#pragma once

#include <chrono>

#include "timer.h"
#include "logging.h"

#include <spdlog/spdlog.h>

namespace csplit {
namespace core {

template <typename Clock = std::chrono::steady_clock>
class SteadyTimer: public Timer
{
private:
    using SteadyPoint = typename Clock::time_point;
    SteadyPoint d_start;
public:
    SteadyTimer();
    void start() override;
    std::chrono::microseconds elapsed() const override;
    std::chrono::microseconds split() const override;
    std::chrono::microseconds elapsedSince(SteadyPoint point) const;
};

template<typename Clock>
SteadyTimer<Clock>::SteadyTimer()
: d_start()
{}

template<typename Clock>
void SteadyTimer<Clock>::start()
{
    d_start = Clock::now();
    spdlog::info("Timer started. Initial value: {}", d_start.time_since_epoch().count());
}

template<typename Clock>
std::chrono::microseconds SteadyTimer<Clock>::split() const
{
    auto now = Clock::now();
    SPDLOG_DEBUG("Split made. Raw value: {}", now.time_since_epoch().count());
    return std::chrono::duration_cast<std::chrono::microseconds>(now - d_start);
}

template<typename Clock>
std::chrono::microseconds SteadyTimer<Clock>::elapsed() const
{
    auto now = Clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now - d_start);
}

template<typename Clock>
std::chrono::microseconds SteadyTimer<Clock>::elapsedSince(SteadyPoint point) const
{
    auto now = Clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - point);
    return duration;
}

}
}