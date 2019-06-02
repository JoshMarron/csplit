#include <gtest/gtest.h>

#include "splitter.t.h"

#include <core/speedrun.h>
#include <core/steadytimer.h>

using namespace csplit;
using microseconds = std::chrono::microseconds;

class MockSplitterSpeedrunTest: public ::testing::Test
{
protected:
    MockSplitter* d_splitter;
    core::Speedrun d_speedrun;

    MockSplitterSpeedrunTest()
    : d_splitter(new MockSplitter())
    , d_speedrun("testRun",
                 "any%",
                 std::unique_ptr<core::Splitter>(d_splitter),
                 std::make_unique<core::SteadyTimer>())
    {}
};

TEST_F(MockSplitterSpeedrunTest, TestStartRun)
{
    using ::testing::ReturnRef;

    std::vector<core::Split> emptyVec{};
    EXPECT_CALL(*d_splitter, splits()).Times(1).WillOnce(ReturnRef(emptyVec));

    d_speedrun.start();

    EXPECT_TRUE(d_speedrun.isInProgress());
}

TEST_F(MockSplitterSpeedrunTest, TestDelegateToSplitter)
{
    using ::testing::Return;
    using ::testing::ReturnRef;
    using ::testing::_;

    std::vector<core::Split> emptyVec{};
    EXPECT_CALL(*d_splitter, split(_)).Times(1).WillOnce(Return(core::SplitState::GoldAhead));
    EXPECT_CALL(*d_splitter, splits()).Times(1).WillOnce(ReturnRef(emptyVec));
    d_speedrun.start();
    auto res = d_speedrun.split();

    EXPECT_EQ(core::SplitState::GoldAhead, res);
}

TEST_F(MockSplitterSpeedrunTest, TestDieOnSplitBeforeStart)
{
    EXPECT_DEATH(d_speedrun.split(), "");
}

TEST(SpeedrunTest, TestAddSplit)
{
    core::Speedrun run("testRun", "any%");
    core::Split newSplit("testSplit");

    run.addSplit(newSplit);
    EXPECT_EQ(run.splits().back(), newSplit);
}