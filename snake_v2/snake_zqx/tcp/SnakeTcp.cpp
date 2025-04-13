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


// void logToFile(const std::string& message) {
//     static std::ofstream logFile("debug.log", std::ios::app); // 打开日志文件，追加模式
//     if (logFile.is_open()) {
//         logFile << message << std::endl;
//     }
// }

//去除空格字符
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos)
        return ""; // 全部是空格
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}


std::string SnakeTcp::ReceiveData(){
    char buffer[BUFFER_SIZE];
    ZeroMemory (buffer, BUFFER_SIZE);

    int BytesReceived = recv(ClientSocket, buffer, BUFFER_SIZE, 0);
    
    if (BytesReceived > 0) {
        std::string receivedStr(buffer, 0, BytesReceived);
        receivedStr = trim(receivedStr); // 去掉首尾空格

        // logToFile("Received" + receivedStr);
        // logToFile((
        //     receivedStr == "right"||
        //     receivedStr == "left"||
        //     receivedStr == "up")||
        //     receivedStr == "down"
        //     ? "true" : "false");
        return receivedStr;
    } 
    // else {
    //     //logToFile("无消息.");
    // }
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