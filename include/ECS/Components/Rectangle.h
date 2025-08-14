#pragma once
#include "glm/glm.hpp"
#include "ECS/Helpers/Color.h"

namespace Engine
{
	struct RectangleRenderer
	{
		glm::ivec2 size;
		Color color;
		bool isActive = true;
	};
} // namespace Engine
