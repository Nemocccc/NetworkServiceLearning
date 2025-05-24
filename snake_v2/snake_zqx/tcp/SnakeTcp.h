// server


#ifndef SNAKETCP_H
#define SNAKETCP_H

#include <iostream>
#include <vector>
#include <winsock2.h>
#include <windows.h>
#include <mutex>
#include <thread>
#include <cstring>
#include <fstream>

#pragma comment(lib, "ws2_32.lib")  // Link with ws2_32.lib

#define PORT 12345
#define BUFFER_SIZE 1024

class SnakeTcp {
    protected:
        SOCKET ServerSocket;
        sockaddr_in ServerAddr;
        sockaddr_in ClientAddr;
        std::vector<SOCKET> Threads;
        CRITICAL_SECTION cs;         // 线程锁
        WSADATA wsaData;

        int ClientSize;

    public:
        SOCKET ClientSocket;
        
        SnakeTcp() = default;
        ~SnakeTcp() = default;

        bool StartServer();
        std::string ReceiveData();
        void SendResponse(char response[]);
        void CloseServer();
};

#endif