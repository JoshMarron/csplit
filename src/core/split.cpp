#include "split.h"

namespace csplit {
namespace core {

Split::Split(std::string name)
: d_name(name)
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
    if (splitTime < d_goldTime)
    {
        return currentRunTime > d_cumulativePbTime ? SplitState::GoldBehind : SplitState::GoldAhead;
    }

    // Otherwise, we check how the run is doing vs. the PB
    // If the current run time is faster than cumulative PB
    if (currentRunTime < d_cumulativePbTime)
    {
        return splitTime > d_pbTime ? SplitState::AheadPbLosingTime : SplitState::AheadPbGainingTime;  
    }
    // If the current run is slower than cumulative PB
    else if (currentRunTime > d_cumulativePbTime)
    {
        return splitTime > d_pbTime ? SplitState::BehindPbLosingTime : SplitState::BehindPbGainingTime;
    }
    
    // Otherwise, we must be equalling the PB
    return SplitState::EqualPb;
}

void Split::changeSplitName(std::string name)
{
    d_name = name;
}

const std::string& Split::name() const
{
    return d_name;
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

} // end namespace core
} // end namespace csplit