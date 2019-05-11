#include "split.h"

namespace csplit {
namespace core {

Split::Split(std::string name)
: d_name(name)
, d_state(SplitState::NotReached)
, d_goldTime()
, d_pbTime()
, d_currentTime()
, d_cumulativeTime()
, d_cumulativePbTime()
{}

Split::Split(std::string name, 
             std::chrono::microseconds goldTime, 
             std::chrono::microseconds pbTime,
             std::chrono::microseconds cumulativePbTime)
: d_name(name)
, d_state(SplitState::NotReached)
, d_goldTime(goldTime)
, d_pbTime(pbTime)
, d_currentTime()
, d_cumulativeTime()
, d_cumulativePbTime(cumulativePbTime)
{}

SplitState Split::updateTime(std::chrono::microseconds splitTime, 
                             std::chrono::microseconds currentRunTime)
{
    d_cumulativeTime = currentRunTime;
    d_currentTime = splitTime;

    // Is this a gold split?
    // Alternatively, is this an empty split? An empty split will always gold.
    if (splitTime < d_goldTime.value_or(std::chrono::microseconds::max()))
    {
        d_state = currentRunTime > d_cumulativePbTime.value_or(std::chrono::microseconds::max()) ? 
                                SplitState::GoldBehind : 
                                SplitState::GoldAhead;
    }

    // Otherwise, we check how fast the split is vs the PB
    else if (splitTime < d_pbTime)
    {
        d_state = currentRunTime < d_cumulativePbTime ? 
                                SplitState::AheadPbGainingTime : 
                                SplitState::BehindPbGainingTime;  
    }
    else if (splitTime > d_pbTime)
    {
        d_state = currentRunTime < d_cumulativePbTime ? 
                                SplitState::AheadPbLosingTime : 
                                SplitState::BehindPbLosingTime;
    }
    else
    {
        d_state = SplitState::EqualPb;
    }
    
    return d_state;
}

SplitState Split::updateEmptySplit(std::chrono::microseconds time,
                                   std::chrono::microseconds currentRunTime)
{
    return SplitState::GoldAhead;
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

const Split::PossibleTime& Split::pbTime() const
{
    return d_pbTime;
}

const Split::PossibleTime& Split::thisRunTime() const
{
    return d_currentTime;
}

const Split::PossibleTime& Split::thisRunCumulativeTime() const
{
    return d_cumulativeTime;
}

} // end namespace core
} // end namespace csplit