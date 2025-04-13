// server


#ifndef SNAKEUDP_H
#define SNAKEUDP_H

#include <iostream>
#include <vector>
#include <winsock2.h>
#include <windows.h>
#include <mutex>
#include <thread>
#include <cstring>

#pragma comment(lib, "ws2_32.lib")  // Link with ws2_32.lib

#define PORT 12345
#define BUFFER_SIZE 1024

class SnakeUdp {
    protected:
        SOCKET ServerSocket;
        sockaddr_in ServerAddr;
        std::vector<SOCKET> Threads;
        CRITICAL_SECTION cs;         // 线程锁
        WSADATA wsaData;

        int ClientSize;

    public:
        sockaddr_in ClientAddr;
        SOCKET ClientSocket;
        
        SnakeUdp() = default;
        ~SnakeUdp() = default;

        bool StartServer();
        std::string ReceiveData();
        void SendResponse(const char response[]);
        void CloseServer();
};

#endif