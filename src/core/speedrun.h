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

    std::string d_gameName;
    std::string d_categoryName;
public:
    Speedrun(std::string gameName, std::string categoryName);
    Speedrun(std::string gameName, std::string categoryName, std::vector<Split> splits);
    Speedrun(std::string gameName, std::string categoryName, std::unique_ptr<Splitter> splitter);

    void start();   // Could eventually take an optional delay
    SplitState split();
    void addSplit(const Split& split);

    const std::string& gameName() const;
    const std::string& categoryName() const;
    bool isInProgress() const;
};

} // end namespace core
} // end namespace csplit