#pragma once

#include <chrono>
#include <vector>

namespace csplit {
namespace core {

class Timer
{
private:
    using SteadyPoint = std::chrono::steady_clock::time_point;
    SteadyPoint d_start;
public:
    Timer();
    void start();
    std::chrono::microseconds elapsed() const;
    std::chrono::microseconds split();
    std::chrono::microseconds elapsedSince(SteadyPoint point) const;
};

}
}