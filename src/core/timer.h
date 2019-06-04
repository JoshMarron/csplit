#pragma once

#include <chrono>
#include <vector>
#include <iostream>

namespace csplit {
namespace core {

// IMPORTANT: Behaviour of elapsed() and split() is UNDEFINED until start() is called.
class Timer
{
public:
    virtual ~Timer() {}
    virtual void start() = 0;
    virtual std::chrono::microseconds elapsed() const = 0;
    virtual std::chrono::microseconds split() const = 0;
    virtual void print(std::ostream& stream) const = 0;
    // The elapsedSince method has been removed for now as I'm not certain it's very useful
    // We can consider re-adding it in future
};

inline
std::ostream& operator<<(std::ostream& stream, const Timer& timer)
{
    timer.print(stream);
    return stream;
}

}
}