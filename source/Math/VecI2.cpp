#include "Halib/Math/VecI2.h"
#include <cmath>

Halib::VecI2::VecI2(int x, int y)
{
	this->x = x;
	this->y = y;
}

float Halib::VecI2::Magnitude()
{
	return std::sqrtf(x * x + y * y);
}

Halib::VecI2 Halib::VecI2::operator+(const VecI2& other) const
{
	return VecI2(x + other.x, y + other.y);
}

Halib::VecI2 Halib::VecI2::operator-(const VecI2& other) const
{
	return VecI2(x - other.x, y - other.y);
}

Halib::VecI2 Halib::VecI2::operator*(const int scalar) const
{
	return VecI2(x * scalar, y * scalar);
}

Halib::VecI2 Halib::VecI2::operator/(const int scalar) const
{
	return VecI2(x / scalar, y / scalar);
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

Halib::VecI2 Halib::VecI2::operator*=(const int scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Halib::VecI2 Halib::VecI2::operator/=(const int scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

bool Halib::VecI2::operator==(const VecI2& other)
{
	return x == other.x && y == other.y;
}

bool Halib::VecI2::operator!=(const VecI2& other)
{
	return (*this == other);
}
