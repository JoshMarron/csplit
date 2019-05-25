#include "split.h"
#include "logging.h"
#include "timerutils.h"

#include <spdlog/spdlog.h>

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
             std::chrono::microseconds pbSegmentTime,
             std::chrono::microseconds pbSplitTime)
: d_name(name)
, d_state(SplitState::NotReached)
, d_goldTime(goldTime)
, d_pbSegmentTime(pbSegmentTime)
, d_segmentTime()
, d_splitTime()
, d_pbSplitTime(pbSplitTime)
{}

SplitState Split::updateTime(std::chrono::microseconds splitTime)
{
    d_splitTime = splitTime;

    if (!d_pbSplitTime.has_value())
    {
        d_state = SplitState::NoDataPossible;
    }
    else if (splitTime < d_pbSplitTime)
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
    
    SPDLOG_DEBUG("SPLIT MADE. Name: {} - Split time only: {} - Result: {}", 
                 d_name, splitTime.count(), d_state);
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
    
    SPDLOG_DEBUG("SPLIT MADE. Name: {} - Split time: {} - Segment time: {}. Result {}", 
                 d_name, splitTime.count(), segmentTime.count(), d_state);
    return d_state;
}

SplitState Split::resetSplit()
{
    d_state = SplitState::NotReached;
    d_segmentTime.reset();
    d_splitTime.reset();

    SPDLOG_DEBUG("SPLIT {} RESET.", d_name);

    return d_state;
}

void Split::print(std::ostream& stream) const
{
    using microseconds = std::chrono::microseconds;
    stream << "{[SPLIT] Name: " << d_name << ", "
           << "State: " << d_state << ", "
           << "Gold Time: " 
           << timerutils::microseconds2string(d_goldTime.value_or(microseconds(0))) << ", "
           << "PB Segment Time: "
           << timerutils::microseconds2string(d_pbSegmentTime.value_or(microseconds(0))) << ", "
           << "This Segment Time: "
           << timerutils::microseconds2string(d_segmentTime.value_or(microseconds(0))) << ", "
           << "PB Split Time: "
           << timerutils::microseconds2string(d_pbSplitTime.value_or(microseconds(0))) << ", "
           << "This Split Time: "
           << timerutils::microseconds2string(d_splitTime.value_or(microseconds(0))) << "}";
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