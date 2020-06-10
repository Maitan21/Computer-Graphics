//  Created by Jho on 10/0５/2019.
//  Copyright © 2019 Jho. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include "cglec.h"

int LineFunc(int x, int y, int x1, int y1, int x2, int y2)
{
	return (x2 - x1) * (y - y1) - (y2 - y1) * (x - x1); //点(x,y)が正領域なら正値
}
void PaintTriangle(Image img, int x1, int y1, int x2, int y2, int x3, int y3, int g)
{
	int x, y;
	int Min_x, Min_y, Max_x, Max_y; //クリッピング 処理
	if (x1 >= x2) {	Max_x = x1, Min_x = x2;}
	else { Max_x = x2, Min_x = x1;}
	if (x3 > Max_x)Max_x = x3;
	if (x3 < Min_x)Min_x = x3;

	if (y1 >= y2) { Max_y = y1, Min_y = y2; }
	else { Max_y = y2, Min_y = y1; }
	if (y3 > Max_y)Max_y = y3;
	if (y3 < Min_y)Min_y = y3;

	if (LineFunc(x3, y3, x1, y1, x2, y2) > 0) //パターンI(反時計回り)かパターンII(時計周り)かを 判定
	{
		for (x = Min_x; x < Max_x; x++)
			for (y = Min_y; y < Max_y; y++)
			{
				if (LineFunc(x, y, x1, y1, x2, y2) > 0 && LineFunc(x, y, x2, y2, x3, y3) > 0 && LineFunc(x, y, x3, y3, x1, y1) > 0
					&& 0 < x&& img.Nx > x && 0 < y&& img.Ny > y)
					* (img.Data + x * img.Ny + y) = g;
			}
	}
	else
	{
		for (x = Min_x; x < Max_x; x++)
			for (y = Min_y; y < Max_y; y++)
			{
				if (LineFunc(x, y, x1, y1, x2, y2) < 0 && LineFunc(x, y, x2, y2, x3, y3) < 0 && LineFunc(x, y, x3, y3, x1, y1) < 0
					&&0<x&&img.Nx>x&&0<y&&img.Ny>y)
					* (img.Data + x * img.Ny + y) = g;
			}
	}
}
int main(void)
{
	int Nx, Ny;
	printf("画像の横向ピクセル数は? "); scanf("%d", &Nx);
	printf("画像の縦向ピクセル数は? "); scanf("%d", &Ny);
	
	unsigned char* data = (unsigned char*)malloc(sizeof(unsigned char) * Nx * Ny);
	if (data == NULL)
	{
		printf("ERROR");
		exit(0);
	}

	Image img = { (unsigned char*)data,Nx,Ny};
	CglSetAll(img, 0);
	PaintTriangle(img, 0, 0, Nx - 1, Ny / 2, 3 * Nx / 4, Ny - 1, 255);
	PaintTriangle(img, Nx / 5, 4 * Ny / 5, Nx / 5 + Nx, 4 * Ny / 5, 2 * Nx / 3, -Ny / 5, 100);
	PaintTriangle(img, Nx / 2, Ny / 2, 3 * Nx / 4, 3 * Ny / 4, 3 * Nx / 4, Ny / 2, 180);
	PaintTriangle(img, Nx / 2, Ny / 3, Nx / 4, 4 * Ny / 3, -Nx / 4, Ny / 2, 60);
	CglSaveGrayBMP(img, "Triangles.bmp");
	free(data);
}
