#pragma once

namespace Engine
{
    struct Animator
    {
        bool isPlaying = true;
		short animationCounter; //counter for the animation frames
		float timer;
		float framesPerSecond; //Animation speed
        glm::ivec2 frameIndex; //index of the current frame
    };
} // Engine
