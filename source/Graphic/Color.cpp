#include "Graphic/Color.h"

Halib::Color::Color()
{
	SetRed(0);
	SetGreen(0);
	SetBlue(0);
	SetAlpha(true);
}

Halib::Color::Color(char red, char green, char blue, bool alpha)
{
	SetRed(red);
	SetGreen(green);
	SetBlue(blue);
	SetAlpha(alpha);
}

Halib::Color::Color(Hall::Color color)
{
	this->color = color;
}

void Halib::Color::SetRed(char red)
{
	color = (color & 0b0000011111111111) | (((unsigned short)red & 0b11111) << 11);
}

void Halib::Color::SetGreen(char green)
{
	color = (color & 0b1111100000111111) | (((unsigned short)green & 0b11111) << 6);
}

void Halib::Color::SetBlue(char blue)
{
	color = (color & 0b1111111111000001) | (((unsigned short)blue & 0b11111) << 1);
}

void Halib::Color::SetAlpha(bool alpha)
{
	unsigned short alphaVal = alpha ? 1 : 0;
	color = (color & 0b1111111111111110) | alphaVal;
}

char Halib::Color::GetRed()
{
	return (color >> 11) & 0b11111;
}

char Halib::Color::GetGreen()
{
	return (color >> 6) & 0b11111;
}

char Halib::Color::GetBlue()
{
	return (color >> 1) & 0b11111;
}

bool Halib::Color::GetAlpha()
{
	return color & 0b1;
}
