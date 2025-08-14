#pragma once
#include <memory>
#include <Hall/Hall.h>
#include "ECS/Helpers/Image.h"
#include "glm/vec2.hpp"

namespace Engine
{
	struct Sprite
	{
		std::shared_ptr<Image> image;
		glm::ivec2 size;
		glm::ivec2 offset = glm::ivec2(0, 0); //pixel offset of the sprite within the image
		Hall::CTType ctType = Hall::CTType::NONE;
		bool isActive = true;

		int GetLayer() const;
		void SetLayer(int layer);
	private:
		int layer = 0;
	};
} // namespace Engine
