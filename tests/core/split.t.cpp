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
    EXPECT_EQ(testSplit.thisSegmentTime(), std::chrono::microseconds(1200));
    EXPECT_EQ(testSplit.thisSplitTime(), std::chrono::microseconds(12000));
}

TEST(TestSplit, TestUpdateEqualPb)
{
    auto goldTime = std::chrono::microseconds(1100);
    auto pbSegmentTime = std::chrono::microseconds(1300);
    auto pbSplitTime = std::chrono::microseconds(13000);

    auto testSplit = core::Split("testSplit", goldTime, pbSegmentTime, pbSplitTime);
    auto res = testSplit.updateTime(pbSegmentTime, std::chrono::microseconds(14000));

    EXPECT_EQ(res._value, core::SplitState::EqualPb);
    EXPECT_EQ(testSplit.thisSplitTime(), std::chrono::microseconds(14000));
    EXPECT_EQ(testSplit.pbSegmentTime(), testSplit.thisSegmentTime());
    EXPECT_EQ(testSplit.goldTime(), goldTime);
}

TEST(TestSplit, TestUpdateGoldAhead)
{
    // GIVEN
    auto goldTime = microseconds(1100);
    auto pbSegmentTime = microseconds(1300);
    auto pbSplitTime = microseconds(14000);
    auto newGold = microseconds(1000);
    auto thisSegmentTime = microseconds(13500);
    
    auto testSplit = core::Split("testSplit", goldTime, pbSegmentTime, pbSplitTime);

    // WHEN
    auto res = testSplit.updateTime(newGold, thisSegmentTime);

    // THEN
    EXPECT_EQ(res._value, core::SplitState::GoldAhead);
}

TEST(TestSplit, TestUpdateGoldBehind)
{
    // GIVEN
    auto goldTime = microseconds(1100);
    auto pbSegmentTime = microseconds(1300);
    auto pbSplitTime = microseconds(14000);
    auto newGold = microseconds(1000);
    auto thisSegmentTime = microseconds(16000);

    auto testSplit = core::Split("testSplit", goldTime, pbSegmentTime, pbSplitTime);

    // WHEN
    auto res = testSplit.updateTime(newGold, thisSegmentTime);

    // THEN
    EXPECT_EQ(res._value, core::SplitState::GoldBehind);
}

TEST(TestSplit, TestUpdateAheadGaining)
{
    // GIVEN
    auto goldTime = microseconds(1100);
    auto pbSegmentTime = microseconds(1300);
    auto pbSplitTime = microseconds(15000);

    auto thisSegment = microseconds(1200);
    auto thisSplit = microseconds(14500);

    auto testSplit = core::Split("testSplit", goldTime, pbSegmentTime, pbSplitTime);

    // WHEN
    auto res = testSplit.updateTime(thisSegment, thisSplit);

    // THEN
    EXPECT_EQ(res._value, core::SplitState::AheadPbGainingTime);
}

TEST(TestSplit, TestUpdateAheadLosing)
{
    // GIVEN
    auto goldTime = microseconds(1100);
    auto pbSegmentTime = microseconds(1300);
    auto pbSplitTime = microseconds(15000);

    auto thisSegment = microseconds(1400);
    auto thisSplit = microseconds(14500);

    auto testSplit = core::Split("testSplit", goldTime, pbSegmentTime, pbSplitTime);

    // WHEN
    auto res = testSplit.updateTime(thisSegment, thisSplit);

    // THEN
    EXPECT_EQ(res._value, core::SplitState::AheadPbLosingTime);
}

TEST(TestSplit, TestUpdateBehindGaining)
{
    // GIVEN
    auto goldTime = microseconds(1100);
    auto pbSegmentTime = microseconds(1300);
    auto pbSplitTime = microseconds(15000);

    auto thisSegment = microseconds(1200);
    auto thisSplit = microseconds(16000);

    auto testSplit = core::Split("testSplit", goldTime, pbSegmentTime, pbSplitTime);

    // WHEN
    auto res = testSplit.updateTime(thisSegment, thisSplit);

    // THEN
    EXPECT_EQ(res._value, core::SplitState::BehindPbGainingTime);
}

TEST(TestSplit, TestUpdateBehindLosing)
{
    // GIVEN
    auto goldTime = microseconds(1100);
    auto pbSegmentTime = microseconds(1300);
    auto pbSplitTime = microseconds(15000);

    auto thisSegment = microseconds(1400);
    auto thisSplit = microseconds(16000);

    auto testSplit = core::Split("testSplit", goldTime, pbSegmentTime, pbSplitTime);

    // WHEN
    auto res = testSplit.updateTime(thisSegment, thisSplit);

    // THEN
    EXPECT_EQ(res._value, core::SplitState::BehindPbLosingTime);
}

TEST(TestSplit, TestResetSplit)
{
    auto testSplit = core::Split("testSplit");

    EXPECT_EQ(testSplit.state()._value, core::SplitState::NotReached);   

    auto res = testSplit.updateTime(microseconds(1400), microseconds(15000));
    EXPECT_EQ(res._value, core::SplitState::GoldAhead);
    EXPECT_TRUE(testSplit.thisSegmentTime().has_value());
    EXPECT_TRUE(testSplit.thisSplitTime().has_value());

    res = testSplit.resetSplit();
    EXPECT_EQ(res._value, core::SplitState::NotReached);

    EXPECT_EQ(testSplit.state()._value, core::SplitState::NotReached);
    EXPECT_FALSE(testSplit.thisSegmentTime().has_value());
    EXPECT_FALSE(testSplit.thisSplitTime().has_value());
}