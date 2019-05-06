#pragma once

#include <chrono>

namespace csplit {
namespace core {

class Timer
{
private:
    std::chrono::steady_clock::time_point d_start;
    
public:
    Timer();
    void start();
};

}
}