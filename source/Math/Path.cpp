#include "Halib/Math/Path.h"
#include <cmath>

Halib::Path::Path(std::vector<Vec2> points)
{
	this->points = points;
}

Halib::Vec2 Halib::Path::GetPosition(float x)
{
	x = x >= (points.size() - 1) ? (points.size() - 1) : x;
	x = x < 0 ? 0 : x;
	int indexA = x == (points.size() - 1) ? x - 1 : x;
	int indexB = indexA + 1;

	Vec2 a = points[indexA];
	Vec2 b = points[indexB];
	x -= indexA;
	float xNot = 1.0f - x;

	return a * xNot + b *x;
}

int Halib::Path::GetLength()
{
	return points.size();
}
