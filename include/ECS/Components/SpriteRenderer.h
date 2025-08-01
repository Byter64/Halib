#pragma once
#include <memory>
#include "ECS/Helpers/Image.h"
#include "glm/vec2.hpp"

namespace Engine
{
	struct SpriteRenderer
	{
		std::shared_ptr<Image> image;
		glm::ivec2 scale; //Negative values equal their absolute reciprocal. E.g. -5 == 1/5
		glm::ivec2 size;
		glm::ivec2 offset; //pixel offset of the sprite within the image
		bool isActive;
		bool flipX;
		bool flipY;

	};
} // namespace Engine
