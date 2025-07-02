#pragma once
#include "Halib/Math/VecI2.h"

namespace Halib
{
	/// @brief A 2-D vector
	struct Vec2
	{
		float x;
		float y;
		
		Vec2(float x = 0, float y = 0);
		Vec2(const VecI2 &vec);

		Vec2 operator+(const Vec2& other) const;
		Vec2 operator-(const Vec2& other) const;
		Vec2 operator*(const float scalar) const;
		Vec2 operator/(const float scalar) const;

		Vec2 operator+=(const Vec2& other);
		Vec2 operator-=(const Vec2& other);
		Vec2 operator*=(const float scalar);
		Vec2 operator/=(const float scalar);

		bool operator==(const Vec2& other);
		bool operator!=(const Vec2& other);
	};

}