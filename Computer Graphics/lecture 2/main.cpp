#include "cglec.h"
#define WIDTH 400
#define HEIGHT 400

int main(void)
{
	unsigned char data[WIDTH][HEIGHT];

	Image img = { (unsigned char*)data, WIDTH, HEIGHT };

	CglSetAll(img, 0);
	int x, y;

	for (x = 0; x < 200; x++)
	{
		for (y = 0; y < 200; y++)
			data[x][y] = 0;
		for (y = 200; y < 400; y++)
			data[x][y] = 255;
	}
	
	for (x = 200; x < 400; x++)
	{
		for (y = 0; y < 200; y++)
			data[x][y] = 85;
		for (y = 200; y < 400; y++)
			data[x][y] = 170;
	}
	CglSaveGrayBMP(img, "PaintRect.bmp");
}