#include "Halib/Math/Path.h"
#include <cmath>
#include <iostream>
#include "Halib/System.h"

Halib::Path::Path(std::vector<Vec2> points, int width, Color color)
{
	this->points = points;
	this->drawThickness = width;
	rects = std::vector<std::shared_ptr<Rect>>();
	borders = std::vector<float>();
	length = 0;
	borders.push_back(length);
	isActive = true;

	for(int i = 1; i < points.size(); i++)
	{
		Vec2 a = points[i - 1];
		Vec2 b = points[i];

		length += Magnitude(a - b);
		borders.push_back(length);

		int x = a.x < b.x ? a.x : b.x;
		int y = a.y < b.y ? a.y : b.y;

		int width = abs(a.x - b.x);
		int height = abs(a.y - b.y);

		if(width != 0 && height != 0)
		{
			std::cout << "WARNING: " << "two adjacent points are not in a straight line" << std::endl;
			std::cout << ">> The points are: (" << a.x << ", " << a.y << ") and (" << b.x << ", " << b.y << ")" << std::endl;
		}

		x -= drawThickness / 2;
		y -= drawThickness / 2;
		width += drawThickness;
		height += drawThickness;
		auto rect = std::make_shared<Rect>(VecI2(x, y), VecI2(width, height), color);
		rects.push_back(rect);
		rendersystem.AddEntity(rect);
	}
}

float Halib::Path::GetScaledIndex(float x)
{
	int index = 0;
	while(index < borders.size() - 1 && x > borders[index])
	{
		index++;
	}
	index--;

	float scaledIndex = index;
	float distance = borders[index + 1] - borders[index];
	x -= borders[index];
	scaledIndex += x / distance;

	return scaledIndex;
}

Halib::Vec2 Halib::Path::GetPosition(float x)
{
	x = GetScaledIndex(x);

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
	return length;
}

void Halib::Path::SetActive(bool isActive)
{
	this->isActive = isActive;
	if(!isActive)
	{
		for(int i = 0; i < rects.size(); i++)
		{
			Halib::RemoveEntity(rects[i]);
		}
	}
	else
	{
		for(int i = 0; i < rects.size(); i++)
		{
			Halib::AddEntity(rects[i]);
		}
	}
}