#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/vec2.hpp"
#include <vector>
#include <map>

namespace Engine
{
    struct Animation
    {
		/// @brief Describes in which direction the next animation frame lies
		enum AnimationDirection
		{
			UP,
			DOWN,
			LEFT,
			RIGHT
		};

        glm::ivec2 frameCount; //Amount of frames in x and y direction
		glm::ivec2 animationStartIndex; //Index of the first frame of the animation
		
		short animationFrameCount; //Number of frames in this animation
		AnimationDirection animationDirection;
    };

} // Engine
