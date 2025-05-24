#include "SnakeUdp.h"

bool SnakeUdp::StartServer() {
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    ServerSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (ServerSocket == INVALID_SOCKET) {
        std::cerr << "创建服务失败" << std::endl;
        return false;
    }

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(12345);
    ServerAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR) {
        std::cerr << "绑定失败" << std::endl;
        closesocket(ServerSocket);
        WSACleanup();
        return false;
    }

    std::cout << "UDP 服务器启动成功..." << std::endl;
    std::cout << "服务运行在：" << ServerAddr.sin_addr.s_addr << ":" << ntohs(ServerAddr.sin_port) << std::endl;
    std::cout << "========================================" << std::endl;
    return true;
}

std::string SnakeUdp::ReceiveData() {
    char buffer[BUFFER_SIZE];
    ZeroMemory(buffer, BUFFER_SIZE);

    ClientAddr;
    int ClientAddrSize = sizeof(ClientAddr);

    int BytesReceived = recvfrom(ServerSocket, buffer, BUFFER_SIZE, 0, (SOCKADDR*)&ClientAddr, &ClientAddrSize);
    if (BytesReceived > 0) {
        std::cout << "Received: " << std::string(buffer, 0, BytesReceived) << std::endl;
        return std::string(buffer, 0, BytesReceived);
    } else {
        std::cerr << "无消息" << std::endl;   // ？
    }
    return "";
}

void SnakeUdp::SendResponse(const char response[]) {
    std::cout << "Udp Sending: " << std::string(response, 0, strlen(response)) << std::endl;
    sendto(ServerSocket, response, strlen(response), 0, (SOCKADDR*)&ClientAddr, sizeof(ClientAddr));
}

void SnakeUdp::CloseServer() {
    closesocket(ServerSocket);
    WSACleanup();
}