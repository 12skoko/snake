#include"pch.h"
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<stdio.h>

int snake_x[100] = { 0 };
int snake_y[100] = { 0 };
int n = 1;
int dir = 0;
int food_x = 0;
int food_y = 0;
int flag = 0;
int death = 0;
int level;
int score = 0;

void start();
void move();
void drawsnake();
void control();
void drawfood();
void foodcoor();
int eatfood();
int hitwall();
int hitself();
void stat();
int main()
{
	printf("Plz choose the level(1-10):");
	do {
		scanf_s("%d", &level);
	} while (level < 1 || level>10);
	start();
	while (!death)
	{
		while (!_kbhit())
		{
			if (hitwall() || hitself())
			{
				death = 1;
				break;
			}
			if (flag == 0)
				foodcoor();
			move();
			drawfood();
			flag = eatfood();
			stat();
			Sleep(110 - level * 10);
		}
		control();
	}
	_getch();
}
void start()
{
	initgraph(800, 480);

	setfillcolor(0x66ccff);
	solidrectangle(600, 0, 800, 480);
	setcolor(RED);
	settextstyle(50, 0, L"华文行楷");
	setbkmode(TRANSPARENT);
	outtextxy(625, 50, L"贪吃蛇");
	settextstyle(20, 0, L"黑体");
	RECT rect = { 625, 100, 780, 470 };
	drawtext(_T("游戏说明：\n傻逼贪吃蛇"), &rect, DT_WORDBREAK);

	setfillcolor(0x9999ff);
	solidrectangle(0, 0, 600, 480);
	setbkcolor(0x9999ff);


	//🐍

}
void move()
{
	for (int i = n; i > 0; i--)
	{
		snake_x[i] = snake_x[i-1];
		snake_y[i] = snake_y[i-1];
	}
	switch (dir)
	{
	case 0:
		snake_x[0] += 10;
		break;
	case 1:
		snake_y[0] += 10;
		break;
	case 2:
		snake_x[0] -= 10;
		break;
	case 3:
		snake_y[0] -= 10;
		break;
	}
	drawsnake();
}
void drawsnake()
{
	setfillcolor(RGB(102, 204, 255));
	clearrectangle(0, 0, 600, 480);
	for (int i = 0; i < n; i++)
	{
		solidrectangle(snake_x[i], snake_y[i], snake_x[i] + 10, snake_y[i] + 10);
	}
}
void control()
{
	int a;
	a = _getch();
	switch (a)
	{
	case 77:
		if (dir != 2)
		{
			dir = 0;
			//snake_x[0] += 10;
			//score++;
			break;
		}
	case 80:
		if (dir != 3)
		{
			dir = 1;
			//snake_y[0] += 10;
			//score++;
			break;
		}
	case 75:
		if (dir != 0)
		{
			dir = 2;
			//snake_x[0] -= 10;
			//score++;
			break;
		}
	case 72:
		if (dir != 1)
		{
			dir = 3;
			//snake_y[0] -= 10;
			//score++;
			break;
		}
	}
	Sleep(10);
}
void drawfood()
{
	setfillcolor(0xff1178);
	solidroundrect(food_x, food_y, food_x + 10, food_y + 10, 10, 10);
}
void foodcoor()
{
	srand(unsigned(time(NULL)));
	food_x = rand() % 60 * 10;
	food_y = rand() % 48 * 10;
	flag = 1;
}
int eatfood()
{
	if (snake_x[0] == food_x&&snake_y[0] == food_y)
	{
		n++;
		score += 10;
		flag = 0;
		return 0;
	}
	else return 1;
}
int hitwall()
{
		if (snake_x[0] < 0 || snake_x[0]>600 || snake_y[0] < 0 || snake_y[0]>480)
			return 1;
		return 0;
}
int hitself()
{
	if (n > 1)
	{
		for (int i = 2; i <= n; i++)
		{
			if ((snake_x[0] == snake_x[i]) && (snake_y[0] == snake_y[i]))
				return 1;
		}
		return 0;
	}
	return 0;
}
void stat()
{
	TCHAR s[15];
	setfillcolor(0x66ccff);
	solidrectangle(720, 140, 780, 160);
	_stprintf_s(s, _T("您的得分：%d"), score);
	outtextxy(625, 140, s);
}