#ifndef NODETHREAD_H
#define NODETHREAD_H

#include <pthread.h>

class NodeThread
{
public:
    NodeThread();
    NodeThread(int index, char *ip, int chl_port);
    void start();
    void stop();

private:
    int chl_index;
    char chl_ip[16];
    int chl_port;
    static void *threadFunc(void *arg);
    void run();

    pthread_t thread;
    bool running;
};

#endif // NODETHREAD_H
