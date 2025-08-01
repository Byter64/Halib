#pragma once
#include <memory>
#include <Hall/Hall.h>
#include "ECS/Helpers/Image.h"
#include "glm/vec2.hpp"

namespace Engine
{
	struct SpriteRenderer
	{
		std::shared_ptr<Image> image;
		glm::ivec2 size;
		glm::ivec2 offset; //pixel offset of the sprite within the image
		bool isActive;
		Hall::CTType ctType;
	};
} // namespace Engine
