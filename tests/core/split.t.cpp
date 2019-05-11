#include <gtest/gtest.h>
#include <core/split.h>

using namespace csplit;

TEST(TestSplit, TestUpdateEmptySplit)
{
    auto testSplit = core::Split("testSplit");
    auto res = testSplit.updateTime(std::chrono::microseconds(1200), 
                                    std::chrono::microseconds(12000));
    
    EXPECT_EQ(res._value, core::SplitState::GoldAhead);
    EXPECT_EQ(testSplit.thisRunTime(), std::chrono::microseconds(1200));
    EXPECT_EQ(testSplit.thisRunCumulativeTime(), std::chrono::microseconds(12000));
}

TEST(TestSplit, TestUpdateEqualPb)
{
    auto goldTime = std::chrono::microseconds(1100);
    auto pbTime = std::chrono::microseconds(1300);
    auto cumulativePbTime = std::chrono::microseconds(13000);

    auto testSplit = core::Split("testSplit", goldTime, pbTime, cumulativePbTime);
    auto res = testSplit.updateTime(pbTime, std::chrono::microseconds(14000));

    EXPECT_EQ(res._value, core::SplitState::EqualPb);
    EXPECT_EQ(testSplit.thisRunCumulativeTime(), std::chrono::microseconds(14000));
    EXPECT_EQ(testSplit.pbTime(), testSplit.thisRunTime());
    EXPECT_EQ(testSplit.goldTime(), goldTime);
}