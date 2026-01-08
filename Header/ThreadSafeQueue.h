#pragma once
#include <deque>
#include <afx.h>
#include "Item.h"

class ThreadSafeQueue
{
public:
    ThreadSafeQueue();
    ~ThreadSafeQueue();

    void Push(const Item& item);

    // Called ONLY by worker thread
    bool GetFront(Item& outItem);
    void PopFront();

    void Shutdown();

private:
    std::deque<Item> m_queue;

    CRITICAL_SECTION     m_cs;
    CONDITION_VARIABLE  m_cv;

    bool m_shutdown;
};
