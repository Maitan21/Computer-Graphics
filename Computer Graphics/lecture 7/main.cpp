//  Created by Jho on 27/05/2019.
//  Copyright © 2019 Jho. All rights reserved.
#include    <stdlib.h>
#include    <stdio.h>
#include    <math.h>
#include    "cglec.h"

#define WIDTH 300
#define HEIGHT 300
#define PI 3.14

void DrawLines(Image img, Point p[], int n, int g)
{
	int i;
	if (n <= 1 || n % 2 != 0)     return; //2点以上の偶数でなければ描けない
	for (i = 0; i < n; i += 2)
	{
		CglDrawLine(img, p[i].x, p[i].y, p[i + 1].x, p[i + 1].y, g);
	}
}
//全点の座標をM倍に拡大する関数
void Kakudai(Point p[], int n, double M)
{
	int i;
	for (i = 0; i < n; i++)
	{
		p[i].x = (int)(p[i].x * M + 0.5);
		p[i].y = (int)(p[i].y * M + 0.5);
	}
}

//全点をx方向にax，y方向にay移動する関数
void Idou(Point p[], int n, int ax, int ay)
{
	int i;
	for (i = 0; i < n; i++)
	{
		p[i].x = p[i].x + ax;
		p[i].y = p[i].y + ay;
	}
}

void Kaiten(Point point[], int n, double q)
{ 
	double radian = q * PI/ 180;
	int i,temp;
	for (i = 0; i < n; i++) {
		temp = point[i].x;
		point[i].x = (int)(point[i].x * cos(radian) - point[i].y * sin(radian));
		point[i].y = (int)(temp * sin(radian) + point[i].y * cos(radian));
	}
}

int main(void)
{
	unsigned char data[WIDTH][HEIGHT];
	Image img = { (unsigned char*)data, WIDTH, HEIGHT };
	CglSetAll(img, 0);
	Point moji_k[] = { {0, 0}, {0, 40}, {20, 0},
					  {0, 20}, {0, 20}, {20, 30} };
	int N = 6;
	DrawLines(img, moji_k, N, 255);
	Kakudai(moji_k, N, 4);
	DrawLines(img, moji_k, N, 255);
	Kaiten(moji_k, N, 30);
	Idou(moji_k, N, 150, 100);
	DrawLines(img, moji_k, N, 255);
	CglSaveGrayBMP(img, "moji_k.bmp");
}

