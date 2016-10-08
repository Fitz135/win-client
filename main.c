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

char buffer[MAXBYTE] = {0};
SOCKET sock;

/*
 * UI���� 
 */
 
void removeScrollBar()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);
    COORD new_size = 
    {
        info.srWindow.Right - info.srWindow.Left + 1,
        info.srWindow.Bottom - info.srWindow.Top + 1
    };
    SetConsoleScreenBufferSize(handle, new_size);
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
void moveCursorTo(HANDLE hout, const int X, const int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(hout, coord);
}

/* ����ָ������ɫ */
void setColor(HANDLE hout, const int bg_color, const int fg_color)
{
	SetConsoleTextAttribute(hout, bg_color * 16 + fg_color);
}

void initUI()
{
	setConsoleSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); 
	
	setColor(hout, 8, 0); 
	
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
	
	
	setColor(hout, 0, 7);
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
    	printf("Connect failed, retry after 5s...\n");
    	sleep(5);
	}
    
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
	
}

void win()
{
	
}

void lose()
{
	
}

void work()
{
	initUI();
	while (TRUE)
    {
    	memset(buffer, 0, sizeof(buffer));
    	//���շ��������ص����� 
    	recv(sock, buffer, MAXBYTE, NULL);
    	//������յ������� 
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
