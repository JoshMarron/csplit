#pragma once

#define BETTER_ENUMS_STRICT_CONVERSION

#include <string>
#include <chrono>
#include <optional>
#include <enum.h>

#include <spdlog/fmt/ostr.h>

namespace csplit {
namespace core {

BETTER_ENUM(SplitState, int,
            NotReached,
            NoDataPossible,
            EqualPb,
            AheadPbNoData,
            BehindPbNoData,
            AheadPbGainingTime,
            AheadPbLosingTime,
            BehindPbGainingTime,
            BehindPbLosingTime,
            GoldAhead,
            GoldBehind);

// A class to represent a split
// A split has a name, a best (gold) time, a pb time and a time for this run
class Split
{
private:
    using PossibleTime = std::optional<std::chrono::microseconds>;
    std::string d_name;
    SplitState d_state;
    PossibleTime d_goldTime;
    PossibleTime d_pbSegmentTime;
    PossibleTime d_segmentTime;
    PossibleTime d_splitTime;
    PossibleTime d_pbSplitTime;
public:
    Split(std::string name);
    Split(std::string name,
          std::chrono::microseconds goldTime,
          std::chrono::microseconds pbSegmentTime,
          std::chrono::microseconds pbSplitTime);

    const std::string& name() const;
    SplitState state() const;
    const PossibleTime& goldTime() const;
    const PossibleTime& pbSegmentTime() const;
    const PossibleTime& pbSplitTime() const;
    const PossibleTime& thisSegmentTime() const;
    const PossibleTime& thisSplitTime() const;

    void changeSplitName(std::string name);
    SplitState updateTime(std::chrono::microseconds splitTime);
    SplitState updateTime(std::chrono::microseconds splitTime,
                          std::chrono::microseconds segmentTime);
    SplitState resetSplit();

    void print(std::ostream& stream) const;
    friend bool operator==(const Split& lhs, const Split& rhs);
    friend bool operator!=(const Split& lhs, const Split& rhs);
};

inline
std::ostream& operator<<(std::ostream& stream, const core::Split& split)
{
    split.print(stream);
    return stream;
}

inline
bool operator==(const Split& lhs, const Split& rhs)
{
    return lhs.d_name == rhs.d_name &&
           lhs.d_goldTime == rhs.d_goldTime &&
           lhs.d_pbSplitTime == rhs.d_pbSplitTime &&
           lhs.d_pbSegmentTime == rhs.d_pbSegmentTime;
}

inline
bool operator!=(const Split& lhs, const Split& rhs)
{
    return !(lhs == rhs);
}

} // end namespace core
} // end namespace csplit