#pragma once
#include <afxwin.h>
#include "ThreadSafeQueue.h"

class WorkerThread : public CWinThread
{
    DECLARE_DYNCREATE(WorkerThread)

public:
    WorkerThread();
    virtual ~WorkerThread();

    void SetQueue(ThreadSafeQueue* queue);

protected:
    virtual BOOL InitInstance();
    virtual int Run();

private:
    ThreadSafeQueue* m_queue;
};
