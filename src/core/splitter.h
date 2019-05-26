#pragma once

#include "split.h"

#include <vector>

namespace csplit {
namespace core {

class Splitter
{
private:
public:
    Splitter();
    virtual ~Splitter() {}

    virtual SplitState split(const std::chrono::microseconds& time) = 0;
};

} // end namespace core
} // end namespace csplit