#pragma once

#include <vector>

#include "split.h"
#include "timer.h"

namespace csplit {
namespace core {

// A class to represent a speedrun - a speedrun is a series of splits
class Speedrun
{
using SplitIndex = std::vector<Split>::size_type;
private:
    std::vector<Split> d_splits;
    SplitIndex d_currentSplit;
    Timer d_timer;
    bool d_started;
    Split& currentSplit();
public:
    Speedrun(); // Initialize with no splits. This would allow splits to be added
    Speedrun(std::vector<Split> splits);

    void start();   // Could eventually take an optional delay
    SplitState split();
    const Split& currentSplit() const;
};

} // end namespace core
} // end namespace csplit