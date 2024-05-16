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

class UpperTcpServer
{
public:
    UpperTcpServer(int data_port, int ctrl_port)
    {
        this->data_port = data_port;
        this->ctrl_port = ctrl_port;
        this->data_socket = createSocket(data_port);
        this->ctrl_socket = createSocket(ctrl_port);
        this->is_running = false;
    }

    void start()
    {
        this->is_running = true;
        std::thread t(&UpperTcpServer::run, this);
        t.detach();
    }

    void stop()
    {
        this->is_running = false;
    }

private:
    int data_port;
    int ctrl_port;
    int data_socket;
    int ctrl_socket;
    std::atomic<bool> is_running;
    std::queue<std::string> data_queue;
    std::queue<std::string> ctrl_queue;
    std::mutex data_mutex;
    std::mutex ctrl_mutex;

    int createSocket(int port)
    {
        int server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket < 0)
        {
            std::cerr << "Error creating socket" << std::endl;
            return -1;
        }

        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(port);

        if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        {
            std::cerr << "Error binding socket to port " << port << std::endl;
            return -1;
        }

        if (listen(server_socket, 5) < 0)
        {
            std::cerr << "Error listening on port " << port << std::endl;
            return -1;
        }

        fcntl(server_socket, F_SETFL, O_NONBLOCK);
        return server_socket;
    }

    void handleDataConnection(int client_socket)
    {
        int index = 0;
        while (true)
        {
            sleep(1);
            printf("-----index=%d------\n", index);
            char buffer[1024];
            int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
            if (bytes_received > 0)
            {
                std::lock_guard<std::mutex> lock(data_mutex);
                data_queue.push(std::string(buffer, bytes_received));
                printf("------handleDataConnection----size-%lu-\n", data_queue.size());
            }
            else if (bytes_received == 0)
            {
                std::cerr << "Client disconnected" << std::endl;
                close(client_socket);
                break;
            }
            else if (bytes_received == -1)
            {
                if (errno == EWOULDBLOCK || errno == EAGAIN)
                {
                    // No data available, continue
                    continue;
                }
                else
                {
                    std::cerr << "Error receiving data: " << strerror(errno) << std::endl;
                    close(client_socket);
                    break;
                }
            }
        }
    }

    void handleCtrlConnection(int client_socket)
    {
        while (true)
        {
            sleep(1);
            char buffer[1024];
            int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
            if (bytes_received > 0)
            {
                std::lock_guard<std::mutex> lock(ctrl_mutex);
                ctrl_queue.push(std::string(buffer, bytes_received));
                printf("------handleCtrlConnection----size-%lu-\n", ctrl_queue.size());
            }
            else if (bytes_received == 0)
            {
                std::cerr << "Client disconnected" << std::endl;
                close(client_socket);
                break;
            }
            else if (bytes_received == -1)
            {
                if (errno == EWOULDBLOCK || errno == EAGAIN)
                {
                    // No data available, continue
                    continue;
                }
                else
                {
                    std::cerr << "Error receiving data: " << strerror(errno) << std::endl;
                    close(client_socket);
                    break;
                }
            }
        }
    }

    // void handleDataConnection(int client_socket)
    // {
    //     while (true)
    //     {
    //         char buffer[1024];
    //         int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    //         if (bytes_received > 0)
    //         {
    //             std::lock_guard<std::mutex> lock(data_mutex);
    //             data_queue.push(std::string(buffer, bytes_received));
    //         }
    //         else if (bytes_received == 0)
    //         {
    //             std::cerr << "Client disconnected" << std::endl;
    //             close(client_socket);
    //             break;
    //         }
    //         else if (bytes_received == -1)
    //         {
    //             if (errno == EWOULDBLOCK || errno == EAGAIN)
    //             {
    //                 // No data available, continue
    //                 continue;
    //             }
    //             else
    //             {
    //                 std::cerr << "Error receiving data: " << strerror(errno) << std::endl;
    //                 close(client_socket);
    //                 break;
    //             }
    //         }
    //     }
    // }

    // void handleCtrlConnection(int client_socket)
    // {
    //     while (true)
    //     {
    //         char buffer[1024];
    //         int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    //         if (bytes_received > 0)
    //         {
    //             std::lock_guard<std::mutex> lock(ctrl_mutex);
    //             ctrl_queue.push(std::string(buffer, bytes_received));
    //         }
    //         else if (bytes_received == 0)
    //         {
    //             std::cerr << "Client disconnected" << std::endl;
    //             close(client_socket);
    //             break;
    //         }
    //         else if (bytes_received == -1)
    //         {
    //             if (errno == EWOULDBLOCK || errno == EAGAIN)
    //             {
    //                 // No data available, continue
    //                 continue;
    //             }
    //             else
    //             {
    //                 std::cerr << "Error receiving data: " << strerror(errno) << std::endl;
    //                 close(client_socket);
    //                 break;
    //             }
    //         }
    //     }
    // }

    void run()
    {
        while (this->is_running)
        {
            int maxfd = std::max(data_socket, ctrl_socket) + 1;
            fd_set read_fds;
            FD_ZERO(&read_fds);
            FD_SET(data_socket, &read_fds);
            FD_SET(ctrl_socket, &read_fds);

            struct timeval timeout;
            timeout.tv_sec = 0;
            timeout.tv_usec = 1000;

            int ret = select(maxfd, &read_fds, NULL, NULL, &timeout);
            if (ret == -1)
            {
                std::cerr << "Error in select()" << std::endl;
                break;
            }

            if (FD_ISSET(data_socket, &read_fds))
            {
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                int client_socket = accept(data_socket, (struct sockaddr *)&client_addr, &client_len);
                if (client_socket < 0)
                {
                    std::cerr << "Error accepting data connection" << std::endl;
                }
                else
                {
                    std::thread t(&UpperTcpServer::handleDataConnection, this, client_socket);
                    t.detach();
                }
            }

            if (FD_ISSET(ctrl_socket, &read_fds))
            {
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                int client_socket = accept(ctrl_socket, (struct sockaddr *)&client_addr, &client_len);
                if (client_socket < 0)
                {
                    std::cerr << "Error accepting ctrl connection" << std::endl;
                }
                else
                {
                    std::thread t(&UpperTcpServer::handleCtrlConnection, this, client_socket);
                    t.detach();
                }
            }
        }
    }
};

int main()
{
    UpperTcpServer server(8001, 8002);
    server.start();

    // Stop the server after 10 seconds
    sleep(1000);
    server.stop();

    return 0;
}
