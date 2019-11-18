#include"pch.h"
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include <mmsystem.h>//多媒体
#pragma comment(lib,"winmm.lib")

struct coor
{
	int x;
	int y;
};
typedef enum ch
{
	up = 72,
    down = 80,
    left = 75,
    right = 77
}CH;
struct snake 
{
	struct coor scr[100];
	int n=10;
	CH ch;
}snake;
struct food
{
	struct  coor fcr;
	int flag;
}food;
//using namespace std;
void beforestart();
void drawsnake();
void move();
void control();
void foodcoor();
void drawfood();
int eatfood();
int main()
{
	beforestart();
	int flag = 0;
	while (1) 
	{
		while(!_kbhit())
		{
			if (flag == 0)
			{
				foodcoor();
			}
			move();
			drawfood();
			flag = eatfood();
		    Sleep(50); 
		}
		control();
	}
	_getch();
}

void beforestart()
{
	initgraph(800, 480);
	setbkcolor(0x9999ff);
 
	setfillcolor(0x66ccff);		
	HRGN rgn = CreateRectRgn(600, 0, 800, 480);
	setcliprgn(rgn);
	DeleteObject(rgn);
    solidrectangle(600, 0, 800, 480);	
	setcolor(RED);
	settextstyle(50, 0, L"华文行楷");
	setbkmode(TRANSPARENT);
	outtextxy(625, 50, L"贪吃蛇");
	settextstyle(20, 0, L"黑体");
	RECT rect = { 625, 100, 780, 470 };
	drawtext(_T("游戏说明：\n傻逼贪吃蛇"),&rect,DT_WORDBREAK);
	
	HRGN rgn1 = CreateRectRgn(0, 0, 600, 480);
	setcliprgn(rgn1);
	DeleteObject(rgn1);

	setfillcolor(0x9999ff);
	solidrectangle(0, 0, 600, 480);
	
	
	mciSendString(L"open YO.mp3 alias YO", 0, 0, 0);
	mciSendString(L"play YO repeat", 0, 0, 0);

	//🐍
	setfillcolor(RGB(102, 204, 255));
	setcolor(RGB(102, 204, 255));
	fillrectangle(0, 0, 10, 10);
	snake.scr[0].x = 0;
	snake.scr[0].y = 0;
	snake.ch = right;

	food.flag = 0;
}

void move()
{
	for (int i = snake.n; i >0; i--)
	{
		snake.scr[i].x = snake.scr[i-1].x;
		snake.scr[i].y = snake.scr[i-1].y;
	}
	switch(snake.ch)
	{
	case up:
		snake.scr[0].y -= 10;
		break;
	case down:
		snake.scr[0].y += 10;
		break;
	case right:
		snake.scr[0].x += 10;
		break;
	case left:
		snake.scr[0].x -= 10;
		break;
	}
	drawsnake();
}

void drawsnake()
{
	setfillcolor(RGB(102, 204, 255));
	setcolor(RGB(102, 204, 255));
	clearrectangle(0, 0, 600, 480);
	for (int i = 0; i < snake.n; i++)
	{
		fillrectangle(snake.scr[i].x, snake.scr[i].y, snake.scr[i].x + 10, snake.scr[i].y + 10);
	}
}

void control()
{
	int input;
	input = _getch();
	switch(input)
	{
	case up:
		if (snake.ch != down)
			snake.ch = up;
		break;
	case down:
		if (snake.ch != up)
			snake.ch = down;
		break;
	case left:
		if (snake.ch != right)
			snake.ch = left;
		break;
	case right:
		if (snake.ch != left)
			snake.ch = right;
		break;
	}
}

void foodcoor()
{
	srand(unsigned(time(NULL)));
	food.fcr.x = rand() % 60 * 10;
	food.fcr.y = rand() % 48 * 10;

	food.flag = 1;
}

void drawfood()
{
	setfillcolor(0xff1178);
	solidroundrect(food.fcr.x, food.fcr.y, food.fcr.x + 10, food.fcr.y + 10, 10, 10);
}

int eatfood()
{
	if (snake.scr[0].x == food.fcr.x&&snake.scr[0].y == food.fcr.y)
	{
		snake.n++;
		food.flag = 0;
		return 0;
	}
	else return 1;
}