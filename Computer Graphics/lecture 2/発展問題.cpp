#include "cglec.h"
#define WIDTH 256
#define HEIGHT 200

int main(void)
{
	unsigned char data[WIDTH][HEIGHT];

	Image img = { (unsigned char*)data, WIDTH, HEIGHT };

	CglSetAll(img, 0);
	int x, y;

	for (y = 0; y < 200; y++)
	{
		
		for (x = 0; x < 256; x++)
			if (y < 100)
				data[x][y] = x;
			else
				data[x][y] = 255 - x;
	}
	CglSaveGrayBMP(img, "PaintRect.bmp");
}