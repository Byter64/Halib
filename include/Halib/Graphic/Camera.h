#pragma once
#include "Halib/Math/VecI2.h"

namespace Halib
{
	/// @brief Represents a camera. Its origin is the top left corner of the screen
	struct Camera
	{
		VecI2 position = VecI2{0};
	};
} // namespace Halib
