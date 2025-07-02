#pragma once

namespace Halib
{
	/// @brief A 2-D vector with ints
	struct VecI2
	{
		int x;
		int y;
		
		VecI2(int x = 0, int y = 0);

		VecI2 operator+(const VecI2& other) const;
		VecI2 operator-(const VecI2& other) const;
		VecI2 operator*(const int scalar) const;
		VecI2 operator/(const int scalar) const;

		VecI2 operator+=(const VecI2& other);
		VecI2 operator-=(const VecI2& other);
		VecI2 operator*=(const int scalar);
		VecI2 operator/=(const int scalar);

		bool operator==(const VecI2& other);
		bool operator!=(const VecI2& other);
	};

}