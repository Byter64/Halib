#pragma once
#include "glm/glm.hpp"
#include <string>

namespace Engine
{
	struct TextRenderer
	{
		glm::ivec2 position;
		glm::ivec2 size; //Size of the textbox
		std::string text;
		//Add shit from Text.h and Halib Text here
		bool useWordWrap = true;
	};
} // namespace Engine
