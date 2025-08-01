#pragma once
#include <memory>
#include "ECS/Helpers/Image.h"

namespace Engine
{
	struct SpriteRenderer
	{
		bool isActive;
		std::shared_ptr<Image> image;
	};
} // namespace Engine
