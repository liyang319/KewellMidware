#include "NodeThread.h"
#include <iostream>
#include <unistd.h>

NodeThread::NodeThread() : running(false) {}

NodeThread::NodeThread(int index, char *ip, int port) : running(false)
{
    this->chl_index = index;
    this->chl_port = port;
    strncpy(this->chl_ip, ip, sizeof(this->chl_ip));
}

void NodeThread::start()
{
    if (!running)
    {
        running = true;
        pthread_create(&thread, NULL, &NodeThread::threadFunc, this);
    }
}

void NodeThread::stop()
{
    if (running)
    {
        running = false;
        pthread_join(thread, NULL);
    }
}

void *NodeThread::threadFunc(void *arg)
{
    NodeThread *self = static_cast<NodeThread *>(arg);
    self->run();
    return NULL;
}

void NodeThread::run()
{
    // 线程执行的代码
    // std::cout << "Thread is running" << std::endl;
    std::cout << "Thread " << chl_index << " is running with IP: " << chl_ip << " and port: " << chl_port << std::endl;
    printf("\n");
}