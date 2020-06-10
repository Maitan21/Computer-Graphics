//  Created by Jho on 19/04/2019.
//  Copyright © 2019 Jho. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "cglec.h"

int main(void)
{
	int WEIGHT, HEIGHT;
	int x1, x2,y1, y2;
	printf("画像の横向ピクセル数は？ "); scanf("%d", &WEIGHT);
	printf("画像の縦向ピクセル数は？ "); scanf("%d", &HEIGHT);
	printf("X1 = ? "); scanf("%d", &x1);
	printf("y1 = ? "); scanf("%d", &y1);
	printf("X2 = ? "); scanf("%d", &x2);
	printf("y2 = ? "); scanf("%d", &y2);

	unsigned char* data;
	data = (unsigned char*)malloc(sizeof(unsigned char) * WEIGHT * HEIGHT);
	if (data == NULL)
	{
		printf("ERROR");
		exit(0);
	}

	Image img = { (unsigned char*)data,WEIGHT,HEIGHT};
	CglSetAll(img, 0);
	int i, j;
	
	for (i = x1; i < x2; i++)
		if (i < WEIGHT)         //範囲内だけ
			for (j = y1; j < y2; j++)
                if (j < HEIGHT) //範囲内だけ
					* (data + i* HEIGHT + j) = 255;
			
	CglSaveGrayBMP(img, "Rei3-1.bmp");
	free(data);
}

