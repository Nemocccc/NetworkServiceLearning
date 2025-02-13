#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>
#include <vector>
#include <conio.h>
#include <winsock.h>

#pragma comment(lib, "ws2_32.lib")  // Link with ws2_32.lib
#define PORT 12345
#define BUFFER_SIZE 1024
#define MAP_WIDTH 29//地图宽度
#define MAP_HEIGHT 26//地图高度
#define FOOD_WEIGHT 10//一个食物的分数  
#define DELAY 500//休息时间
#define MAX_LENGTH 10//最大蛇身长度
#define INIT_LENGTH 3//初始蛇身长度
#define WALL L'□'//墙
#define BODY L'●'//蛇身
#define FOOD L'★'//食物
#define MAX_FOOD_NUMBERS 5  // 最大食物数量


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



class SnackGame
{
private:
	SOCKET server_fd;
	std::vector<SOCKET> clients;
	CRITICAL_SECTION cs;

	std::vector<COORD> SnackBody;//蛇身	
	std::vector<COORD> foods;  // 改为食物数组
	GAME_STATUS status;
	int len;
	enum Direction dir;//蛇的方向
	int score;//总得分

public:
	SnackGame();
	~SnackGame();

	static DWORD WINAPI handle_client(LPVOID lpParam);

	//蛇身移动
	void SnackMove();
	//初始化地图
	void CreateMap();
	//初始化蛇身
	void InitSnack();
	//生成食物
	void CreateFood();
	//打印蛇身
	void PrintSnack();
	// 实时显示得分
	void PrintScore();
	//碰撞检测
	bool Collision(COORD new_head);
	//设置方向
	void SetDir(Direction new_dir) {
		dir = new_dir;
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


DWORD WINAPI SnackGame::handle_client(LPVOID lpParam) {
	SnackGame* game = (SnackGame*)lpParam;
	SOCKET client = game->clients.back();
	char buffer[BUFFER_SIZE] = { 0 };

	while (true) {
		int valread = recv(client, buffer, BUFFER_SIZE, 0);
		if (valread <= 0) break;

		if (strcmp(buffer, "reset") == 0) {
			game->InitSnack();
			game->foods.clear();
			game->CreateFood();
			game->PrintScore();
		}
		else {
			// 处理8个方向指令
			if (strcmp(buffer, "up") == 0) game->SetDir(Up);
			else if (strcmp(buffer, "down") == 0) game->SetDir(Down);
			else if (strcmp(buffer, "left") == 0) game->SetDir(Left);
			else if (strcmp(buffer, "right") == 0) game->SetDir(Right);
			else if (strcmp(buffer, "upleft") == 0) game->SetDir(UpLeft);
			else if (strcmp(buffer, "upright") == 0) game->SetDir(UpRight);
			else if (strcmp(buffer, "downleft") == 0) game->SetDir(DownLeft);
			else if (strcmp(buffer, "downright") == 0) game->SetDir(DownRight);

			game->SnackMove();
			if (game->Collision(game->SnackBody.front())) {
				game->GameEnd();
			}
		}

		// 构建包含多个食物的JSON响应
		char response[BUFFER_SIZE];
		snprintf(response, BUFFER_SIZE, "{\"game_over\":%d,\"snake\":[", game->status != OK);

		for (auto& seg : game->SnackBody) {
			char temp[50];
			snprintf(temp, 50, "{\"x\":%d,\"y\":%d},", seg.X, seg.Y);
			strcat(response, temp);
		}
		if (!game->SnackBody.empty()) response[strlen(response) - 1] = '\0';

		strcat(response, "],\"foods\":[");
		for (auto& food : game->foods) {
			char temp[50];
			snprintf(temp, 50, "{\"x\":%d,\"y\":%d},", food.X, food.Y);
			strcat(response, temp);
		}
		if (!game->foods.empty()) response[strlen(response) - 1] = '\0';
		char temp[50];
		// 添加地图信息
		strcat(response, "],\"map\":{");
		snprintf(temp, 50, "\"width\":%d,\"height\":%d,\"walls\":[", MAP_WIDTH, MAP_HEIGHT);
		strcat(response, temp);

		// 添加墙的位置
		for (int y = 0; y < MAP_HEIGHT; y++) {
			for (int x = 0; x < MAP_WIDTH; x++) {
				if ((x == 0 || x == MAP_WIDTH - 1) || (y == 0 || y == MAP_HEIGHT - 1)) {
					char temp[50];
					snprintf(temp, 50, "{\"x\":%d,\"y\":%d},", x, y);
					strcat(response, temp);
				}
			}
		}
		if (response[strlen(response) - 1] == ',') response[strlen(response) - 1] = '\0';

		strcat(response, "]},");
		snprintf(temp, 50, "\"score\":%d}", game->score);
		strcat(response, temp);

		send(client, response, strlen(response), 0);
		memset(buffer, 0, BUFFER_SIZE);
	}

	closesocket(client);
	return 0;
}



//打印蛇身
void SnackGame::PrintSnack() {
	for (int i = 0; i < len; i++) {

		SetPos(SnackBody[i].X, SnackBody[i].Y);
		wprintf(L"%lc", BODY);
	}
}

// 实时显示得分
void SnackGame::PrintScore() {
	SetPos(MAP_WIDTH + 10, 5);
	wprintf(L"得分：%d", score);
}

//生成食物
void SnackGame::CreateFood() {
	while (foods.size() < MAX_FOOD_NUMBERS) {
		COORD new_food;
		bool valid = false;
		do {
			valid = true;
			new_food.X = (rand() % (MAP_WIDTH - 4) + 2) & 0xFE;
			new_food.Y = rand() % (MAP_HEIGHT - 2) + 1;

			for (auto& seg : SnackBody) {
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
void SnackGame::InitSnack() {
	//初始蛇头位置在地图中间
	SnackBody.clear();
	len = 3;
	SnackBody.push_back({ (MAP_WIDTH / 2) & 0xFE ,MAP_HEIGHT / 2 });
	SnackBody.push_back({ (MAP_WIDTH / 2) & 0xFE - 2,MAP_HEIGHT / 2 });
	SnackBody.push_back({ (MAP_WIDTH / 2) & 0xFE - 4,MAP_HEIGHT / 2 });

	//绘制蛇身
	PrintSnack();
	//初始为正常状态
	status = OK;
	//总得分
	score = 0;
}

//移动蛇身
void SnackGame::SnackMove() {

	COORD new_head = SnackBody.front();
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
			SnackBody.insert(SnackBody.begin(), new_head);
			it = foods.erase(it);
			ate = true;
		}
		else {
			++it;
		}
	}

	if (!ate) {
		SnackBody.pop_back();
		SnackBody.insert(SnackBody.begin(), new_head);
	}
	else {
		CreateFood();
	}
	if (Collision(SnackBody.front())) {
		GameEnd();
	}
	system("cls");
	CreateMap();
	PrintSnack();
	PrintScore();
	PrintFood();

}

// 结束游戏 - 善后工作（如销毁节点）
void SnackGame::GameEnd()
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
bool SnackGame::Collision(COORD new_head) {
	// 自碰撞检测
	for (auto it = SnackBody.begin() + 1; it != SnackBody.end(); ++it) {
		if (new_head.X == it->X && new_head.Y == it->Y) {
			status = KILL_BY_SELF;
			return true;
		}
	}
	//碰墙检测
	if (new_head.X <= 2 || new_head.X >= MAP_WIDTH - 2 || new_head.Y <= 1 || new_head.Y >= MAP_HEIGHT - 1) {
		status = KTLL_BY_WALL;
		return true;
	}
	return false;
}

SnackGame::SnackGame()
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
	CreateMap();
	//初始化蛇
	InitSnack();
	//生成食物
	CreateFood();
	//显示分数
	PrintScore();

}

SnackGame::~SnackGame()
{
}

//初始化地图
void SnackGame::CreateMap() {
	//上
	SetPos(0, 0);
	int i = 0;
	for (i = 0; i < MAP_WIDTH; i++)
	{
		wprintf(L"%lc", WALL);
	}
	//下
	SetPos(0, MAP_HEIGHT);
	for (i = 0; i < MAP_WIDTH; i++)
	{
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

int main() {
	system("mode con cols=100 lines=30");
	system("title 贪吃蛇");

	setlocale(LC_ALL, "");  // 支持宽字符打印
	srand((unsigned int)time(NULL));
	SnackGame game;
	WSADATA wsaData;
	SOCKET server_fd, new_socket;
	struct sockaddr_in address;
	int addrlen = sizeof(address);

	srand(time(NULL));

	// Initialize Winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("WSAStartup failed\n");
		return 1;
	}

	// Create socket
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Socket creation error\n");
		WSACleanup();
		return 1;
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Bind the socket to the network address and port
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
		printf("Bind failed\n");
		closesocket(server_fd);
		WSACleanup();
		return 1;
	}

	// Start listening for connections
	if (listen(server_fd, 3) == SOCKET_ERROR) {
		printf("Listen failed\n");
		closesocket(server_fd);
		WSACleanup();
		return 1;
	}

	//printf("Server is running on port %d\n", PORT);

	while (1) {
		if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) == INVALID_SOCKET) {
			printf("Accept failed\n");
			closesocket(server_fd);
			WSACleanup();
			return 1;
		}

		// Create a new thread for each client
		DWORD thread_id;
		HANDLE thread_handle = CreateThread(NULL, 0, game.handle_client, &new_socket, 0, &thread_id);
		if (thread_handle == NULL) {
			printf("Error creating thread\n");
			closesocket(new_socket);
		}
		else {
			CloseHandle(thread_handle);  // We don't need to keep the handle after creating the thread
		}
	}

	closesocket(server_fd);
	WSACleanup();

	
	//while (true) {
	//	// 处理输入
	//	if (_kbhit()) {
	//		switch (_getch()) {
	//		case 'W': case 'w': game.SetDir(Up); break;
	//		case 'S': case 's': game.SetDir(Down); break;
	//		case 'A': case 'a': game.SetDir(Left); break;
	//		case 'D': case 'd': game.SetDir(Right); break;
	//		case 'Q': case 'q': game.SetDir(Direction::UpLeft); break;
	//		case 'E': case 'e': game.SetDir(Direction::UpRight); break;
	//		case 'Z': case 'z': game.SetDir(Direction::DownLeft); break;
	//		case 'X': case 'x': game.SetDir(Direction::DownRight); break;
	//		case 27: exit(0); // ESC退出
	//		}
	//	}

	//	// 游戏逻辑更新
	//	game.SnackMove();
	//	
	//	// 画面刷新
	//	Sleep(DELAY);
	//}
	
	return 0;
}