#include "speedrun.h"
#include "timerutils.h"
#include "logging.h"

#include "timeattacksplitter.h"

#include <spdlog/spdlog.h>

namespace csplit {
namespace core {

Speedrun::Speedrun()
: d_splits()
, d_currentSplit(0)
, d_timer()
, d_started(false)
, d_splitter()
{}

Speedrun::Speedrun(std::vector<Split> splits)
: d_splits(splits)
, d_currentSplit(0)
, d_timer()
, d_started(false)
, d_splitter(std::make_unique<TimeAttackSplitter>(splits))
{}

void Speedrun::start()
{
    d_timer.start();
    spdlog::info("Run started!");
    if (d_splits.empty())
    {
        SPDLOG_WARN("Run started without any splits loaded.");
    }
    d_started = true;
}

SplitState Speedrun::split()
{
    if (!d_started)
    {
        SPDLOG_WARN("A split was attempted before the run began.");
        return SplitState::NoDataPossible;
    }
    auto split = d_timer.split();
    return d_splitter->split(split);
}

Split& Speedrun::currentSplit()
{
    return d_splits[d_currentSplit];
}

const Split& Speedrun::currentSplit() const
{
    return d_splits[d_currentSplit];
}

} // end namespace core
} // end namespace csplit