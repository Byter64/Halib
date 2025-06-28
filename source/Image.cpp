#include "Image.h"
#include "bmpread.h"
#include <cstdlib>

Halib::Image::Image() : width(0), height(0), data(nullptr)
{

}

Halib::Image::Image(short width, short height, Hall::Color* data) : width(width), height(height), data(data)
{

}

Halib::Image::Image(const char* path)
{
	bmpread_t bmp;
	int result = bmpread(path, BMPREAD_TOP_DOWN | BMPREAD_ANY_SIZE | BMPREAD_ALPHA, &bmp);
	data = (Hall::Color*)malloc(sizeof(Hall::Color) * bmp.width * bmp.height);
	width = bmp.width;
	height = bmp.height;

	//This is stupid, but changing bmpread to directly output R5G5B5A1 did not seem so straight forward
	for(int i = 0; i < bmp.width * bmp.height; i++)
	{
		char red   = bmp.data[4 * i + 0];
		char green = bmp.data[4 * i + 1];
		char blue  = bmp.data[4 * i + 2];
		char alpha = bmp.data[4 * i + 3];
		
		Hall::Color color = 0;
		color |= (red   >> 11) & 0b11111;
		color |= (green >> 6)  & 0b11111;
		color |= (blue  >> 1)  & 0b11111;
		color |= alpha >= 0 ? 1 : 0;

		data[i] = color;
	}

	bmpread_free(&bmp);
}

Halib::Image::~Image()
{
	free(data);
}