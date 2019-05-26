#pragma once

#include "splitter.h"
#include "split.h"

#include <vector>
#include <chrono>

namespace csplit {
namespace core {

class TimeAttackSplitter: public Splitter
{
using SplitIndex = std::vector<Split>::size_type;
private:
    SplitIndex d_currentSplit;
    std::vector<Split> d_splits;
    Split& currentSplit();
public:
    TimeAttackSplitter(const std::vector<Split>& splits);
    SplitState split(const std::chrono::microseconds& time) override;
    void addSplit(const Split& split);
};

}
}