#include <stdio.h>
#include "NodeThread.h"
#include <unistd.h>

#define MAX_CHANNEL_NUM 16

int main()
{

    printf("hello world\n");

    for (int i = 0; i < MAX_CHANNEL_NUM; i++)
    {
        char ip[16] = "192.168.20.220";
        int index = i;
        int port = 1234;

        NodeThread thread(index, ip, port);
        thread.start();
        sleep(1);
    }

    // 等待一段时间
    sleep(60);
    // thread.stop();

    return 0;
}