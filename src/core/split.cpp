#include "split.h"

namespace csplit {
namespace core {

Split::Split(std::string name)
: d_name(name)
, d_state(SplitState::NotReached)
, d_goldTime()
, d_pbSegmentTime()
, d_segmentTime()
, d_splitTime()
, d_pbSplitTime()
{}

Split::Split(std::string name, 
             std::chrono::microseconds goldTime, 
             std::chrono::microseconds pbTime,
             std::chrono::microseconds cumulativePbTime)
: d_name(name)
, d_state(SplitState::NotReached)
, d_goldTime(goldTime)
, d_pbSegmentTime(pbTime)
, d_segmentTime()
, d_splitTime()
, d_pbSplitTime(cumulativePbTime)
{}

SplitState Split::updateTime(std::chrono::microseconds splitTime)
{
    d_splitTime = splitTime;

    if (splitTime < d_pbSplitTime)
    {
        d_state = SplitState::AheadPbNoData;
    }
    else if (splitTime > d_pbSplitTime)
    {
        d_state = SplitState::BehindPbNoData;
    }
    else
    {
        d_state = SplitState::EqualPb;
    }
    
    return d_state;
}

SplitState Split::updateTime(std::chrono::microseconds splitTime, 
                             std::chrono::microseconds segmentTime)
{
    d_splitTime = splitTime;
    d_segmentTime = segmentTime;

    // Is this a gold split?
    // Alternatively, is this an empty split? An empty split will always gold.
    if (segmentTime < d_goldTime.value_or(std::chrono::microseconds::max()))
    {
        d_state = splitTime > d_pbSplitTime.value_or(std::chrono::microseconds::max()) ? 
                                SplitState::GoldBehind : 
                                SplitState::GoldAhead;
    }

    // Otherwise, we check how fast the split is vs the PB
    else if (segmentTime < d_pbSegmentTime)
    {
        d_state = splitTime < d_pbSplitTime ? 
                                SplitState::AheadPbGainingTime : 
                                SplitState::BehindPbGainingTime;  
    }
    else if (segmentTime > d_pbSegmentTime)
    {
        d_state = splitTime < d_pbSplitTime ? 
                                SplitState::AheadPbLosingTime : 
                                SplitState::BehindPbLosingTime;
    }
    else
    {
        d_state = SplitState::EqualPb;
    }
    
    return d_state;
}

SplitState Split::resetSplit()
{
    d_state = SplitState::NotReached;
    d_segmentTime.reset();
    d_splitTime.reset();

    return d_state;
}

void Split::changeSplitName(std::string name)
{
    d_name = name;
}

const std::string& Split::name() const
{
    return d_name;
}

SplitState Split::state() const
{
    return d_state;
}

const Split::PossibleTime& Split::goldTime() const
{
    return d_goldTime;
}

const Split::PossibleTime& Split::pbSegmentTime() const
{
    return d_pbSegmentTime;
}

const Split::PossibleTime& Split::thisSegmentTime() const
{
    return d_segmentTime;
}

const Split::PossibleTime& Split::thisSplitTime() const
{
    return d_splitTime;
}

} // end namespace core
} // end namespace csplit