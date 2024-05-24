#ifndef UPPERWORKERTHREAD_H
#define UPPERWORKERTHREAD_H

#include <thread>

class UpperWorkerThread
{
public:
    UpperWorkerThread();
    ~UpperWorkerThread();

    void start();
    void stop();
    void join(); // 添加join方法

private:
    std::thread m_thread;
    bool m_running;

    void threadFunction();
};

#endif // UPPERWORKERTHREAD_H
