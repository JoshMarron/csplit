#include "speedrun.h"
#include "timerutils.h"
#include "logging.h"

#include "timeattacksplitter.h"
#include "adhocsplitter.h"
#include "steadytimer.h"

#include <spdlog/spdlog.h>
#include <utility>

namespace csplit {
namespace core {

Speedrun::Speedrun(std::string gameName, std::string categoryName)
: d_timer(std::make_unique<SteadyTimer>())
, d_started(false)
, d_splitter(std::make_unique<AdHocSplitter>())
, d_gameName(std::move(gameName))
, d_categoryName(std::move(categoryName))
{}

Speedrun::Speedrun(std::string gameName, std::string categoryName, std::vector<Split> splits)
: d_timer(std::make_unique<SteadyTimer>())
, d_started(false)
, d_splitter(std::make_unique<TimeAttackSplitter>(splits))
, d_gameName(std::move(gameName))
, d_categoryName(std::move(categoryName))
{}

Speedrun::Speedrun(std::string gameName,
                   std::string categoryName,
                   std::unique_ptr<Splitter> splitter,
                   std::unique_ptr<Timer> timer)
: d_timer(std::move(timer))
, d_started(false)
, d_splitter(std::move(splitter))
, d_gameName(std::move(gameName))
, d_categoryName(std::move(categoryName))
{}

void Speedrun::start()
{
    d_timer->start();
    spdlog::info("Run started!");
    if (d_splitter->splits().empty())
    {
        SPDLOG_INFO("Run started without splits loaded, so they will be created ad hoc.");
    }
    d_started = true;
}

SplitState Speedrun::split()
{
    if (!d_started)
    {
        SPDLOG_ERROR("FATAL LOGIC ERROR: A split was attempted before the run started.");
        assert(false);
    }
    auto splitTime = d_timer->split();
    return d_splitter->split(splitTime);
}

void Speedrun::addSplit(const Split& split)
{
    if(!d_splitter->addSplit(split))
    {
        // Then we must be using an adhoc splitter. We can't do that anymore, so change
        auto splits = std::vector<Split>();
        splits.push_back(split);
        d_splitter = std::make_unique<TimeAttackSplitter>(splits);
    }
}

const std::vector<Split>& Speedrun::splits() const
{
    return d_splitter->splits();
}

std::optional<Split> Speedrun::currentSplit() const
{
    return d_splitter->currentSplit();
}

const std::string& Speedrun::gameName() const
{
    return d_gameName;
}

const std::string& Speedrun::categoryName() const
{
    return d_categoryName;
}

bool Speedrun::isInProgress() const
{
    return d_started;
}

} // end namespace core
} // end namespace csplit