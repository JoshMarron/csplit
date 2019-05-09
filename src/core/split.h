#pragma once

#include <string>
#include <chrono>
#include <optional>

namespace csplit {
namespace core {

enum class SplitState {
    EqualPb,
    FasterThanPb,
    SlowerThanPb,
    Gold
};

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
public:
    Split(std::string name);
    Split(std::string name, std::chrono::microseconds goldTime, std::chrono::microseconds pbTime);

    const std::string& name() const;
    const PossibleTime& goldTime() const;
    const PossibleTime& pbTime() const;

    void changeSplitName(std::string name);
    SplitState updateTime(std::chrono::microseconds);
};

} // end namespace core
} // end namespace csplit