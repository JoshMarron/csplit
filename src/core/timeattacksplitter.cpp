#include "timeattacksplitter.h"
#include "timerutils.h"
#include "logging.h"

#include <spdlog/spdlog.h>

namespace csplit {
namespace core {

TimeAttackSplitter::TimeAttackSplitter(std::vector<Split> splits)
: Splitter()
, d_splits(std::move(splits))
, d_currentSplit(0)
{}

SplitState TimeAttackSplitter::split(const std::chrono::microseconds& time)
{
    SPDLOG_DEBUG("Splitting with time: {}", timerutils::microseconds2string(time));
    SplitState state(SplitState::NotReached);

    if (d_currentSplit == 0)
    {
        std::chrono::microseconds segment = time;
        state = currentSplitMut().updateTime(time, segment);
    }
    else
    {
        auto previousSplit = d_splits[d_currentSplit - 1].thisSplitTime();
        if (previousSplit.has_value())
        {
            auto segment = time - previousSplit.value();
            state = currentSplitMut().updateTime(time, segment);
        }
        else
        {
            state = currentSplitMut().updateTime(time);
        }
    }

    ++d_currentSplit;
    return state;
}

void TimeAttackSplitter::skip()
{
    SPDLOG_DEBUG("Split: {} has been skipped! Will remain in NotReached state.", currentSplitMut());
    ++d_currentSplit;
}

bool TimeAttackSplitter::addSplit(const Split& split)
{
    d_splits.push_back(split);
    return true;
}

Split& TimeAttackSplitter::currentSplitMut()
{
    return d_splits[d_currentSplit];
}

std::optional<Split> TimeAttackSplitter::currentSplit() const
{
    if (d_currentSplit < d_splits.size())
    {
        return d_splits[d_currentSplit];
    }
    return std::nullopt;
}

const std::vector<Split>& TimeAttackSplitter::splits() const
{
    return d_splits;
}

} // end namespace core
} // end namespace csplit