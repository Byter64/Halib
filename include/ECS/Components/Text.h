#pragma once
#include "glm/glm.hpp"
#include <string>
#include "ECS/Helpers/Color.h"
#include "ECS/Helpers/Font.h"

namespace Engine
{
	struct Text
	{
		enum Alignment : char
		{
			LEFT, CENTER, RIGHT,
			TOP = 0, BOTTOM = 2
		};

		Font font;
		glm::ivec2 size; //Size of the textbox
		std::string text;
		Color color;
		Alignment hAlignment = LEFT;
		Alignment vAlignment = TOP;
		float fontSize = 1; //In pixels

		bool isActive = true;
		bool useWordWrap = true;
	};
} // namespace Engine
