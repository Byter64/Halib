#pragma once
#include "Halib/Graphic/Color.h"
#include "Halib/Graphic/Image.h"
#include <string>
#include "Halib/Math/Vec.h"
#include "Halib/Math/Rectangle.h"
#include "Halib/Graphic/Font.h"
#include "Halib/Graphic/Camera.h"
#include "Halib/Graphic/Sprite.h"
#include "Halib/Graphic/Tilemap.h"

namespace Halib
{
	/// @brief Blocks until the GPU is not busy anymore
	void WaitForGPU();

	void Draw(Image &image, VecI2 position);
	void Draw(const std::string &text, VecI2 position, Font& font, Color color = Color::BLACK);
	void Draw(const Rectangle &rect, VecI2 position, Color color);
	void Draw(Sprite &sprite, VecI2 position);
	
	void Draw(Image &image, VecI2 position, const Camera& camera);
	void Draw(const std::string &text, VecI2 position, Font& font, const Camera& camera, Color color = Color::BLACK);
	void Draw(const Rectangle &rect, VecI2 position, Color color, const Camera& camera);
	void Draw(Sprite &sprite, VecI2 position, const Camera& camera);

	void Draw(Tilemap& tilemap);
	void Draw(Tilemap& tilemap, const Camera &camera);
	
	/// @brief Clears the whole screen with the given color
	/// @param color 
	void Clear(Color color);

	/// @brief Updates the screen and blocks until vSync happened
	void Show();
} // namespace Halib
