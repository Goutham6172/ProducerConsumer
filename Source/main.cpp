void CMyDialog::OnAddItem()
{
    static int counter = 1;

    CTime now = CTime::GetCurrentTime();
    CTime expiry = now + CTimeSpan(0, 0, 0, 10); // +10 seconds

    Item item(counter++, expiry);

    m_queue.Push(item);
}

OnInitDialog()
{
    m_workerThread = (WorkerThread*)AfxBeginThread(RUNTIME_CLASS(WorkerThread));
    m_workerThread->SetQueue(&m_queue);
}

OnDestroy()
{
    m_queue.Shutdown();
    WaitForSingleObject(m_workerThread->m_hThread, INFINITE);

}

private:
    ThreadSafeQueue m_queue;
    WorkerThread*   m_workerThread;  // ← THIS
