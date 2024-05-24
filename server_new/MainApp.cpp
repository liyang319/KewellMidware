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

int main()
{
    UpperTcpServer server(8001, 8002);
    server.start();

    // Stop the server after 10 seconds
    sleep(10);
    server.stop();

    return 0;
}