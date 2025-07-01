#include "Halib/Graphic/Sprite.h"
#include <limits>
#include "Halib/Graphic/Render.h"

Halib::Sprite::Sprite(std::shared_ptr<Image> image, VecI2 frameCount, VecI2 frameIndex)
{
	this->image = image;
	this->frameCount = frameCount;
	this->frameIndex = frameIndex;

	size = VecI2(image->GetWidth() / frameCount.x, image->GetHeight() /frameCount.y);

	isPlaying = false;
	timer = 0;
}

void Halib::Sprite::SetupAnimation(VecI2 startFrame, short length, float secondsPerFrame, AnimationDirection direction = RIGHT)
{
	this->animationStartIndex = startFrame;
	this->animationFrameCount = length;
	this->timePerFrame = secondsPerFrame;
	this->animationDirection = direction;

	timer = 0;
	frameIndex = startFrame;
	animationCounter = 0;

}


void Halib::Sprite::Draw(VecI2 position)
{
	Halib::Draw(*this, position);
}

void Halib::Sprite::Draw(VecI2 position, float deltaTime)
{
	Halib::Draw(*this, position);
	if(!isPlaying) return;

	timer += deltaTime;
	if(timer >= timePerFrame)
	{
		timer = 0;
		animationCounter++;
		if(animationCounter >= animationFrameCount)
		{
			animationCounter = 0;
			frameIndex = animationStartIndex;
		}
		else
		{
			switch (animationDirection)
			{
				case UP		: frameIndex.y--; break;
				case DOWN	: frameIndex.y++; break;
				case LEFT	: frameIndex.x--; break;
				case RIGHT	: frameIndex.x++; break;
			}
		}
	}
}

void Halib::Sprite::Draw(VecI2 position, const Camera &camera)
{
	Halib::Draw(*this, position, camera);
}