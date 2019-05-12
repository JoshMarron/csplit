#include <chrono>
#include <thread>

#include <spdlog/spdlog.h>

#include "core/timer.h"
#include "core/timerutils.h"
#include "core/speedrun.h"

int main()
{
    spdlog::info("Hello world from csplit.");
    spdlog::info("This is a test line.");
    spdlog::set_level(spdlog::level::debug);

    auto t = csplit::core::Timer();
    t.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1230));
    auto splitTime = t.split();
    
    spdlog::info("Timer split at {}", splitTime.count());
    spdlog::info("Timer split at {}", csplit::core::timerutils::microseconds2string(splitTime));

    for (int i = 0; i < 100; ++i)
    {
        auto elapsedTime = t.elapsed();
        spdlog::info("{}", csplit::core::timerutils::microseconds2string(elapsedTime));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    auto run = csplit::core::Speedrun();
    run.start();

    return 0;
}