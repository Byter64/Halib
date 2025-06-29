#pragma once
#include "Graphic/Color.h"
#include "Graphic/Image.h"
#include "VecI2.h"
#include <string>
#include "Rectangle.h"
#include "Graphic/Font.h"

namespace Halib
{
	/// @brief Blocks until the GPU is not busy anymore
	void WaitForGPU();

	
	void Draw(Image &image, VecI2 position);
	void Draw(const std::string &text, VecI2 position, Font& font, Color color = Color::BLACK);
	void Draw(const Rectangle &rect, VecI2 position, Color color);
	
	/// @brief Clears the whole screen with the given color
	/// @param color 
	void Clear(Color color);

	/// @brief Updates the screen and blocks until vSync happened
	void Show();

} // namespace Halib
