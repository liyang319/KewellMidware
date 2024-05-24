// appdata.h
#ifndef APPDATA_H
#define APPDATA_H

#include <queue>
#include <array>
#include <mutex>

#define DEFAULT_DATA_ITEM_SIZE 1024

class AppData
{

private:
    AppData();                                    // private constructor to prevent instantiation
    AppData(const AppData &) = delete;            // delete the copy constructor
    AppData &operator=(const AppData &) = delete; // delete the assignment operator

    std::queue<std::array<char, DEFAULT_DATA_ITEM_SIZE>> data_recv_queue;
    std::queue<std::array<char, DEFAULT_DATA_ITEM_SIZE>> data_send_queue;
    std::queue<std::array<char, DEFAULT_DATA_ITEM_SIZE>> ctrl_recv_queue;
    std::queue<std::array<char, DEFAULT_DATA_ITEM_SIZE>> ctrl_send_queue;

    std::mutex data_recv_queue_mutex;
    std::mutex data_send_queue_mutex;
    std::mutex ctrl_recv_queue_mutex;
    std::mutex ctrl_send_queue_mutex;

public:
    static AppData &getInstance();

    void addDataToDataRecvQueue(const std::array<char, 1024> &data);
    std::array<char, 1024> getDataFromDataRecvQueue();

    void addDataToDataSendQueue(const std::array<char, 1024> &data);
    std::array<char, 1024> getDataFromDataSendQueue();

    void addDataToCtrlRecvQueue(const std::array<char, 1024> &data);
    std::array<char, 1024> getDataFromCtrlRecvQueue();

    void addDataToCtrlSendQueue(const std::array<char, 1024> &data);
    std::array<char, 1024> getDataFromCtrlSendQueue();

    int getDataRecvQueueSize() { return data_recv_queue.size(); };
    int getDataSendQueueSize() { return data_send_queue.size(); };
    int getCtrlRecvQueueSize() { return ctrl_recv_queue.size(); };
    int getCtrlSendQueueSize() { return ctrl_send_queue.size(); };
};

#endif // APPDATA_H
