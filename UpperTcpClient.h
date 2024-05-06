#ifndef UPPER_TCP_CLIENT_H
#define UPPER_TCP_CLIENT_H

#include <iostream>
#include <string>
#include <thread>
#include "ComThread.h"

class UpperTcpClient
{
public:
    static UpperTcpClient &getInstance(const std::string &server_ip, int server_port);
    ~UpperTcpClient();

    void Init();
    static void *SendThreadFun(void *arg);
    static void *RecvThreadFun(void *arg);

private:
    UpperTcpClient(const std::string &server_ip, int server_port);
    std::string server_ip_;
    int server_port_;
    int socket_fd_;
    ComThread *pSend_thread;
    ComThread *pRecv_thread;

    bool is_running_;
};

#endif // UPPER_TCP_CLIENT_H
