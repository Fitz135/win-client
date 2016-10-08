#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <windows.h>
#include <unistd.h>

#define READY "READY"
#define TURN  "TURN" 
#define WIN   "WIN"
#define LOSE  "LOSE"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define BLACK 0
#define WHITE 1

#define INFO_X 36
#define INFO_Y 1
#define MESSAGE_X 36
#define MESSAGE_Y 20

char buffer[MAXBYTE] = {0};
SOCKET sock;
HANDLE hin;
HANDLE hout;
int step;

/*
 * UI���� 
 */
 
void removeScrollBar()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hout, &info);
    COORD new_size = 
    {
        info.srWindow.Right - info.srWindow.Left + 1,
        info.srWindow.Bottom - info.srWindow.Top + 1
    };
    SetConsoleScreenBufferSize(hout, new_size);
}
 
void setConsoleSize(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    MoveWindow(console, r.left, r.top, width, height, TRUE);
    removeScrollBar();
}
 
/* ������ƶ���ָ��λ�� */
void moveCursorTo(const int X, const int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(hout, coord);
}

/* ����ָ������ɫ */
void setColor(const int bg_color, const int fg_color)
{
	SetConsoleTextAttribute(hout, bg_color * 16 + fg_color);
}

void initUI()
{
	hin = GetStdHandle(STD_INPUT_HANDLE);
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	
	setConsoleSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	setColor(8, 0);
	moveCursorTo(0, 0); 
	
	printf("  1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19\n");
	printf("A�����ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש��ש���\n");
	printf(" ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("B�ǩ��贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈��\n");
	printf(" ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("C�ǩ��贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈��\n");
	printf(" ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("D�ǩ��贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈��\n");
	printf(" ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("E�ǩ��贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈��\n");
	printf(" ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("F�ǩ��贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈��\n");
	printf(" ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("G�ǩ��贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈��\n");
	printf(" ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("H�ǩ��贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈��\n");
	printf(" ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("I�ǩ��贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈��\n");
	printf(" ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("J�ǩ��贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈��\n");
	printf(" ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("K�ǩ��贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈��\n");
	printf(" ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("L�ǩ��贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈��\n");
	printf(" ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("M�ǩ��贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈��\n");
	printf(" ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("N�ǩ��贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈��\n");
	printf(" ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("O�ǩ��贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈��\n");
	printf(" ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("P�ǩ��贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈��\n");
	printf(" ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("Q�ǩ��贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈��\n");
	printf(" ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("R�ǩ��贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈�贈��\n");
	printf(" ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��\n");
	printf("S�����ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ��ߩ���\n");
	
	
	setColor(0, 7);
}

void putChessAt(int x, int y)
{
	if (step % 2 == BLACK)
	{
		setColor(8, 0);
	}
	else
	{
		setColor(8, 15);	
	}
	
	moveCursorTo(2 * x + 1, 2 * y + 1);
	printf("��");
	
	setColor(0, 7);
	++step;
}


/*
 * Socket���� 
 */
void sendTo(const char *message, SOCKET *sock)
{
	send(*sock, message, strlen(message)+sizeof(char), NULL);
}

void initSock()
{
    //��ʼ��DLL 
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    //�����׽��� 
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    //��������������� 
    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0��� 
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(23333);
    
    while (connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR)))
    {
    	moveCursorTo(INFO_X, INFO_Y);
    	printf("Connect failed, retry after 5s...\n");
    	sleep(5);
	}
	
    moveCursorTo(INFO_X, INFO_Y);
    printf("Connected");
}

void closeSock()
{
    //�ر��׽��� 
    closesocket(sock);
    
    //��ֹʹ��DLL 
    WSACleanup();
}


void ready()
{
	
}

void turn(int x, int y)
{
	putChessAt(x, y);
}

void win()
{
	moveCursorTo(INFO_X, INFO_Y);
	printf("You win!\n");
}

void lose()
{
	moveCursorTo(INFO_X, INFO_Y);
	printf("You Lose!\n");
}

void work()
{
	while (TRUE)
    {
    	memset(buffer, 0, sizeof(buffer));
    	//���շ��������ص����� 
    	recv(sock, buffer, MAXBYTE, NULL);
    	
    	//������յ������� 
    	moveCursorTo(MESSAGE_X, MESSAGE_Y);
    	printf("Message form server: %s", buffer);
    	
    	if (strstr(buffer, READY))
    	{
    		ready();
		}
		else if (strstr(buffer, TURN))
		{
			//TODO: parse
			char tmp[MAXBYTE] = {0};
			int row,  col;
			sscanf(buffer, "%s %d %d", tmp, row, col);
			turn(row, col);
		}
		else if (strstr(buffer, WIN))
		{
			win();
		}
		else if (strstr(buffer, LOSE))
		{
			lose();
		}
    	
    	int row, col;
    	scanf("%d %d", &row, &col);
    	
    	memset(buffer, 0, sizeof(buffer));
    	sprintf(buffer, "%d %d\n", row, col);
    	
    	sendTo("buffer", &sock);
	}
}

int main(){
	
	initUI();
	initSock();
	work();
	closeSock();

    return 0;
}
