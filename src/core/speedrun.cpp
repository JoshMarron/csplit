#include "speedrun.h"

#include <spdlog/spdlog.h>

namespace csplit {
namespace core {

Speedrun::Speedrun()
: d_splits()
, d_currentSplit(0)
, d_timer()
, d_started(false)
{}

Speedrun::Speedrun(std::vector<Split> splits)
: d_splits(splits)
, d_currentSplit(0)
, d_timer()
, d_started(false)
{}

void Speedrun::start()
{
    d_timer.start();
    spdlog::info("Run started!");
    if (d_splits.empty())
    {
        spdlog::warn("Run started in simple timer mode. No splits can be made.");
    }
    d_started = true;
}

SplitState Speedrun::split()
{
    auto split = d_timer.split();
    std::chrono::microseconds segment;
    if (d_currentSplit == 0)
    {
        segment = split;
    }
    else
    {
        auto previousSplit = d_splits[d_currentSplit].thisSplitTime();
    }
}

} // end namespace core
} // end namespace csplit