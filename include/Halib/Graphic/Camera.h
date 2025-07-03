#pragma once
#include "Halib/Math/Vec.h"

namespace Halib
{
	/// @brief Represents a camera. Its origin is the top left corner of the screen
	struct Camera
	{
		VecI2 position = VecI2{0};
	};
} // namespace Halib
