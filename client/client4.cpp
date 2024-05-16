#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <queue>

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8002);                   // Change port number if needed
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change IP address if needed

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        std::cerr << "Error connecting to server" << std::endl;
        return 1;
    }

    // Set socket to non-blocking mode
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);

    std::queue<std::string> sendQueue;
    std::queue<std::string> recvQueue;

    sendQueue.push("aaaaaa");
    sendQueue.push("bbbbbb");
    sendQueue.push("cccccc");

    while (true)
    {
        printf("----loop----\n");
        // Check if there is data in sendQueue to send
        if (!sendQueue.empty())
        {
            std::string message = sendQueue.front();
            sendQueue.pop();
            printf("-----send---%lu--\n", sendQueue.size());
            send(sock, message.c_str(), message.size(), 0);
        }

        // Receive data from server
        char buffer[1024] = {0};
        int bytes_received = recv(sock, buffer, 1024, 0);
        if (bytes_received > 0)
        {
            recvQueue.push(buffer);
        }
        printf("recvQueue = %lu\n", recvQueue.size());
        // Add any additional functionality as needed

        // Sleep for a short time to prevent CPU overload
        sleep(2);
    }

    close(sock);

    return 0;
}
