#include <gtest/gtest.h>

#include <core/split.h>
#include <core/splitter.h>
#include <core/adhocsplitter.h>

using namespace csplit;
using microseconds = std::chrono::microseconds;

TEST(AdHocSplitterTest, TestSplitFirstSplit)
{
    core::AdHocSplitter splitter{};
    EXPECT_TRUE(splitter.splits().empty());

    microseconds time(23000);
    splitter.split(time);

    ASSERT_FALSE(splitter.splits().empty());

    const auto& split = splitter.currentSplit();
    EXPECT_EQ(split->thisSplitTime(), time);
    EXPECT_EQ(split->thisSegmentTime(), time);
}

TEST(AdHocSplitterTest, TestSplitSecondSplit)
{
    core::AdHocSplitter splitter{};
    EXPECT_TRUE(splitter.splits().empty());

    microseconds firstTime(25000);
    microseconds secondTime(36000);
    microseconds expectedSegment(11000);

    splitter.split(firstTime);
    splitter.split(secondTime);

    ASSERT_EQ(splitter.splits().size(), 2);

    const auto& split = splitter.currentSplit();
    EXPECT_EQ(split->thisSplitTime(), secondTime);
    EXPECT_EQ(split->thisSegmentTime(), expectedSegment);
}

TEST(AdHocSplitterTest, TestSkipBreaks)
{
    core::AdHocSplitter splitter{};
    ASSERT_DEATH(splitter.skip(), "");
}

TEST(AdHocSplitterTest, TestCantAddSplit)
{
    core::AdHocSplitter splitter{};
    ASSERT_FALSE(splitter.addSplit(core::Split("testSplit")));
}