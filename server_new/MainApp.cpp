#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <thread>
#include <atomic>
#include <queue>
#include <mutex>
#include "AppData.h"
#include "UpperTcpServer.h"
#include "UpperWorkerThread.h"

int main()
{
    UpperTcpServer server(8001, 8002);
    UpperWorkerThread workerThread;
    // workerThread.start();
    server.start();
    workerThread.start();
    printf("-----begin------\n");
    // Stop the server after 10 seconds
    // sleep(10);
    // server.stop();

    // workerThread.join();
    server.join();
    workerThread.join();
    return 0;
}