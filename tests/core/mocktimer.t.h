#pragma once

#include <gmock/gmock.h>
#include <chrono>
#include <ratio>
#include <core/timer.h>

class MockTimer: public csplit::core::Timer
{
public:
    MOCK_METHOD0(start, void());
    MOCK_CONST_METHOD0(elapsed, std::chrono::microseconds());
    MOCK_CONST_METHOD0(split, std::chrono::microseconds());
    MOCK_CONST_METHOD1(print, void(std::ostream&));
};