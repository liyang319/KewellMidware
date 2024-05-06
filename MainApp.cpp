#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "NodeThread.h"
#include "ComThread.h"
#include <unistd.h>
#include "UpperTcpClient.h"

#define MAX_CHANNEL_NUM 16

void *threadCallback(void *arg)
{
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Thread " << i << std::endl;
        sleep(1);
    }
    return NULL;
}

int main()
{

    printf("hello world\n");
    // ComThread mThread(threadCallback);
    // mThread.start();
    // mThread.join();

    // UpperTcpClient mClient("127.0.0.1", 8080);
    // mClient.Init();
    UpperTcpClient &mClient = UpperTcpClient::getInstance("127.0.0.1", 8080);
    // UpperTcpClient mClient("127.0.0.1", 8080);
    mClient.Init();

    // for (int i = 0; i < MAX_CHANNEL_NUM; i++)
    // {
    //     char ip[16] = "192.168.20.220";
    //     int index = i;
    //     int port = 1234;

    //     NodeThread thread(index, ip, port);
    //     thread.start();
    //     sleep(1);
    // }

    // 等待一段时间
    // sleep(60);
    // thread.stop();

    return 0;
}