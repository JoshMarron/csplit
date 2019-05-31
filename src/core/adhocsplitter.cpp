#include "adhocsplitter.h"

#include <sstream>

namespace csplit {
namespace core {

AdHocSplitter::AdHocSplitter()
: Splitter()
, d_splits()
{}

SplitState AdHocSplitter::split(const std::chrono::microseconds& time)
{
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
    std::stringstream ss;
    ss << "Split " << splitNumber;
    
    return Split(ss.str());
}

// If we add a split, we're no longer AdHoc
bool AdHocSplitter::addSplit(const Split& split)
{
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