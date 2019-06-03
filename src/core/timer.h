#pragma once

#include <chrono>
#include <vector>

namespace csplit {
namespace core {

class Timer
{
public:
    virtual ~Timer() {}
    virtual void start() = 0;
    virtual std::chrono::microseconds elapsed() const = 0;
    virtual std::chrono::microseconds split() const = 0;
};

}
}