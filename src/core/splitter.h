#pragma once

#include "split.h"

#include <vector>

namespace csplit {
namespace core {

class Splitter
{
private:
    Splitter();
    virtual ~Splitter() {}

    virtual SplitState split(std::vector<Split>& splits) = 0;
};

} // end namespace core
} // end namespace csplit