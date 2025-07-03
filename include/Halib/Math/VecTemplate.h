#pragma once
#include <cmath>
#include <type_traits>

namespace Halib
{
	template<typename T, int dimension>
	struct Vec
	{
		union{
			T coords[dimension];

			struct
			{
				[[no_unique_address]] std::conditional_t<dimension <= 1, T, std::monostate> x;
				[[no_unique_address]] std::conditional_t<dimension <= 2, T, std::monostate> y;
				[[no_unique_address]] std::conditional_t<dimension <= 3, T, std::monostate> z;
				[[no_unique_address]] std::conditional_t<dimension <= 4, T, std::monostate> w;
				//T x;
				//T y;
				//T z;
				//T w;
			};
		};

		

		Vec() = default;

		Vec(T value)
		{
			for(int i = 0; i < dimension; i++) coords[i] = value;
		}

		Vec(T x, T y) : x(x), y(y) { }

		//template <typename std::enable_if<dimension <= 3, int>::type>
		Vec(T x, T y, T z) : x(x), y(y), z(z) { }

		//template <typename std::enable_if<dimension <= 4, int>::type>
		Vec(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) { }

		/// @brief Magnitude is always calculated as float
		/// @return 
		float Magnitude()
		{
			float sum;
			for(int i = 0; i < dimension; i++) sum += coords[i] * coords[i];

			return std::powf(sum, 1.0f/dimension);
		}

		Vec operator+(const Vec& other) const
		{
			Vec vec;
			for(int i = 0; i < dimension; i++) vec.coords[i] = coords[i] + other.coords[i];
			return vec;
		}

		Vec operator-(const Vec& other) const
		{
			Vec vec;
			for(int i = 0; i < dimension; i++) vec.coords[i] = coords[i] - other.coords[i];
			return vec;
		}

		Vec operator*(const float scalar) const
		{
			Vec vec;
			for(int i = 0; i < dimension; i++) vec.coords[i] = coords[i] * scalar;
			return vec;
		}

		Vec operator/(const float scalar) const
		{
			Vec vec;
			for(int i = 0; i < dimension; i++) vec.coords[i] = coords[i] / scalar;
			return vec;
		}

		Vec operator+=(const Vec& other)
		{
			for(int i = 0; i < dimension; i++) coords[i] += other.coords[i];
			return *this;
		}

		Vec operator-=(const Vec& other)
		{
			for(int i = 0; i < dimension; i++) coords[i] -= other.coords[i];
			return *this;
		}

		Vec operator*=(const float scalar)
		{
			for(int i = 0; i < dimension; i++) coords[i] *= scalar;
			return *this;
		}

		Vec operator/=(const float scalar)
		{
			for(int i = 0; i < dimension; i++) coords[i] /= scalar;
			return *this;
		}

		bool operator==(const Vec& other)
		{
			for(int i = 0; i < dimension; i++) if (coords[i] != other.coords[i]) return false;
			return true;
		}

		bool operator!=(const Vec& other)
		{
			return !(*this == other);
		}
	};
} // namespace Halib
