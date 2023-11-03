#pragma once
#include <mutex>
#include <list>

namespace Core::Pool
{
    struct NoThreadPoolLock
    {
        void lock() {}
        void unlock() {}
    };

    using MultithreadedPoolLock = std::mutex;

    template<typename T, typename PoolLock = MultithreadedPoolLock>
    class SimpleReusePool
    {
    public:
        class ReuseHandle
        {
        public:
            ReuseHandle(std::list<T>::iterator it) :
                m_it{ it }
            {}

            ReuseHandle(const ReuseHandle&) = delete;
            ReuseHandle& operator=(const ReuseHandle&) = delete;

            ReuseHandle(ReuseHandle&& other)
            {
                this->m_it = std::move(other.m_it);
            }

            ReuseHandle& operator=(ReuseHandle&& other)
            {
                this->m_it = std::move(other.m_it);

                return *this;
            }

            operator T& () { return *m_it; }

        private:
            std::list<T>::iterator m_it;

            friend class SimpleReusePool;
        };
    public:
        /// <summary>
        /// This does not guarantee an allocation
        /// </summary>
        template<typename ... Args>
        ReuseHandle Allocate(Args&& ... args)
        {
            std::scoped_lock<decltype(m_poolLock)> lock(m_poolLock);

            if (!m_freeList.empty())
            {
                m_usedList.splice(m_usedList.end(), m_freeList, std::prev(m_freeList.end()));
                return std::prev(m_usedList.end());
            }
            m_usedList.emplace_back(std::forward<Args>(args)...);
            return std::prev(m_usedList.end());
        }

        void Free(ReuseHandle Handle)
        {
            std::scoped_lock<decltype(m_poolLock)> lock(m_poolLock);
#ifdef DEBUG_POOL_MEMORY
            uint32_t prevFreeSize = m_freeList.size();
            uint32_t prevUseSize = m_usedList.size();
#endif
            m_freeList.splice(m_freeList.end(), m_usedList, Handle.m_it);

#ifdef DEBUG_POOL_MEMORY
            check(prevUseSize - 1 == m_usedList.size());
            check(prevFreeSize + 1 == m_freeList.size());
#endif
        }

    private:
        PoolLock m_poolLock;
        std::list<T> m_usedList;
        std::list<T> m_freeList;
    };
}