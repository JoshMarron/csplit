#include "timeattacksplitter.h"
#include "timerutils.h"
#include "logging.h"

#include <spdlog/spdlog.h>

namespace csplit {
namespace core {

TimeAttackSplitter::TimeAttackSplitter(const std::vector<Split>& splits)
: Splitter()
, d_splits(splits)
, d_currentSplit(0)
{}

SplitState TimeAttackSplitter::split(const std::chrono::microseconds& time)
{
    SPDLOG_DEBUG("Splitting with time: {}", timerutils::microseconds2string(time));
    SplitState state(SplitState::NotReached);

    if (d_currentSplit == 0)
    {
        std::chrono::microseconds segment = time;
        state = currentSplit().updateTime(time, segment);
    }
    else
    {
        auto previousSplit = d_splits[d_currentSplit - 1].thisSplitTime();
        if (previousSplit.has_value())
        {
            auto segment = time - previousSplit.value();
            state = currentSplit().updateTime(time, segment);
        }
        else
        {
            state = currentSplit().updateTime(time);
        }
    }

    ++d_currentSplit;
    return state;
}

Split& TimeAttackSplitter::currentSplit()
{
    return d_splits[d_currentSplit];
}

} // end namespace core
} // end namespace csplit