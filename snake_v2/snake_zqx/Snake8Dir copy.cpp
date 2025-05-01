#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>
#include <vector>
#include <conio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>

#include "tcp/SnakeTcp.h"
#include "udp/SnakeUdp.h"

#pragma comment(lib, "ws2_32.lib")  // Link with ws2_32.lib

#define BUFFER_SIZE 1024
#define MAP_WIDTH 5//地图宽度
#define MAP_HEIGHT 5//地图高度
#define FOOD_WEIGHT 10//一个食物的分数  
#define DELAY 500//休息时间
#define MAX_LENGTH 6//最大蛇身长度
#define INIT_LENGTH 3//初始蛇身长度
#define WALL L'\u25A1'//墙
#define BODY L'\u25CF'//蛇身
#define FOOD L'\u2605'//食物
#define MAX_FOOD_NUMBERS 1  // 最大食物数量



// 定义方向
enum Direction {
    Up,
    Down,
    Left,
    Right,
    UpLeft,
    UpRight,
    DownLeft,
    DownRight
};

//蛇的状态
// 正常、撞墙、撞到自己、正常退出
enum GAME_STATUS
{
    OK,
    KTLL_BY_WALL,//撞墙
    KILL_BY_SELF,//撞到自己
    END_NORMAL//正常退出
};

//定位光标位置
void SetPos(short x, short y)
{
    //获得标准输出设备的句柄
    HANDLE houtput = NULL;
    houtput = GetStdHandle(STD_OUTPUT_HANDLE);
    //定位光标的位置
    COORD pos = { x,y };
    SetConsoleCursorPosition(houtput, pos);
}

class SnakeGame
{
private:
    SOCKET server_fd;
    std::vector<SOCKET> clients;
    CRITICAL_SECTION cs;

    std::vector<COORD> SnakeBody;//蛇身    
    std::vector<COORD> foods;  // 改为食物数组
    GAME_STATUS status;
    int len;
    enum Direction dir;//蛇的方向
    int score;//总得分

public:

    SnakeGame();
    ~SnakeGame();

    std::string dirToString(Direction dir) {
    switch (dir) {
    case Up: return "Up";
    case Down: return "Down";
    case Left: return "Left";
    case Right: return "Right";
    case UpLeft: return "UpLeft";
    case UpRight: return "UpRight";
    case DownLeft: return "DownLeft";
    case DownRight: return "DownRight";
    default: return "Unknown";
    }
    };
    
    // void logToFile1(const std::string& message) {
    // static std::ofstream logFile("game.log", std::ios::app); // 打开日志文件，追加模式
    // if (logFile.is_open()) {
    //     logFile << message << std::endl;
    // }
    // };
    friend DWORD WINAPI handle_client(LPVOID lpParam);
    //蛇身移动
    void SnakeMove();
    //初始化地图
    //void CreateMap();
    //初始化蛇身
    void InitSnake();
    //生成食物
    void CreateFood();
    //打印蛇身
    void PrintSnake();
    // 实时显示得分
    void PrintScore();
    //碰撞检测
    bool Collision(COORD new_head);
    //设置方向
    void SetDir(Direction new_dir) {
        dir = new_dir;
        //logToFile1(dirToString(dir));
    }
    //结束游戏
    void GameEnd();
    //打印食物
    void PrintFood() {
        for (auto& food : foods) {
            SetPos(food.X, food.Y);
            wprintf(L"%lc", FOOD);
        }
    }
};


std::string proto;





