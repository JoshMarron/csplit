#pragma once

#include <chrono>

#include "timer.h"

namespace csplit {
namespace core {

class SteadyTimer: public Timer
{
private:
    SteadyPoint d_start;
public:
    SteadyTimer();
    void start() override;
    std::chrono::microseconds elapsed() const override;
    std::chrono::microseconds split() const override;
    std::chrono::microseconds elapsedSince(SteadyPoint point) const override;
};

}
}