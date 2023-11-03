#include "Statistics.h"
#include "../CoreDebug/DebugMacros.h"

Core::Statistics::StatisticsManager& Core::Statistics::StatisticsManager::Get()
{
    static StatisticsManager manager;
    return manager;
}

void Core::Statistics::StatisticsManager::RegisterCounter(CountStatistic* Counter)
{
    check(Counter);
    std::scoped_lock<std::mutex> lock(m_mutex);
    m_counters.emplace_back(Counter);
}

void Core::Statistics::StatisticsManager::IterateCounter(std::function<void(CountStatistic&)> ItFnc)
{
    std::scoped_lock<std::mutex> lock(m_mutex);
    for (auto& counter : m_counters)
    {
        ItFnc(*counter);
    }
}

Core::Statistics::CountStatistic::CountStatistic(const char* Name) :
    m_statName{ Name }
{
    StatisticsManager::Get().RegisterCounter(this);
}
