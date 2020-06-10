//  Created by Jho on 19/04/2019.
//  Copyright © 2019 Jho. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "cglec.h"

int main(void)
{
	int WEIGHT, HEIGHT;
	int x1, y1;
	printf("画像の横向ピクセル数は? "); scanf("%d", &WEIGHT);
	printf("画像の縦向ピクセル数は? "); scanf("%d", &HEIGHT);
	
	unsigned char* data;
	data = (unsigned char*)malloc(sizeof(unsigned char) * WEIGHT * HEIGHT);
	if (data == NULL)
	{
		printf("ERROR");
		exit(0);
	}

	Image img = { (unsigned char*)data,WEIGHT,HEIGHT };
	CglSetAll(img, 0);
	int i, j, R;
	x1 = WEIGHT / 2 - 1;   //円の中心
	y1 = HEIGHT / 2 - 1;   //円の中心
	if (x1 >= y1)          //detect radian
		R = HEIGHT / 4;
	else
		R = WEIGHT / 4;

	for (i = 0; i < WEIGHT; i++)
		for (j = 0; j < HEIGHT; j++)
			if ((i - x1) * (i - x1) + (j - y1) * (j - y1) <= R*R)
				*(data + i * HEIGHT + j) = 255;
    
	CglSaveGrayBMP(img, "Rei3-1.bmp");
	free(data);
}
