#pragma once

#include <gmock/gmock.h>

#include <core/splitter.h>
#include <core/split.h>

class MockSplitter: public csplit::core::Splitter
{
public:
    MOCK_METHOD1(split, csplit::core::SplitState(const std::chrono::microseconds&));
    MOCK_METHOD1(addSplit, bool(const csplit::core::Split&));
    MOCK_CONST_METHOD0(splits, const std::vector<csplit::core::Split>&());
    MOCK_CONST_METHOD0(currentSplit, std::optional<csplit::core::Split>());
    MOCK_METHOD0(skip, void());
};