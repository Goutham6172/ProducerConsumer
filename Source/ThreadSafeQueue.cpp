#include "ThreadSafeQueue.h"

ThreadSafeQueue::ThreadSafeQueue()
    : m_shutdown(false)
{
    InitializeCriticalSection(&m_cs);
    InitializeConditionVariable(&m_cv);
}

ThreadSafeQueue::~ThreadSafeQueue()
{
    DeleteCriticalSection(&m_cs);
}

void ThreadSafeQueue::Push(const Item& item)
{
    EnterCriticalSection(&m_cs);

    m_queue.push_back(item);

    LeaveCriticalSection(&m_cs);

    // Wake worker thread
    WakeConditionVariable(&m_cv);
}

bool ThreadSafeQueue::GetFront(Item& outItem)
{
    EnterCriticalSection(&m_cs);

    while (m_queue.empty() && !m_shutdown)
    {
        SleepConditionVariableCS(&m_cv, &m_cs, INFINITE);
    }

    if (m_shutdown)
    {
        LeaveCriticalSection(&m_cs);
        return false;
    }

    outItem = m_queue.front();

    LeaveCriticalSection(&m_cs);
    return true;
}

void ThreadSafeQueue::PopFront()
{
    EnterCriticalSection(&m_cs);

    if (!m_queue.empty())
    {
        m_queue.pop_front();
    }

    LeaveCriticalSection(&m_cs);
}

void ThreadSafeQueue::Shutdown()
{
    EnterCriticalSection(&m_cs);
    m_shutdown = true;
    LeaveCriticalSection(&m_cs);

    WakeAllConditionVariable(&m_cv);
}
