#include <chrono>
#include <thread>
#include <iostream>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#define SPDLOG_DEBUG_ON
#define SPDLOG_TRACE_ON

#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "core/timer.h"
#include "core/steadytimer.h"
#include "core/timerutils.h"
#include "core/speedrun.h"

void setupLogging(spdlog::level::level_enum consoleLevel, spdlog::level::level_enum fileLevel)
{
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(consoleLevel);
    console_sink->set_pattern("[%T.%e]%^[%l]%$ %v");

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/csplit.log", true);
    file_sink->set_level(fileLevel);
    file_sink->set_pattern("[%T.%e.%f]%^[%l]%$-%@- %v");

    auto logger = std::shared_ptr<spdlog::logger>(new spdlog::logger("logger", {console_sink, file_sink}));
    spdlog::set_default_logger(logger);
}

int main()
{
    setupLogging(spdlog::level::info, spdlog::level::debug);

    spdlog::info("I AM CSPLIT. I AM STARTING.");

    auto t = csplit::core::SteadyTimer<>();
    t.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1230));
    auto splitTime = t.split();

    spdlog::info("Timer split at {}", splitTime.count());
    spdlog::info("Timer split at {}", csplit::core::timerutils::microseconds2string(splitTime));

    for (int i = 0; i < 100; ++i)
    {
        auto elapsedTime = t.elapsed();
        spdlog::debug("{}", csplit::core::timerutils::microseconds2string(elapsedTime));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    auto run = csplit::core::Speedrun("testRun", "any%");
    run.start();

    auto split = csplit::core::Split("testSplit");
    split.updateTime(std::chrono::microseconds(15607434));
    SPDLOG_INFO("Split is: {}", split);

    return 0;
}