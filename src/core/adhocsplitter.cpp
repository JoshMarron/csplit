#include "adhocsplitter.h"
#include "logging.h"
#include "timerutils.h"

#include <spdlog/spdlog.h>

#include <sstream>

namespace csplit {
namespace core {

AdHocSplitter::AdHocSplitter()
: Splitter()
, d_splits()
{}

SplitState AdHocSplitter::split(const std::chrono::microseconds& time)
{
    SPDLOG_DEBUG("Split made in ad-hoc mode at: {}", timerutils::microseconds2string(time));
    auto split = createNewSplit();
    SplitState state = SplitState::NoDataPossible;
    if (d_splits.empty())
    {
        state = split.updateTime(time, time);
    }
    else
    {
        // We can be certain that the split time has a value as an AdHoc split cannot be skipped
        auto segmentTime = time - d_splits.back().thisSplitTime().value();
        state = split.updateTime(time, segmentTime);
    }

    d_splits.push_back(split);
    return state;
}

Split AdHocSplitter::createNewSplit()
{
    auto splitNumber = d_splits.size() + 1;
    SPDLOG_DEBUG("Creating new AdHoc split with number: {}", splitNumber);

    std::stringstream ss;
    ss << "Split " << splitNumber;

    return Split(ss.str());
}

void AdHocSplitter::skip()
{
    // Skipping in an AdHoc scenario is a noop
    SPDLOG_ERROR("Skip attempted in AdHoc mode. This is a No-Op");
    return;
}

// If we add a split, we're no longer AdHoc
bool AdHocSplitter::addSplit(const Split& split)
{
    SPDLOG_WARN("Attempted to add a split to an AdHocSplitter.");
    return false;
}

const std::vector<Split>& AdHocSplitter::splits() const
{
    return d_splits;
}

std::optional<Split> AdHocSplitter::currentSplit() const
{
    if (d_splits.empty())
    {
        return std::nullopt;
    }
    return d_splits.back();
}

} // end namespace core
} // end namespace csplit