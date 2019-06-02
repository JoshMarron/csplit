#include <gtest/gtest.h>

#include <core/split.h>
#include <core/splitter.h>
#include <core/timeattacksplitter.h>

using namespace csplit;
using microseconds = std::chrono::microseconds;

class TimeAttackSplitterTest: public ::testing::Test
{
protected:
    std::vector<core::Split> d_splits;
};

TEST_F(TimeAttackSplitterTest, TestSplitFirstSplit)
{
    core::Split firstSplit("testSplit");
    d_splits.push_back(firstSplit);
    core::TimeAttackSplitter splitter(d_splits);

    microseconds time(25000);
    auto result = splitter.split(time);

    const auto& updatedSplit = splitter.splits()[0];

    EXPECT_EQ(result, core::SplitState::GoldAhead);
    EXPECT_EQ(updatedSplit.thisSegmentTime(), time);
    EXPECT_EQ(updatedSplit.thisSplitTime(), time);
}

TEST_F(TimeAttackSplitterTest, TestSplitSecondSplit)
{
    core::Split firstSplit("testSplit");
    core::Split secondSplit("testSplit2");

    d_splits = {firstSplit, secondSplit};
    core::TimeAttackSplitter splitter(d_splits);

    microseconds firstTime(25000);
    microseconds secondTime(36000);
    microseconds expectedSegment = secondTime - firstTime;

    splitter.split(firstTime);
    auto res = splitter.split(secondTime);
    const auto& updatedSplit = splitter.splits()[1];

    EXPECT_EQ(res, core::SplitState::GoldAhead);
    EXPECT_EQ(updatedSplit.thisSegmentTime(), expectedSegment);
    EXPECT_EQ(updatedSplit.thisSplitTime(), secondTime);
}

TEST_F(TimeAttackSplitterTest, TestSkipSplit)
{
    core::Split split("testSplit");
    d_splits = {split};
    core::TimeAttackSplitter splitter(d_splits);

    splitter.skip();
    const auto& updatedSplit = splitter.splits()[0];

    EXPECT_FALSE(updatedSplit.thisSegmentTime().has_value());
    EXPECT_FALSE(updatedSplit.thisSplitTime().has_value());
    EXPECT_FALSE(splitter.currentSplit().has_value());
}

TEST_F(TimeAttackSplitterTest, TestSplitAfterSkip)
{
    core::Split firstSplit("testSplit1");
    core::Split secondSplit("testSplit2");
    d_splits = {firstSplit, secondSplit};
    core::TimeAttackSplitter splitter(d_splits);

    microseconds time(36000);

    splitter.skip();
    splitter.split(time);
    const auto& updatedSplit = splitter.splits()[1];

    EXPECT_FALSE(updatedSplit.thisSegmentTime().has_value());
    EXPECT_EQ(updatedSplit.thisSplitTime(), time);
}

TEST_F(TimeAttackSplitterTest, TestAddSplit)
{
    core::Split newSplit("newSplit");
    core::TimeAttackSplitter splitter(d_splits);

    EXPECT_TRUE(splitter.addSplit(newSplit));
    EXPECT_EQ(newSplit, splitter.splits().back());
}