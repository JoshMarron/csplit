#pragma once

#include "split.h"

#include <vector>

#include <spdlog/fmt/ostr.h>

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
    virtual void print(std::ostream&) const = 0;
};

inline
std::ostream& operator<<(std::ostream& stream, const core::Splitter& splitter)
{
    splitter.print(stream);
    return stream;
}

} // end namespace core
} // end namespace csplit