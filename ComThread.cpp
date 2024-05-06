#include "ComThread.h"

ComThread::ComThread() : m_running(false)
{
    m_threadFunc = NULL;
}

ComThread::ComThread(void *(*threadFunc)(void *)) : m_running(false), m_threadFunc(threadFunc)
{
}

ComThread::~ComThread()
{
    if (m_running)
    {
        stop();
    }
}

void ComThread::start()
{
    if (!m_running)
    {
        if (pthread_create(&m_thread, NULL, m_threadFunc, this) == 0)
        {
            m_running = true;
        }
    }
}

void ComThread::stop()
{
    if (m_running)
    {
        pthread_cancel(m_thread);
        m_running = false;
    }
}

void ComThread::join()
{
    if (m_running)
    {
        pthread_join(m_thread, NULL);
        m_running = false;
    }
}

void *ComThread::threadFunc(void *arg)
{
    ComThread *thread = static_cast<ComThread *>(arg);
    if (thread)
    {
        return thread->m_threadFunc(arg);
    }
    return NULL;
}

void ComThread::setCallbackFun(void *(*threadFunc)(void *))
{
    m_threadFunc = threadFunc;
}