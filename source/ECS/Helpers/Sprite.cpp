#include "ECS/Helpers/Sprite.h"
#include <limits>

Engine::Sprite::Sprite(glm::ivec2 frameCount, glm::ivec2 frameIndex)
{
	this->frameCount = frameCount;
	this->frameIndex = frameIndex;

	size = glm::ivec2({image->GetWidth() / frameCount.x, image->GetHeight() /frameCount.y});

	isPlaying = false;
	timer = 0;

	scale = glm::ivec2({1, 1});
	flipX = false;
	flipY = false;
}

Engine::Sprite::Sprite(const char* path, glm::ivec2 frameCount, glm::ivec2 frameIndex)
{
	this->frameCount = frameCount;
	this->frameIndex = frameIndex;

	size = glm::ivec2({image->GetWidth() / frameCount.x, image->GetHeight() /frameCount.y});

	isPlaying = false;
	timer = 0;

	scale = glm::ivec2({1, 1});
	flipX = false;
	flipY = false;
}
 
void Engine::Sprite::SetupAnimation(glm::ivec2 startFrame, short length, float framesPerSecond, AnimationDirection direction)
{
	this->animationStartIndex = startFrame;
	this->animationFrameCount = length;
	this->framesPerSecond = framesPerSecond;
	this->animationDirection = direction;

	timer = 0;
	frameIndex = startFrame;
	animationCounter = 0;
}

void Engine::Sprite::ResetAnimation()
{
	timer = 0;
	frameIndex = animationStartIndex;
	animationCounter = 0;
}
