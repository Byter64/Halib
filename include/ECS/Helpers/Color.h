#pragma once
#include <Hall/Hall.h>

namespace Engine
{
	/// @brief Represents a color in the format R5G5B5A1. R, G and B values are in the range [0, 31]
	class Color
	{
		Hall::Color color;

public:
		static const Color BLACK;
		static const Color TRANSPARENT;
		static const Color WHITE;

		Color();
		Color(char red, char green, char blue, bool alpha = true);
		Color(Hall::Color color);

		/// @brief 
		/// @param red Must be in the range [0, 31]
		void SetRed(char red);

		/// @brief 
		/// @param green Must be in the range [0, 31]
		void SetGreen(char green);

		/// @brief 
		/// @param blue Must be in the range [0, 31]
		void SetBlue(char blue);

		/// @brief 
		/// @param alpha true == visible, false == transparent
		void SetAlpha(bool alpha);
		
		/// @brief 
		/// @return In the range [0, 31]
		char GetRed();
		
		/// @brief 
		/// @return In the range [0, 31]
		char GetGreen();

		/// @brief 
		/// @return In the range [0, 31]
		char GetBlue();

		/// @brief 
		/// @return true == visible, false == transparent
		bool GetAlpha();

		Hall::Color GetHallColor() const;

		bool operator==(const Color& other) const;
		bool operator!=(const Color& other) const;
	};
} // namespace Halib
