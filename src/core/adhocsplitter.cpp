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
    if (d_splits.empty())
    {
        split.updateTime(time, time);
    }
    else
    {
        // We can be certain that the split time has a value as an AdHoc split cannot be skipped
        auto segmentTime = time - d_splits.back().thisSplitTime().value();
        split.updateTime(time, segmentTime);
    }
    
    d_splits.push_back(split);
}

Split AdHocSplitter::createNewSplit()
{
    auto splitNumber = d_splits.size() + 1;
    std::stringstream ss;
    ss << "Split " << splitNumber;
    
    return Split(ss.str());
}

} // end namespace core
} // end namespace csplit