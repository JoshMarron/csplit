#include <spdlog/spdlog.h>

#include "core/timer.h"

int main()
{
    spdlog::info("Hello world from csplit.");
    spdlog::info("This is a test line.");

    auto t = csplit::core::Timer();
    t.start();

    return 0;
}