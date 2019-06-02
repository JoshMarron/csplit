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
    Split& currentSplitMut();
public:
    TimeAttackSplitter(const std::vector<Split>& splits);
    SplitState split(const std::chrono::microseconds& time) override;
    bool addSplit(const Split& split) override;
    std::optional<Split> currentSplit() const override;
    const std::vector<Split>& splits() const override;
    void skip() override;
};

}
}