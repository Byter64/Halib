#include "Halib/Graphic/Image.h"
#include "bmpread.h"
#include <cstdlib>
#include <Hall/Hall.h>

Halib::Image::Image() : width(0), height(0), data(nullptr), wasDataRequested(false), type(Type::CONST_COLOR), color(Halib::Color::BLACK)
{

}

Halib::Image::Image(short width, short height, std::unique_ptr<Halib::Color[]> data) : 
width(width), height(height), data(std::move(data)), wasDataRequested(false), type(Type::TEXTURE), color(Halib::Color::BLACK)
{

}

Halib::Image::Image(const char* path) : type(Type::TEXTURE), color(Halib::Color::BLACK)
{
	bmpread_t bmp;
	int result = bmpread(path, BMPREAD_TOP_DOWN | BMPREAD_ANY_SIZE | BMPREAD_ALPHA, &bmp);
	data = std::make_unique<Halib::Color[]>(bmp.width * bmp.height);
	width = bmp.width;
	height = bmp.height;
	wasDataRequested = false;
	
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

Halib::Image::Image(short width, short height, Halib::Color color) : 
width(width), height(height), color(color), type(Halib::Image::Type::CONST_COLOR), data(nullptr)
{
	
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

bool Halib::Image::IsConstColor() const
{
	return type == Type::CONST_COLOR;
}

bool Halib::Image::IsTexture() const
{
	return type == Type::TEXTURE;
}

Halib::Color Halib::Image::GetColor() const
{
	return color;
}

#ifdef DESKTOP
bool Halib::Image::GetWasDataRequested() const
{
	return wasDataRequested;
}
#endif