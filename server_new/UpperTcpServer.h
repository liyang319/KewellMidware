#ifndef UPPER_TCP_SERVER_H
#define UPPER_TCP_SERVER_H

#include <iostream>
#include <thread>
#include <atomic>
#include <array>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <errno.h>
#include "AppData.h"

class UpperTcpServer
{
public:
    UpperTcpServer(int data_port, int ctrl_port);
    void start();
    void stop();
    void join();

private:
    int data_port;
    int ctrl_port;
    int data_socket;
    int ctrl_socket;
    std::atomic<bool> is_running;

    int createSocket(int port);
    void handleDataConnection(int client_socket);
    void handleCtrlConnection(int client_socket);
    void run();
};

#endif // UPPER_TCP_SERVER_H
