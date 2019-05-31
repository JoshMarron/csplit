#include "speedrun.h"
#include "timerutils.h"
#include "logging.h"

#include "timeattacksplitter.h"

#include <spdlog/spdlog.h>

namespace csplit {
namespace core {

Speedrun::Speedrun()
: d_timer()
, d_started(false)
, d_splitter()
{}

Speedrun::Speedrun(std::vector<Split> splits)
: d_timer()
, d_started(false)
, d_splitter(std::make_unique<TimeAttackSplitter>(splits))
{}

void Speedrun::start()
{
    d_timer.start();
    spdlog::info("Run started!");
    if (d_splitter->splits().empty())
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
    auto splitTime = d_timer.split();
    return d_splitter->split(splitTime);
}

void Speedrun::addSplit(const Split& split)
{
    if(!d_splitter->addSplit(split))
    {
        // Then we must be using an adhoc splitter. We can't do that anymore, so change
        auto splits = std::vector<Split>();
        splits.push_back(split);
        d_splitter = std::make_unique<TimeAttackSplitter>(splits);
    }
}

} // end namespace core
} // end namespace csplit