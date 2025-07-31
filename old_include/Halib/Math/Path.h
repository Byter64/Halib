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
		std::vector<float> borders; //contains the 1D beginning of each new point
		int drawThickness;
		float length;
		bool isActive;

		//Returns the index of the point that is underneath x
		float GetScaledIndex(float x);
public:
		Path() = default;
		Path(std::vector<Vec2> points, int width, Color color);


		/// @brief 
		/// @param x X spans between 0 and GetLength(), where 0 is equal to the first point and GetLength() to the last point
		/// @return The 2D-position that corresponds to x
		Vec2 GetPosition(float x);
		
		/// @brief 
		/// @return The length of the path 
		int GetLength();

		/// @brief toggles if the path is drawn or not
		/// @param isActive 
		void SetActive(bool isActive);
	};
} // namespace Halib
