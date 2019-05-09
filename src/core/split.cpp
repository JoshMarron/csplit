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