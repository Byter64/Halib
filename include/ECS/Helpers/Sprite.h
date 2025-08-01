#pragma once
#include "glm/vec2.hpp"

namespace Engine
{
	/// @brief Holds data for animating an image
	struct Sprite
	{
		glm::ivec2 size; //Size of the sprite. This also determines the total amount of frames in the image
		glm::ivec2 frameCount; //Amount of frames in x and y direction
		
		float timer;
		short animationCounter; //counter for the animation frames
		
		/// @brief Describes in which direction the next animation frame lies
		enum AnimationDirection
		{
			UP,
			DOWN,
			LEFT,
			RIGHT
		};
		glm::ivec2 frameIndex; //index of the current frame
		glm::ivec2 animationStartIndex; //Index of the first frame of the animation
		short animationFrameCount; //Number of frames in current animation
		float framesPerSecond; //Animation speed
		AnimationDirection animationDirection;
		bool isPlaying;
		glm::ivec2 scale; //Negative values equel their absolute reciprocal. E.g. -5 == 1/5
		bool flipX;
		bool flipY;


		/// @brief 
		/// @param image The underlying image
		/// @param frameCount The amount of frames in x and y direction
		/// @param frameIndex The index of the active frame
		Sprite(glm::ivec2 frameCount, glm::ivec2 frameIndex = glm::ivec2{0});

		/// @brief Sets up an animation. For starting the animation set isPlaying to true
		/// @param startFrame the index of the first frame of the animation
		/// @param length The number of frames of the animation
		/// @param framesPerSecond Animation speed
		/// @param direction Into which direction the animation in the spritesheet progresses
		void SetupAnimation(glm::ivec2 startFrame, short length, float framesPerSecond, AnimationDirection direction = RIGHT);

		//Resets the current animation to frame 0
		void ResetAnimation();
	};
} // namespace Engine
