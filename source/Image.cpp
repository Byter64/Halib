#include "Image.h"
#include "bmpread.h"
#include <cstdlib>
#include "Misc.h"
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

void Halib::Image::Draw(VecI2 position)
{
	Misc::WaitForGPU();

#ifdef DESKTOP
	if(wasDataRequested)
	{
		Hall::UpdateRaylibTexture((Hall::Color*)data.get());
	}
#endif

	Hall::SetImage((Hall::Color*)data.get(), width);
	Hall::SetExcerpt(0, 0, width, height);
	Hall::SetScale(1, 1);
	Hall::SetFlip(false, false);
	Hall::SetColorTable(Hall::NONE);
	Hall::SetColorSource(Hall::MEMORY);
	Hall::SetShape(Hall::RECTANGLE);
	Hall::SetScreenPosition(position.x, position.y);

	Hall::Draw();
}

short Halib::Image::GetWidth()
{
	return width;
}

short Halib::Image::GetHeight()
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

Halib::Image::~Image()
{
	
}