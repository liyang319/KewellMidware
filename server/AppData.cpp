// appdata.cpp
#include "AppData.h"

AppData &AppData::getInstance()
{
    static AppData instance;
    return instance;
}

void AppData::addDataToDataRecvQueue(const std::array<char, 1024> &data)
{
    std::lock_guard<std::mutex> lock(data_recv_queue_mutex);
    data_recv_queue.push(data);
}

std::array<char, 1024> AppData::getDataFromDataRecvQueue()
{
    std::lock_guard<std::mutex> lock(data_recv_queue_mutex);
    if (!data_recv_queue.empty())
    {
        std::array<char, 1024> data = data_recv_queue.front();
        data_recv_queue.pop();
        return data;
    }
    return {};
}

void AppData::addDataToDataSendQueue(const std::array<char, 1024> &data)
{
    std::lock_guard<std::mutex> lock(data_send_queue_mutex);
    data_send_queue.push(data);
}

std::array<char, 1024> AppData::getDataFromDataSendQueue()
{
    std::lock_guard<std::mutex> lock(data_send_queue_mutex);
    if (!data_send_queue.empty())
    {
        std::array<char, 1024> data = data_send_queue.front();
        data_send_queue.pop();
        return data;
    }
    return {};
}

void AppData::addDataToCtrlRecvQueue(const std::array<char, 1024> &data)
{
    std::lock_guard<std::mutex> lock(ctrl_recv_queue_mutex);
    ctrl_recv_queue.push(data);
}

std::array<char, 1024> AppData::getDataFromCtrlRecvQueue()
{
    std::lock_guard<std::mutex> lock(ctrl_recv_queue_mutex);
    if (!ctrl_recv_queue.empty())
    {
        std::array<char, 1024> data = ctrl_recv_queue.front();
        ctrl_recv_queue.pop();
        return data;
    }
    return {};
}

void AppData::addDataToCtrlSendQueue(const std::array<char, 1024> &data)
{
    std::lock_guard<std::mutex> lock(ctrl_send_queue_mutex);
    ctrl_send_queue.push(data);
}

std::array<char, 1024> AppData::getDataFromCtrlSendQueue()
{
    std::lock_guard<std::mutex> lock(ctrl_send_queue_mutex);
    if (!ctrl_send_queue.empty())
    {
        std::array<char, 1024> data = ctrl_send_queue.front();
        ctrl_send_queue.pop();
        return data;
    }
    return {};
}

AppData::AppData()
{
    // constructor
}
