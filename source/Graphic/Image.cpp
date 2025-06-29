#include "Graphic/Image.h"
#include "bmpread.h"
#include <cstdlib>
#include "Graphic/Misc.h"
#include <Hall/Hall.h>

Halib::Image::Image() : width(0), height(0), data(nullptr)
{

}

Halib::Image::Image(short width, short height, std::unique_ptr<Halib::Color[]> data) : width(width), height(height), data(std::move(data))
{

}

Halib::Image::Image(const char* path)
{
	bmpread_t bmp;
	int result = bmpread(path, BMPREAD_TOP_DOWN | BMPREAD_ANY_SIZE | BMPREAD_ALPHA, &bmp);
	data = std::make_unique<Halib::Color[]>(bmp.width * bmp.height);
	width = bmp.width;
	height = bmp.height;

	//This is stupid, but changing bmpread to directly output R5G5B5A1 did not seem so straight forward
	for(int i = 0; i < bmp.width * bmp.height; i++)
	{
		unsigned char red   = bmp.data[4 * i + 0];
		unsigned char green = bmp.data[4 * i + 1];
		unsigned char blue  = bmp.data[4 * i + 2];
		unsigned char alpha = bmp.data[4 * i + 3];

		red = red >> 3;
		green = green >> 3;
		blue = blue >> 3;
		
		Halib::Color color = 0;
		color.SetRed(red);
		color.SetGreen(green);
		color.SetBlue(blue);
		color.SetAlpha(alpha >= 192);

		data[i] = color;
	}

	bmpread_free(&bmp);
}

short Halib::Image::GetWidth() const
{
	return width;
}

short Halib::Image::GetHeight() const
{
	return height;
}

Halib::Color* Halib::Image::GetData()
{
#ifdef DESKTOP
	wasDataRequested = true;
#endif
	return data.get();
}

#ifdef DESKTOP
bool Halib::Image::GetWasDataRequested() const
{
	return wasDataRequested;
}
#endif

Halib::Image::~Image()
{
	
}