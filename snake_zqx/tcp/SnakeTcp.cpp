#include "SnakeTcp.h"

bool SnakeTcp::StartServer() {
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
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

    if (listen(ServerSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "监听启动失败" << std::endl;
        closesocket(ServerSocket);
        WSACleanup();
        return false;
    }

    ClientSize = sizeof(ClientAddr);
    ClientSocket = accept(ServerSocket, (sockaddr*)&ClientAddr, &ClientSize);
    if (ClientSocket == INVALID_SOCKET) {
        std::cerr << "连接失败" << std::endl;
        closesocket(ServerSocket);
        WSACleanup();
        return false;
    }

    std::cout << "TCP 服务器与客户端" << inet_ntoa(ClientAddr.sin_addr) << ":" << ntohs(ClientAddr.sin_port) << "连接建立成功..." << std::endl;
    std::cout << "服务运行在：" << ServerAddr.sin_addr.s_addr << ServerAddr.sin_port << std::endl;
    std::cout << "========================================" << std::endl;
    return true;
}

std::string SnakeTcp::ReceiveData(){
    char buffer[BUFFER_SIZE];
    ZeroMemory (buffer, BUFFER_SIZE);

    int BytesReceived = recv(ClientSocket, buffer, BUFFER_SIZE, 0);
    if (BytesReceived > 0) {
        std::cout << "Received: " << std::string(buffer, 0, BytesReceived) << std::endl;
        return std::string(buffer, 0, BytesReceived);
    } else {
        std::cerr << "无消息" << std::endl;   // ？
    }
    return "";
}

void SnakeTcp::SendResponse(char response[]) {
    std::cout << "Tcp Sending: " << std::string(response, 0, strlen(response)) << std::endl;
    send(ClientSocket, response, strlen(response), 0);
}

void SnakeTcp::CloseServer() {
    closesocket(ServerSocket);
    closesocket(ClientSocket);
    WSACleanup();
}