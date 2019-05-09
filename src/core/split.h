#pragma once

#include <string>
#include <chrono>
#include <optional>
#include <enum.h>

namespace csplit {
namespace core {

BETTER_ENUM(SplitState, int,
            EqualPb,
            AheadPbGainingTime,
            AheadPbLosingTime,
            BehindPbGainingTime,
            BehindPbLosingTime,
            GoldAhead,
            GoldBehind);

// A POD struct to represent a split
// A split has a name, a best time and possibly a current run time? Does this belong in the run or
// the split?
class Split
{
private:
    using PossibleTime = std::optional<std::chrono::microseconds>;
    std::string d_name;
    PossibleTime d_goldTime;
    PossibleTime d_pbTime;
    PossibleTime d_currentTime;
    PossibleTime d_cumulativeTime;
    PossibleTime d_cumulativePbTime;
public:
    Split(std::string name);
    Split(std::string name, 
          std::chrono::microseconds goldTime, 
          std::chrono::microseconds pbTime,
          std::chrono::microseconds cumulativePbTime);

    const std::string& name() const;
    const PossibleTime& goldTime() const;
    const PossibleTime& pbTime() const;
    const PossibleTime& thisRunTime() const;

    void changeSplitName(std::string name);
    SplitState updateTime(std::chrono::microseconds time,
                          std::chrono::microseconds currentRunTime);
};

} // end namespace core
} // end namespace csplit