#pragma once

#ifndef BETTER_ENUMS_STRICT_CONVERSION
#define BETTER_ENUMS_STRICT_CONVERSION
#endif

#include <vector>
#include <enum.h>

#include "split.h"
#include "timer.h"
#include "splitter.h"

namespace csplit {
namespace core {

// A class to represent a speedrun - a speedrun is a series of splits
class Speedrun
{
private:
    Timer d_timer;
    bool d_started;
    std::unique_ptr<Splitter> d_splitter;

public:
    Speedrun(); // Initialize with no splits. This would allow splits to be added
    Speedrun(std::vector<Split> splits);

    void start();   // Could eventually take an optional delay
    SplitState split();
    void addSplit(const Split& split);
};

} // end namespace core
} // end namespace csplit