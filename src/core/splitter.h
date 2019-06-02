#pragma once

#include "split.h"

#include <vector>

namespace csplit {
namespace core {

class Splitter
{
private:
public:
    Splitter() {}
    virtual ~Splitter() {}

    virtual SplitState split(const std::chrono::microseconds& time) = 0;
    virtual bool addSplit(const Split& split) = 0;
    virtual const std::vector<Split>& splits() const = 0;
    virtual std::optional<Split> currentSplit() const = 0;
    virtual void skip() = 0;
};

} // end namespace core
} // end namespace csplit