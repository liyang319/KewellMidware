#include "UpperTcpClient.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "ComThread.h"

UpperTcpClient::UpperTcpClient(const std::string &server_ip, int server_port)
    : server_ip_(server_ip), server_port_(server_port), socket_fd_(-1), is_running_(true)
{
}

UpperTcpClient::~UpperTcpClient()
{
    if (socket_fd_ != -1)
    {
        close(socket_fd_);
    }
}

void UpperTcpClient::Init()
{
    // 创建socket
    socket_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd_ == -1)
    {
        std::cerr << "Failed to create socket" << std::endl;
        return;
    }

    // 连接到服务器
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip_.c_str());
    server_addr.sin_port = htons(server_port_);

    if (connect(socket_fd_, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        std::cerr << "Failed to connect to server" << std::endl;
        close(socket_fd_);
        return;
    }

    // 启动发送线程和接收线程
    pSend_thread = new ComThread(SendThreadFun);
    pRecv_thread = new ComThread(RecvThreadFun);

    pSend_thread->start();
    pRecv_thread->start();

    pSend_thread->join();
    pRecv_thread->join();
}

void *UpperTcpClient::SendThreadFun(void *arg)
{
    while (1)
    {
        // 发送数据到服务器
        std::cout << "SendThreadFun =========" << std::endl;
        sleep(2);
        // TODO: 实现数据发送逻辑
    }
}

void *UpperTcpClient::RecvThreadFun(void *arg)
{
    while (1)
    {
        // 接收数据从服务器
        std::cout << "RecvThreadFun ******** " << std::endl;
        sleep(2);
        // TODO: 实现数据接收逻辑
    }
}
