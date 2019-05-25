#include "speedrun.h"
#include "timerutils.h"

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
    SPDLOG_DEBUG("Splitting with time: {}", timerutils::microseconds2string(split));
    SplitState state(SplitState::NotReached);
    
    if (d_currentSplit == 0)
    {
        std::chrono::microseconds segment = split;
        state = currentSplit().updateTime(split, segment);
    }
    else
    {
        auto previousSplit = d_splits[d_currentSplit - 1].thisSplitTime();
        if (previousSplit.has_value())
        {
            auto segment = split - previousSplit.value();
            state = currentSplit().updateTime(split, segment);
        }
        else
        {
            state = currentSplit().updateTime(split);
        }
    }
    
    ++d_currentSplit;
    return state;
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