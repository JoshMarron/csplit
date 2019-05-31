#pragma once

#include "splitter.h"
#include "split.h"

#include <vector>
#include <chrono>

namespace csplit {
namespace core {

class AdHocSplitter: public Splitter
{
private:
    std::vector<Split> d_splits;

    Split createNewSplit();
public:
    AdHocSplitter();
    SplitState split(const std::chrono::microseconds& time) override;
};

} // end namespace core
} // end namespace csplit