#ifndef COMTHREAD_H
#define COMTHREAD_H

#include <pthread.h>

class ComThread
{
public:
    ComThread(void *(*threadFunc)(void *));
    virtual ~ComThread();

    void start();
    void stop();
    void join();

private:
    static void *threadFunc(void *arg);
    pthread_t m_thread;
    bool m_running;
    void *(*m_threadFunc)(void *);
};

#endif // COMTHREAD_H
