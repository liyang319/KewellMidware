#include "UpperWorkerThread.h"
#include "AppData.h"
#include <string>
#include <iostream>
#include <unistd.h>

using namespace std;

UpperWorkerThread::UpperWorkerThread() : m_running(false) {}

UpperWorkerThread::~UpperWorkerThread()
{
    stop();
}

void UpperWorkerThread::start()
{
    if (!m_running)
    {
        m_running = true;
        m_thread = std::thread(&UpperWorkerThread::threadFunction, this);
    }
}

void UpperWorkerThread::stop()
{
    if (m_running)
    {
        m_running = false;
        if (m_thread.joinable())
        {
            m_thread.join();
        }
    }
}

void UpperWorkerThread::join()
{
    if (m_thread.joinable())
    {
        m_thread.join();
    }
}

void UpperWorkerThread::threadFunction()
{
    while (m_running)
    {
        // Do work here
        if (AppData::getInstance().getCtrlRecvQueueSize() > 0)
        {
            cout << "----Worker---getCtrlRecvQueueSize------" << AppData::getInstance().getCtrlRecvQueueSize() << endl;
            std::array<char, 1024> recv_data = AppData::getInstance().getDataFromDataRecvQueue();
            std::string str(recv_data.data());
            cout << "--------" << str << endl;
        }

        if (AppData::getInstance().getDataRecvQueueSize() > 0)
        {
            cout << "----workerm---getDataRecvQueueSize------" << AppData::getInstance().getDataRecvQueueSize() << endl;
            std::array<char, 1024> recv_data = AppData::getInstance().getDataFromDataRecvQueue();
            std::string str(recv_data.data());
            cout << "--------" << str << endl;
        }
        // usleep(10000);
        sleep(1);
    }
}
