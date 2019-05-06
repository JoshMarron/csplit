#include <chrono>
#include <thread>

#include <spdlog/spdlog.h>

#include "core/timer.h"
#include "core/timerutils.h"

int main()
{
    spdlog::info("Hello world from csplit.");
    spdlog::info("This is a test line.");

    auto t = csplit::core::Timer();
    t.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1230));
    auto splitTime = t.split();
    spdlog::info("Timer split at {}", splitTime.count());
    spdlog::info("Timer split at {}", csplit::core::TimerUtils::microseconds2string(splitTime));

    return 0;
}