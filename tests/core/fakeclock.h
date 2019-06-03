#pragma once

#include <chrono>
#include <ratio>
#include <cstdint>

class FakeClock
{
public:
    typedef uint64_t rep;
    typedef std::nano period;
    typedef std::chrono::duration<rep, period> duration;
    typedef std::chrono::time_point<FakeClock> time_point;

    static time_point now() noexcept;
    static const bool is_steady = false;

    static void moveForwards(duration d) noexcept;
    static void reset() noexcept;
};