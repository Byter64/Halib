#pragma once
#include "ECS/Helpers/Animation.h"

namespace Engine
{
    struct Animator
    {
        bool isPlaying;
		short animationCounter; //counter for the animation frames
		float timer;
		float framesPerSecond; //Animation speed
        glm::ivec2 frameIndex; //index of the current frame
    };
} // Engine