DWORD WINAPI handle_client(LPVOID lpParam) {

    SnakeGame game;
    SnakeTcp* tcp = (SnakeTcp*)lpParam;
    SnakeUdp* udp = (SnakeUdp*)lpParam;
    SOCKET client;

    client = (tcp->ClientSocket ? proto == "tcp" : udp->ClientSocket);

    std::string buffer;

    while (true) {
        buffer = (proto == "tcp") ? tcp->ReceiveData() : udp->ReceiveData();
        // 移除字符串中的空格
        //buffer.erase(std::remove(buffer.begin(), buffer.end(), ' '), buffer.end());
        Sleep(500);
        if (buffer == "reset") {
            game.InitSnake();
            game.foods.clear();
            game.CreateFood();
            game.PrintScore();
        }
        else {
            // 处理8个方向指令
            if (buffer == (std::string)"up") {
                // game.logToFile1(game.dirToString(game.dir));
                game.SetDir(Up);
            } else if (buffer == (std::string)"down") {
                // game.logToFile1(game.dirToString(game.dir));
                game.SetDir(Down);
            } else if (buffer == (std::string)"left") {
                // game.logToFile1(game.dirToString(game.dir));
                game.SetDir(Left);
            } else if (buffer == (std::string)"right") {
                // game.logToFile1(game.dirToString(game.dir));
                game.SetDir(Right);
            } else if (buffer == (std::string)"upleft") {
                // game.logToFile1(game.dirToString(game.dir));
                game.SetDir(UpLeft);
            } else if (buffer == (std::string)"upright") {
                // game.logToFile1(game.dirToString(game.dir));
                game.SetDir(UpRight);
            } else if (buffer == (std::string)"downleft") {
                // game.logToFile1(game.dirToString(game.dir));
                game.SetDir(DownLeft);
            } else if (buffer == (std::string)"downright") {
                // game.logToFile1(game.dirToString(game.dir));
                game.SetDir(DownRight);
            }
            
            game.SnakeMove();
        }

        // 构建包含多个食物的JSON响应
        char response[BUFFER_SIZE];
        snprintf(response, BUFFER_SIZE, "{\"game_over\":%d,\"snake\":[", game.status != OK);

        for (auto& seg : game.SnakeBody) {
            char temp[50];
            snprintf(temp, 50, "{\"x\":%d,\"y\":%d},", seg.X, seg.Y);
            strcat(response, temp);
        }
        if (!game.SnakeBody.empty()) response[strlen(response) - 1] = '\0';

        strcat(response, "],\"foods\":[");
        for (auto& food : game.foods) {
            char temp[50];
            snprintf(temp, 50, "{\"x\":%d,\"y\":%d},", food.X, food.Y);
            strcat(response, temp);
        }
        if (!game.foods.empty()) response[strlen(response) - 1] = '\0';
        char temp[50];
        // 添加地图信息
        strcat(response, "],\"map\":{");
        snprintf(temp, 50, "\"width\":%d,\"height\":%d,\"walls\":[", MAP_WIDTH, MAP_HEIGHT);
        strcat(response, temp);

        // 添加墙的位置
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x <= (MAP_WIDTH - 1) * 2; x++) {
                if ((x == 0 || x == (MAP_WIDTH - 1) * 2) || (y == 0 || y == MAP_HEIGHT - 1)) {
                    char temp[50];
                    snprintf(temp, 50, "{\"x\":%d,\"y\":%d},", x, y);
                    strcat(response, temp);
                }
            }
        }
        if (response[strlen(response) - 1] == ',') response[strlen(response) - 1] = '\0';

        strcat(response, "]},");
        snprintf(temp, 50, "\"score\":%d}", game.score);
        strcat(response, temp);
        strcat(response, "\n");

        if (proto == "tcp") {
            tcp->SendResponse(response);
        }
        else {
            udp->SendResponse(response);
        }
        buffer.clear();

        if (game.Collision(game.SnakeBody.front())) {
            game.GameEnd();
        }
    }


    if (proto == "tcp") {
        std::cout << "关闭 tcp" << std::endl;
        tcp->CloseServer();
        delete tcp;
    }
    else {
        std::cout << "关闭 udp" << std::endl;
        udp->CloseServer();
        delete udp;
    }
    return 0;
}


//打印蛇身
void SnakeGame::PrintSnake() {
    for (int i = 0; i < len; i++) {
        SetPos(SnakeBody[i].X, SnakeBody[i].Y);
        wprintf(L"%lc", BODY);
    }
}

// 实时显示得分
void SnakeGame::PrintScore() {
    SetPos(MAP_WIDTH + 10, 5);
    printf("得分：%d", score);
}

