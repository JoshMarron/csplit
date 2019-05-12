#include <gtest/gtest.h>
#include <core/split.h>

using namespace csplit;
using microseconds = std::chrono::microseconds;

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

TEST(TestSplit, TestUpdateGoldAhead)
{
    // GIVEN
    auto goldTime = microseconds(1100);
    auto pbTime = microseconds(1300);
    auto cumulativePbTime = microseconds(14000);
    auto newGold = microseconds(1000);
    auto thisRunTime = microseconds(13500);
    
    auto testSplit = core::Split("testSplit", goldTime, pbTime, cumulativePbTime);

    // WHEN
    auto res = testSplit.updateTime(newGold, thisRunTime);

    // THEN
    EXPECT_EQ(res._value, core::SplitState::GoldAhead);
}

TEST(TestSplit, TestUpdateGoldBehind)
{
    // GIVEN
    auto goldTime = microseconds(1100);
    auto pbTime = microseconds(1300);
    auto cumulativePbTime = microseconds(14000);
    auto newGold = microseconds(1000);
    auto thisRunTime = microseconds(16000);

    auto testSplit = core::Split("testSplit", goldTime, pbTime, cumulativePbTime);

    // WHEN
    auto res = testSplit.updateTime(newGold, thisRunTime);

    // THEN
    EXPECT_EQ(res._value, core::SplitState::GoldBehind);
}

TEST(TestSplit, TestUpdateAheadGaining)
{
    // GIVEN
    auto goldTime = microseconds(1100);
    auto pbTime = microseconds(1300);
    auto cumulativePbTime = microseconds(15000);

    auto thisSplit = microseconds(1200);
    auto thisRunCumulative = microseconds(14500);

    auto testSplit = core::Split("testSplit", goldTime, pbTime, cumulativePbTime);

    // WHEN
    auto res = testSplit.updateTime(thisSplit, thisRunCumulative);

    // THEN
    EXPECT_EQ(res._value, core::SplitState::AheadPbGainingTime);
}

TEST(TestSplit, TestUpdateAheadLosing)
{
    // GIVEN
    auto goldTime = microseconds(1100);
    auto pbTime = microseconds(1300);
    auto cumulativePbTime = microseconds(15000);

    auto thisSplit = microseconds(1400);
    auto thisRunCumulative = microseconds(14500);

    auto testSplit = core::Split("testSplit", goldTime, pbTime, cumulativePbTime);

    // WHEN
    auto res = testSplit.updateTime(thisSplit, thisRunCumulative);

    // THEN
    EXPECT_EQ(res._value, core::SplitState::AheadPbLosingTime);
}

TEST(TestSplit, TestUpdateBehindGaining)
{
    // GIVEN
    auto goldTime = microseconds(1100);
    auto pbTime = microseconds(1300);
    auto cumulativePbTime = microseconds(15000);

    auto thisSplit = microseconds(1200);
    auto thisRunCumulative = microseconds(16000);

    auto testSplit = core::Split("testSplit", goldTime, pbTime, cumulativePbTime);

    // WHEN
    auto res = testSplit.updateTime(thisSplit, thisRunCumulative);

    // THEN
    EXPECT_EQ(res._value, core::SplitState::BehindPbGainingTime);
}

TEST(TestSplit, TestUpdateBehindLosing)
{
    // GIVEN
    auto goldTime = microseconds(1100);
    auto pbTime = microseconds(1300);
    auto cumulativePbTime = microseconds(15000);

    auto thisSplit = microseconds(1400);
    auto thisRunCumulative = microseconds(16000);

    auto testSplit = core::Split("testSplit", goldTime, pbTime, cumulativePbTime);

    // WHEN
    auto res = testSplit.updateTime(thisSplit, thisRunCumulative);

    // THEN
    EXPECT_EQ(res._value, core::SplitState::BehindPbLosingTime);
}