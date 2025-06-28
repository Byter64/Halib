#include "Image.h"
#include "bmpread.h"
#include <cstdlib>
#include "Misc.h"

Halib::Image::Image() : width(0), height(0), data(nullptr)
{

}

Halib::Image::Image(short width, short height, std::unique_ptr<Hall::Color[]> data) : width(width), height(height), data(std::move(data))
{

}

Halib::Image::Image(const char* path)
{
	bmpread_t bmp;
	int result = bmpread(path, BMPREAD_TOP_DOWN | BMPREAD_ANY_SIZE | BMPREAD_ALPHA, &bmp);
	data = std::make_unique<Hall::Color[]>(bmp.width * bmp.height);
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
		
		Hall::Color color = 0;
		color |= (red   >> 11) & 0b11111;
		color |= (green >> 6)  & 0b11111;
		color |= (blue  >> 1)  & 0b11111;
		color |= alpha >= 128 ? 1 : 0;

		data[i] = color;
	}

	bmpread_free(&bmp);
}

void Halib::Image::Draw(VecI2 position)
{
	Misc::WaitForGPU();

	Hall::SetImage(data.get(), width);
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

Hall::Color* Halib::Image::GetData()
{
	return data.get();
}

Halib::Image::~Image()
{
	
}