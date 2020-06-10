//  Created by Jho on 10/05/2019.
//  Copyright © 2019 Jho. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include "cglec.h"

int d; //短辺

int LineFunc(int x, int y, int x1, int y1, int x2, int y2)
{
	return (x2 - x1) * (y - y1) - (y2 - y1) * (x - x1); //点(x,y)が正領域なら正値
}
void PaintTriangle(Image img, int x1, int y1, int x2, int y2, int x3, int y3, int g)
{
	int x, y;

	if (LineFunc(x3, y3, x1, y1, x2, y2) > 0) //パターンI(反時計回り)かパターンII(時計周り)かを 判定
	{
		for (x = d/4; x < d/4*3; x++)
			for (y =d/4; y < d/4*3; y++)
			{
				if (LineFunc(x, y, x1, y1, x2, y2) >= 0 && LineFunc(x, y, x2, y2, x3, y3) >= 0 && LineFunc(x, y, x3, y3, x1, y1) >= 0
					&& 0 < x && img.Nx > x && 0 < y && img.Ny > y)
					* (img.Data + x * img.Ny + y) = g;
			}
	}
	else
	{
		for (x = d / 4; x < d / 4 * 3; x++)
			for (y = d / 4; y < d / 4 * 3; y++)
			{
				if (LineFunc(x, y, x1, y1, x2, y2) <= 0 && LineFunc(x, y, x2, y2, x3, y3) <= 0 && LineFunc(x, y, x3, y3, x1, y1) <=0
					&& 0 < x && img.Nx > x && 0 < y && img.Ny > y)
					* (img.Data + x * img.Ny + y) = g;
			}
	}
}
int main(void)
{
	int Nx, Ny;
	printf("画像の横向ピクセル数は? "); scanf("%d", &Nx);
	printf("画像の縦向ピクセル数は? "); scanf("%d", &Ny);

	unsigned char* red = (unsigned char*)malloc(sizeof(unsigned char) * Nx * Ny);
	unsigned char* green = (unsigned char*)malloc(sizeof(unsigned char) * Nx * Ny);
	unsigned char* blue = (unsigned char*)malloc(sizeof(unsigned char) * Nx * Ny);

	if (red == NULL||green==NULL||blue==NULL)
	{
		printf("ERROR");
		exit(0);
	}

	Image img_red = { (unsigned char*)red,Nx,Ny };
	Image img_green = { (unsigned char*)green,Nx,Ny };
	Image img_blue=  { (unsigned char*)blue,Nx,Ny };

	CglSetAll(img_red, 0);
	CglSetAll(img_green, 0);
	CglSetAll(img_blue, 0);

	if (Nx > Ny) d=Ny;
	else d = Nx;
	PaintTriangle(img_red, d/4,d/4,d/4*3,d/4,d/4,d/4*3,255);
	PaintTriangle(img_green, d / 4, d / 4*3, d/ 4 * 3, d / 4, d / 4 * 3, d / 4 * 3, 255);
	PaintTriangle(img_blue, d / 4, d / 4, d / 4 * 3, d / 4, d / 2, d / 4 * 3, 255);

	CglSaveColorBMP(img_red,img_green,img_blue, "Triangles_color.bmp");
	free(red);
	free(green);
	free(blue);
}
