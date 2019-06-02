#include <gtest/gtest.h>
#include <core/split.h>

using namespace csplit;
using microseconds = std::chrono::microseconds;

TEST(TestSplit, TestUpdateEmptySplit)
{
    auto testSplit = core::Split("testSplit");
    auto res = testSplit.updateTime(microseconds(12000),
                                    microseconds(1200));

    EXPECT_EQ(res, core::SplitState::GoldAhead);
    EXPECT_EQ(testSplit.thisSegmentTime(), microseconds(1200));
    EXPECT_EQ(testSplit.thisSplitTime(), microseconds(12000));
}

TEST(TestSplit, TestUpdateEqualPb)
{
    auto goldTime = microseconds(1100);
    auto pbSegmentTime = microseconds(1300);
    auto pbSplitTime = microseconds(13000);

    auto testSplit = core::Split("testSplit", goldTime, pbSegmentTime, pbSplitTime);
    auto res = testSplit.updateTime(microseconds(14000), pbSegmentTime);

    EXPECT_EQ(res, core::SplitState::EqualPb);
    EXPECT_EQ(testSplit.thisSplitTime(), microseconds(14000));
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
    auto res = testSplit.updateTime(thisSegmentTime, newGold);

    // THEN
    EXPECT_EQ(res, core::SplitState::GoldAhead);
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
    auto res = testSplit.updateTime(thisSegmentTime, newGold);

    // THEN
    EXPECT_EQ(res, core::SplitState::GoldBehind);
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
    auto res = testSplit.updateTime(thisSplit, thisSegment);

    // THEN
    EXPECT_EQ(res, core::SplitState::AheadPbGainingTime);
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
    auto res = testSplit.updateTime(thisSplit, thisSegment);

    // THEN
    EXPECT_EQ(res, core::SplitState::AheadPbLosingTime);
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
    auto res = testSplit.updateTime(thisSplit, thisSegment);

    // THEN
    EXPECT_EQ(res, core::SplitState::BehindPbGainingTime);
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
    auto res = testSplit.updateTime(thisSplit, thisSegment);

    // THEN
    EXPECT_EQ(res, core::SplitState::BehindPbLosingTime);
}

TEST(TestSplit, TestResetSplit)
{
    auto testSplit = core::Split("testSplit");

    EXPECT_EQ(testSplit.state(), core::SplitState::NotReached);

    auto res = testSplit.updateTime(microseconds(15000), microseconds(1400));
    EXPECT_EQ(res, core::SplitState::GoldAhead);
    EXPECT_TRUE(testSplit.thisSegmentTime().has_value());
    EXPECT_TRUE(testSplit.thisSplitTime().has_value());

    res = testSplit.resetSplit();
    EXPECT_EQ(res, core::SplitState::NotReached);

    EXPECT_EQ(testSplit.state(), core::SplitState::NotReached);
    EXPECT_FALSE(testSplit.thisSegmentTime().has_value());
    EXPECT_FALSE(testSplit.thisSplitTime().has_value());
}

TEST(TestSplit, TestUpdateSplitOnlyBehind)
{
    auto goldTime = microseconds(1100);
    auto pbSegmentTime = microseconds(1200);
    auto pbSplitTime = microseconds(15000);

    auto testSplit = core::Split("testSplit", goldTime, pbSegmentTime, pbSplitTime);
    auto res = testSplit.updateTime(microseconds(16000));

    EXPECT_EQ(res, core::SplitState::BehindPbNoData);
}

TEST(TestSplit, TestUpdateSplitOnlyAhead)
{
    auto goldTime = microseconds(1100);
    auto pbSegmentTime = microseconds(1200);
    auto pbSplitTime = microseconds(15000);

    auto testSplit = core::Split("testSplit", goldTime, pbSegmentTime, pbSplitTime);
    auto res = testSplit.updateTime(microseconds(14000));

    EXPECT_EQ(res, core::SplitState::AheadPbNoData);
}

TEST(TestSplit, TestUpdateSplitOnlyEqual)
{
    auto goldTime = microseconds(1100);
    auto pbSegmentTime = microseconds(1200);
    auto pbSplitTime = microseconds(15000);

    auto testSplit = core::Split("testSplit", goldTime, pbSegmentTime, pbSplitTime);
    auto res = testSplit.updateTime(microseconds(15000));

    EXPECT_EQ(res, core::SplitState::EqualPb);
}

TEST(TestSplit, TestUpdateSplitOnlyOnNewSplit)
{
    auto testSplit = core::Split("testSplit");
    auto res = testSplit.updateTime(microseconds(1111));

    EXPECT_EQ(res, core::SplitState::NoDataPossible);
}

TEST(TestSplit, TestSplitEqualityEmptySplits)
{
    core::Split lhsSplit("testSplit");
    core::Split rhsSplit("testSplit");

    EXPECT_EQ(lhsSplit, rhsSplit);

    core::Split secondRhsSplit("testSplit2");
    EXPECT_NE(lhsSplit, secondRhsSplit);
}

TEST(TestSplit, TestSplitEquality)
{
    core::Split lhsSplit("testSplit", microseconds(2300), microseconds(1200), microseconds(1300));
    core::Split rhsSplit("testSplit", microseconds(2300), microseconds(1200), microseconds(1300));

    EXPECT_EQ(lhsSplit, rhsSplit);

    core::Split secondRhsSplit("testSplit", microseconds(1400), microseconds(1200), microseconds(1300));
    EXPECT_NE(lhsSplit, secondRhsSplit);
}