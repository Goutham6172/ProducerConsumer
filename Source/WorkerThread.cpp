#include "WorkerThread.h"

IMPLEMENT_DYNCREATE(WorkerThread, CWinThread)

WorkerThread::WorkerThread()
    : m_queue(nullptr)
{
}

WorkerThread::~WorkerThread()
{
}

void WorkerThread::SetQueue(ThreadSafeQueue* queue)
{
    m_queue = queue;
}

BOOL WorkerThread::InitInstance()
{
    return TRUE;
}

int WorkerThread::Run()
{
    while (true)
    {
        Item item(0, CTime());

        if (!m_queue->GetFront(item))
            break; // shutdown

        CTime now = CTime::GetCurrentTime();

        if (item.expiryTime <= now)
        {
            // expired → delete
            m_queue->PopFront();
        }
        else
        {
            // not expired → sleep until expiry
            CTimeSpan waitSpan = item.expiryTime - now;
            DWORD waitMs = (DWORD)waitSpan.GetTotalSeconds() * 1000;

            ::Sleep(waitMs);
        }
    }

    return 0;
}