//生成食物
void SnakeGame::CreateFood() {
    while (foods.size() < MAX_FOOD_NUMBERS) {
        COORD new_food;
        bool valid = false;
        do {
            valid = true;
            new_food.X = (rand() % (MAP_WIDTH - 4) + 2) & 0xFE;
            new_food.Y = rand() % (MAP_HEIGHT - 2) + 1;

            for (auto& seg : SnakeBody) {
                if (seg.X == new_food.X && seg.Y == new_food.Y) {
                    valid = false;
                    break;
                }
            }

            for (auto& existing : foods) {
                if (existing.X == new_food.X && existing.Y == new_food.Y) {
                    valid = false;
                    break;
                }
            }
        } while (!valid);

        foods.push_back(new_food);
    }
}

//初始化蛇身
void SnakeGame::InitSnake() {
    //初始蛇头位置在地图中间
    SnakeBody.clear();
    len = 1;
    auto headx = (MAP_WIDTH & 0xFE) - 2;  // 修正运算符优先级问题
    SHORT startY = static_cast<SHORT>(MAP_HEIGHT / 2);

    // 显式构造COORD对象并转换类型
    SnakeBody.push_back(COORD{ static_cast<SHORT>(headx), startY });
    
    
    //绘制蛇身
    PrintSnake();
    //初始为正常状态
    status = OK;
    //总得分
    score = 0;
}


//移动蛇身
void SnakeGame::SnakeMove() {
    COORD new_head = SnakeBody.front();
    switch (dir) {
    case Up: new_head.Y--; break;
    case Down: new_head.Y++; break;
    case Left: new_head.X -= 2; break;
    case Right: new_head.X += 2; break;
    case UpLeft: new_head.X -= 2; new_head.Y--; break;
    case UpRight: new_head.X += 2; new_head.Y--; break;
    case DownLeft: new_head.X -= 2; new_head.Y++; break;
    case DownRight: new_head.X += 2; new_head.Y++; break;
    }

    // 食物检测
    bool ate = false;
    for (auto it = foods.begin(); it != foods.end();) {
        if (new_head.X == it->X && new_head.Y == it->Y) {
            len++;
            score += FOOD_WEIGHT;
            SnakeBody.insert(SnakeBody.begin(), new_head);
            it = foods.erase(it);
            ate = true;
        }
        else {
            ++it;
        }
    }

    if (!ate) {
        SnakeBody.pop_back();
        SnakeBody.insert(SnakeBody.begin(), new_head);
    }
    else {
        CreateFood();
    }
    //在通信中碰撞检测被移动到handle_client了
    // if (Collision(SnakeBody.front())) {
    //     GameEnd();
    // }
    system("cls");
    //CreateMap();
    PrintSnake();
    PrintScore();
    PrintFood();
}

// 结束游戏 - 善后工作（如销毁节点）
void SnakeGame::GameEnd()
{
    system("cls");
    SetPos(24, 12);
    switch (status)
    {
    case END_NORMAL:
        wprintf(L"%ls", L"您主动结束游戏\n");
        break;
    case KTLL_BY_WALL:
        wprintf(L"%ls", L"您撞到墙上，游戏结束\n");
        break;
    case KILL_BY_SELF:
        wprintf(L"%ls", L"您撞到了自己，游戏结束\n");
        break;

    }
    exit(0);
}

// 碰撞检测
bool SnakeGame::Collision(COORD new_head) {
    // 自碰撞检测
    for (auto it = SnakeBody.begin() + 1; it != SnakeBody.end(); ++it) {
        if (new_head.X == it->X && new_head.Y == it->Y) {
            status = KILL_BY_SELF;
            return true;
        }
    }
    //碰墙检测
    if (new_head.X < 0 || new_head.X >= MAP_WIDTH * 2 || new_head.Y < 0 || new_head.Y >= MAP_HEIGHT) {
        status = KTLL_BY_WALL;
        return true;
    }
    return false;
}

