#include "Halib/Math/Vec2.h"

Halib::Vec2::Vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Halib::Vec2 Halib::Vec2::operator+(const Vec2& other) const
{
	return Vec2(x + other.x, y + other.y);
}

Halib::Vec2 Halib::Vec2::operator-(const Vec2& other) const
{
	return Vec2(x - other.x, y - other.y);
}

Halib::Vec2 Halib::Vec2::operator*(const float scalar) const
{
	return Vec2(x * scalar, y * scalar);
}

Halib::Vec2 Halib::Vec2::operator/(const float scalar) const
{
	return Vec2(x / scalar, y / scalar);
}


Halib::Vec2 Halib::Vec2::operator+=(const Vec2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}
Halib::Vec2 Halib::Vec2::operator-=(const Vec2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Halib::Vec2 Halib::Vec2::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Halib::Vec2 Halib::Vec2::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}
