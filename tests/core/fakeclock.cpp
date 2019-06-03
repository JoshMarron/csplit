#include "fakeclock.h"

namespace {
    FakeClock::time_point nowVal;
}

FakeClock::time_point FakeClock::now() noexcept
{
    return nowVal;
}

void FakeClock::moveForwards(FakeClock::duration d) noexcept
{
    nowVal += d;
}

void FakeClock::reset() noexcept
{
    nowVal -= (nowVal - FakeClock::time_point());
}