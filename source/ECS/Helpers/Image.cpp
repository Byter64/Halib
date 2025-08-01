#include "Engine/Helpers/Image.h"
#include "bmpread.h"
#include <cstdlib>
#include <Hall/Hall.h>

Engine::Image::Image() : width(0), height(0), data(nullptr), wasDataRequested(false), type(Type::CONST_COLOR), color(Engine::Color::BLACK)
{

}

Engine::Image::Image(short width, short height, std::unique_ptr<Engine::Color[]> data) : 
width(width), height(height), data(std::move(data)), wasDataRequested(false), type(Type::TEXTURE), color(Engine::Color::BLACK)
{

}

Engine::Image::Image(const char* path) : type(Type::TEXTURE), color(Engine::Color::BLACK)
{
	bmpread_t bmp;
	int result = bmpread(path, BMPREAD_TOP_DOWN | BMPREAD_ANY_SIZE | BMPREAD_ALPHA, &bmp);
	data = std::make_unique<Engine::Color[]>(bmp.width * bmp.height);
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
		
		Engine::Color color = 0;
		color.SetRed(red);
		color.SetGreen(green);
		color.SetBlue(blue);
		color.SetAlpha(alpha >= 192);

		data[i] = color;
	}

	bmpread_free(&bmp);
	
}

short Engine::Image::GetWidth() const
{
	return width;
}

short Engine::Image::GetHeight() const
{
	return height;
}

Engine::Color* Engine::Image::GetData()
{
#ifdef DESKTOP
	wasDataRequested = true;
#endif
	return data.get();
}

Engine::Color Engine::Image::GetCTType() const
{
	return ctType;
}

#ifdef DESKTOP
bool Engine::Image::GetWasDataRequested() const
{
	return wasDataRequested;
}
#endif