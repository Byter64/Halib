#include "Halib/Graphic/Sprite.h"
#include <limits>
#include "Halib/Graphic/Render.h"

Halib::Sprite::Sprite(std::shared_ptr<Image> image, VecI2 frameCount, VecI2 frameIndex)
{
	this->image = image;
	this->frameCount = frameCount;
	this->frameIndex = frameIndex;

	size = VecI2({image->GetWidth() / frameCount.x, image->GetHeight() /frameCount.y});

	isPlaying = false;
	timer = 0;

	scale = VecI2({1, 1});
	flipX = false;
	flipY = false;
}

Halib::Sprite::Sprite(const char* path, VecI2 frameCount, VecI2 frameIndex)
{
	image = std::make_shared<Image>(path);

	this->frameCount = frameCount;
	this->frameIndex = frameIndex;

	size = VecI2({image->GetWidth() / frameCount.x, image->GetHeight() /frameCount.y});

	isPlaying = false;
	timer = 0;

	scale = VecI2({1, 1});
	flipX = false;
	flipY = false;
}

std::shared_ptr<Halib::Image> Halib::Sprite::GetImage()
{
	return image;
}

Halib::VecI2 Halib::Sprite::GetFrameSize()
{
	return size;
}

Halib::VecI2 Halib::Sprite::GetFrameOffset()
{
	return VecI2({frameIndex.x * size.x, frameIndex.y * size.y});
}
 
void Halib::Sprite::SetupAnimation(VecI2 startFrame, short length, float framesPerSecond, AnimationDirection direction)
{
	this->animationStartIndex = startFrame;
	this->animationFrameCount = length;
	this->framesPerSecond = framesPerSecond;
	this->animationDirection = direction;

	timer = 0;
	frameIndex = startFrame;
	animationCounter = 0;
}

void Halib::Sprite::ResetAnimation()
{
	timer = 0;
	frameIndex = animationStartIndex;
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

	timer += deltaTime * framesPerSecond;
	if(timer >= 1)
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
	Draw(position - camera.position);
}

void Halib::Sprite::Draw(VecI2 position, float deltaTime, const Camera &camera)
{
	Draw(position - camera.position, deltaTime);
}