SnakeGame::SnakeGame()
{
    //先设置窗口的大小，光标隐藏
    system("mode con cols=100 lines=30");
    system("title 贪吃蛇");

    HANDLE houtput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CurSorInfo;
    GetConsoleCursorInfo(houtput, &CurSorInfo);//获取控制台光标信息
    CurSorInfo.bVisible = false;//隐藏控制台光标
    SetConsoleCursorInfo(houtput, &CurSorInfo);//设置控制台光标状态

    //初始化地图
    //CreateMap();
    //初始化蛇
    InitSnake();
    //生成食物
    CreateFood();
    //显示分数
    PrintScore();
}

SnakeGame::~SnakeGame()
{
}

// 初始化地图
/*

void SnakeGame::CreateMap() {
    //上
    SetPos(0, 0);
    int i = 0;
    for (i = 0; i < MAP_WIDTH; i++)
    {
        wprintf(L"%lc", WALL);
    }
    //下
    SetPos(0, MAP_HEIGHT);
     for (i = 0; i < MAP_WIDTH*2-1; i++)
    {
     SetPos(i, MAP_HEIGHT);
     wprintf(L"%lc", WALL);
    }
    //左
    for (i = 1; i <= MAP_HEIGHT - 1; i++)
    {
        SetPos(0, i);
        wprintf(L"%lc", WALL);
    }
    //右
    for (i = 1; i <= MAP_HEIGHT - 1; i++)
    {
        SetPos((MAP_WIDTH - 1) * 2, i);
        wprintf(L"%lc", WALL);
    }
}
*/

int main(int argc, char* argv[]) {
    
    system("mode con cols=100 lines=30");
    system("title 贪吃蛇");

    setlocale(LC_ALL, "");  // 支持宽字符打印
    srand((unsigned int)time(NULL));

    if (argc > 1 && strcmp(argv[1], "udp") == 0) {
        proto = "udp";
        // 使用 UDP 服务器
        while (true) {
            SnakeUdp* udp = new SnakeUdp();
            if (!udp->StartServer()) {
                delete udp;
                continue;
            }

            // Create a new thread for each client
            DWORD thread_id;
            HANDLE thread_handle = CreateThread(NULL, 0, handle_client, udp, 0, &thread_id);
            if (thread_handle == NULL) {
                printf("Error creating thread\n");
                udp->CloseServer();
                delete udp;
            }
            else {
                CloseHandle(thread_handle);  // We don't need to keep the handle after creating the thread
            }
        }
    }
    else {
        proto = "tcp";
        // 使用 TCP 服务器
        while (true) {
            SnakeTcp* tcp = new SnakeTcp();
            if (!tcp->StartServer()) {
                delete tcp;
                continue;
            }

            // Create a new thread for each client
            DWORD thread_id;
            HANDLE thread_handle = CreateThread(NULL, 0, handle_client, tcp, 0, &thread_id);
            if (thread_handle == NULL) {
                printf("Error creating thread\n");
                tcp->CloseServer();
                delete tcp;
            }
            else {
                CloseHandle(thread_handle);  // We don't need to keep the handle after creating the thread
            }
        }
    }

    // //键盘测试游戏逻辑
    
    //  system("mode con cols=100 lines=30");
    // system("title 贪吃蛇");

    // setlocale(LC_ALL, "");  // 支持宽字符打印
    // srand((unsigned int)time(NULL));
    // SnakeGame game;

    // while (true) {
    //     // 处理输入
    //     if (_kbhit()) {
    //         switch (_getch()) {
    //         case 'W': case 'w': game.SetDir(Up); break;
    //         case 'S': case 's': game.SetDir(Down); break;
    //         case 'A': case 'a': game.SetDir(Left); break;
    //         case 'D': case 'd': game.SetDir(Right); break;
    //         case 'Q': case 'q': game.SetDir(Direction::UpLeft); break;
    //         case 'E': case 'e': game.SetDir(Direction::UpRight); break;
    //         case 'Z': case 'z': game.SetDir(Direction::DownLeft); break;
    //         case 'X': case 'x': game.SetDir(Direction::DownRight); break;
    //         case 27: exit(0); // ESC退出
    //         }

    //         // 游戏逻辑更新
    //         game.SnakeMove();
    //     }

    //     // 画面刷新
    //     Sleep(100); // 减小延迟，避免程序占用过多CPU资源
    // }
    



    return 0;
}