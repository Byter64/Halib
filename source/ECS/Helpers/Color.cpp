#include "ECS/Helpers/Color.h"

const Engine::Color Engine::Color::BLACK = {0b0000000000000001};
const Engine::Color Engine::Color::TRANSPARENT = {0b0000000000000000};

Engine::Color::Color()
{
	SetRed(0);
	SetGreen(0);
	SetBlue(0);
	SetAlpha(true);
}

Engine::Color::Color(char red, char green, char blue, bool alpha)
{
	SetRed(red);
	SetGreen(green);
	SetBlue(blue);
	SetAlpha(alpha);
}

Engine::Color::Color(Hall::Color color)
{
	this->color = color;
}

void Engine::Color::SetRed(char red)
{
	color = (color & 0b0000011111111111) | (((unsigned short)red & 0b11111) << 11);
}

void Engine::Color::SetGreen(char green)
{
	color = (color & 0b1111100000111111) | (((unsigned short)green & 0b11111) << 6);
}

void Engine::Color::SetBlue(char blue)
{
	color = (color & 0b1111111111000001) | (((unsigned short)blue & 0b11111) << 1);
}

void Engine::Color::SetAlpha(bool alpha)
{
	unsigned short alphaVal = alpha ? 1 : 0;
	color = (color & 0b1111111111111110) | alphaVal;
}

char Engine::Color::GetRed()
{
	return (color >> 11) & 0b11111;
}

char Engine::Color::GetGreen()
{
	return (color >> 6) & 0b11111;
}

char Engine::Color::GetBlue()
{
	return (color >> 1) & 0b11111;
}

bool Engine::Color::GetAlpha()
{
	return color & 0b1;
}

Hall::Color Engine::Color::GetHallColor() const
{
	return color;
}