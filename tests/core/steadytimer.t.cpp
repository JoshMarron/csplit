#include <gtest/gtest.h>
#include <chrono>

#include <core/steadytimer.h>
#include "fakeclock.h"

using namespace csplit;
using microseconds = std::chrono::microseconds;

TEST(TestSteadyTimer, TestElapsed)
{
    core::SteadyTimer<FakeClock> timer{};
    auto epoch = FakeClock::now();
    microseconds elapsedDelay(20000);

    timer.start();
    FakeClock::moveForwards(elapsedDelay);
    auto elapsed = timer.elapsed();

    EXPECT_EQ(elapsed, elapsedDelay);
}