#include "Halib/Math/VecI2.h"

Halib::VecI2::VecI2(int x, int y)
{
	this->x = x;
	this->y = y;
}

Halib::VecI2 Halib::VecI2::operator+(const VecI2& other) const
{
	return VecI2(x + other.x, y + other.y);
}

Halib::VecI2 Halib::VecI2::operator-(const VecI2& other) const
{
	return VecI2(x - other.x, y - other.y);
}

Halib::VecI2 Halib::VecI2::operator+=(const VecI2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}
Halib::VecI2 Halib::VecI2::operator-=(const VecI2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}
