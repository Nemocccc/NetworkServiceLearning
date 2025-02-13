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
#define MAP_WIDTH 29//��ͼ���
#define MAP_HEIGHT 26//��ͼ�߶�
#define FOOD_WEIGHT 10//һ��ʳ��ķ���  
#define DELAY 500//��Ϣʱ��
#define MAX_LENGTH 10//���������
#define INIT_LENGTH 3//��ʼ������
#define WALL L'��'//ǽ
#define BODY L'��'//����
#define FOOD L'��'//ʳ��
#define MAX_FOOD_NUMBERS 5  // ���ʳ������


// ���巽��
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

//�ߵ�״̬
// ������ײǽ��ײ���Լ��������˳�
enum GAME_STATUS
{
	OK,
	KTLL_BY_WALL,//ײǽ
	KILL_BY_SELF,//ײ���Լ�
	END_NORMAL//�����˳�
};

//��λ���λ��
void SetPos(short x, short y)
{
	//��ñ�׼����豸�ľ��
	HANDLE houtput = NULL;
	houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	//��λ����λ��
	COORD pos = { x,y };
	SetConsoleCursorPosition(houtput, pos);
}



class SnackGame
{
private:
	SOCKET server_fd;
	std::vector<SOCKET> clients;
	CRITICAL_SECTION cs;

	std::vector<COORD> SnackBody;//����	
	std::vector<COORD> foods;  // ��Ϊʳ������
	GAME_STATUS status;
	int len;
	enum Direction dir;//�ߵķ���
	int score;//�ܵ÷�

public:
	SnackGame();
	~SnackGame();

	static DWORD WINAPI handle_client(LPVOID lpParam);

	//�����ƶ�
	void SnackMove();
	//��ʼ����ͼ
	void CreateMap();
	//��ʼ������
	void InitSnack();
	//����ʳ��
	void CreateFood();
	//��ӡ����
	void PrintSnack();
	// ʵʱ��ʾ�÷�
	void PrintScore();
	//��ײ���
	bool Collision(COORD new_head);
	//���÷���
	void SetDir(Direction new_dir) {
		dir = new_dir;
	}
	//������Ϸ
	void GameEnd();
	//��ӡʳ��
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
			// ����8������ָ��
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

		// �����������ʳ���JSON��Ӧ
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
		// ��ӵ�ͼ��Ϣ
		strcat(response, "],\"map\":{");
		snprintf(temp, 50, "\"width\":%d,\"height\":%d,\"walls\":[", MAP_WIDTH, MAP_HEIGHT);
		strcat(response, temp);

		// ���ǽ��λ��
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



//��ӡ����
void SnackGame::PrintSnack() {
	for (int i = 0; i < len; i++) {

		SetPos(SnackBody[i].X, SnackBody[i].Y);
		wprintf(L"%lc", BODY);
	}
}

// ʵʱ��ʾ�÷�
void SnackGame::PrintScore() {
	SetPos(MAP_WIDTH + 10, 5);
	wprintf(L"�÷֣�%d", score);
}

//����ʳ��
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

//��ʼ������
void SnackGame::InitSnack() {
	//��ʼ��ͷλ���ڵ�ͼ�м�
	SnackBody.clear();
	len = 3;
	SnackBody.push_back({ (MAP_WIDTH / 2) & 0xFE ,MAP_HEIGHT / 2 });
	SnackBody.push_back({ (MAP_WIDTH / 2) & 0xFE - 2,MAP_HEIGHT / 2 });
	SnackBody.push_back({ (MAP_WIDTH / 2) & 0xFE - 4,MAP_HEIGHT / 2 });

	//��������
	PrintSnack();
	//��ʼΪ����״̬
	status = OK;
	//�ܵ÷�
	score = 0;
}

//�ƶ�����
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

	// ʳ����
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

// ������Ϸ - �ƺ����������ٽڵ㣩
void SnackGame::GameEnd()
{
	system("cls");
	SetPos(24, 12);
	switch (status)
	{
	case END_NORMAL:
		wprintf(L"%ls", L"������������Ϸ\n");
		break;
	case KTLL_BY_WALL:
		wprintf(L"%ls", L"��ײ��ǽ�ϣ���Ϸ����\n");
		break;
	case KILL_BY_SELF:
		wprintf(L"%ls", L"��ײ�����Լ�����Ϸ����\n");
		break;

	}
	exit(0);

}

// ��ײ���
bool SnackGame::Collision(COORD new_head) {
	// ����ײ���
	for (auto it = SnackBody.begin() + 1; it != SnackBody.end(); ++it) {
		if (new_head.X == it->X && new_head.Y == it->Y) {
			status = KILL_BY_SELF;
			return true;
		}
	}
	//��ǽ���
	if (new_head.X <= 2 || new_head.X >= MAP_WIDTH - 2 || new_head.Y <= 1 || new_head.Y >= MAP_HEIGHT - 1) {
		status = KTLL_BY_WALL;
		return true;
	}
	return false;
}

SnackGame::SnackGame()
{
	//�����ô��ڵĴ�С���������
	system("mode con cols=100 lines=30");
	system("title ̰����");

	HANDLE houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CurSorInfo;
	GetConsoleCursorInfo(houtput, &CurSorInfo);//��ȡ����̨�����Ϣ
	CurSorInfo.bVisible = false;//���ؿ���̨���
	SetConsoleCursorInfo(houtput, &CurSorInfo);//���ÿ���̨���״̬

	//��ʼ����ͼ
	CreateMap();
	//��ʼ����
	InitSnack();
	//����ʳ��
	CreateFood();
	//��ʾ����
	PrintScore();

}

SnackGame::~SnackGame()
{
}

//��ʼ����ͼ
void SnackGame::CreateMap() {
	//��
	SetPos(0, 0);
	int i = 0;
	for (i = 0; i < MAP_WIDTH; i++)
	{
		wprintf(L"%lc", WALL);
	}
	//��
	SetPos(0, MAP_HEIGHT);
	for (i = 0; i < MAP_WIDTH; i++)
	{
		wprintf(L"%lc", WALL);
	}
	//��
	for (i = 1; i <= MAP_HEIGHT - 1; i++)
	{
		SetPos(0, i);
		wprintf(L"%lc", WALL);
	}
	//��
	for (i = 1; i <= MAP_HEIGHT - 1; i++)
	{
		SetPos((MAP_WIDTH - 1) * 2, i);
		wprintf(L"%lc", WALL);
	}
}

int main() {
	system("mode con cols=100 lines=30");
	system("title ̰����");

	setlocale(LC_ALL, "");  // ֧�ֿ��ַ���ӡ
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
	//	// ��������
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
	//		case 27: exit(0); // ESC�˳�
	//		}
	//	}

	//	// ��Ϸ�߼�����
	//	game.SnackMove();
	//	
	//	// ����ˢ��
	//	Sleep(DELAY);
	//}
	
	return 0;
}