#pragma once
#include <atomic>
#include <chrono>
#include <functional>
#include "../CoreAPI.h"

namespace Core::Statistics
{
    class CORE_API CountStatistic
    {
    public:
        CountStatistic(const char* Name);

        void Increment() { ++m_count; }
        void Add(uint64_t Inc) { m_count += Inc; }

        uint64_t GetValue() const { return m_count.load(std::memory_order_relaxed); }
        const char* GetName() const { return m_statName; }

    private:
        const char* m_statName;
        std::atomic<uint64_t> m_count = 0;
    };

    class CORE_API StatisticsManager
    {
    public:
        void RegisterCounter(CountStatistic* Counter);

        static StatisticsManager& Get();

        void IterateCounter(std::function<void(CountStatistic&)> ItFnc);

    private:
        StatisticsManager() = default;
        ~StatisticsManager() = default;
        
        std::mutex m_mutex;
        std::vector<CountStatistic*>  m_counters;
    };
}

#define CREATE_STATIC_COUNTER_STATISTIC(Name) static Core::Statistics::CountStatistic Name(#Name)
#define INCREMENT_STATISTIC(Stat) Stat.Increment()
#define INCREMENT_BY_STATISTIC(Stat, Val) Stat.Add(Val)