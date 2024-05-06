#ifndef COMTHREAD_H
#define COMTHREAD_H

#include <pthread.h>
#include <iostream>

class ComThread
{
public:
    ComThread();
    ComThread(void *(*threadFunc)(void *));
    virtual ~ComThread();

    void start();
    void stop();
    void join();

    void setCallbackFun(void *(*threadFunc)(void *));

private:
    static void *threadFunc(void *arg);
    pthread_t m_thread;
    bool m_running;
    void *(*m_threadFunc)(void *);
};

#endif // COMTHREAD_H
