#pragma once
#include "Halib/Math/Vec.h"
#include "Halib/Graphic/Rect.h"
#include <vector>

namespace Halib
{
	/// @brief A path consists of multiple points, connected by straight lines
	class Path 
	{
		std::vector<Vec2> points;
		std::vector<std::shared_ptr<Rect>> rects;
		int drawThickness;

public:
		Path(std::vector<Vec2> points, int width, Color color);


		/// @brief 
		/// @param x X spans between 0 and GetLength(), where 0 is equal to the first point and GetLength() to the last point
		/// @return The 2D-position that corresponds to x
		Vec2 GetPosition(float x);
		
		/// @brief 
		/// @return The length of the path 
		int GetLength();
	};
} // namespace Halib
