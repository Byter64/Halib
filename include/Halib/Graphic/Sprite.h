#pragma once
#include <memory>
#include "Halib/Graphic/Image.h"
#include "Halib/Math/Rectangle.h"
#include "Halib/Graphic/Camera.h"

namespace Halib
{
	/// @brief Represents a sprite. The underlying image must have one animation per row/column
	class Sprite
	{
		
		std::shared_ptr<Image> image;
		VecI2 size; //Size of the sprite. This also determines the total amount of frames in the image
		VecI2 frameCount; //Amount of frames in x and y direction
		
		float timer;
		short animationCounter; //counter for the animation frames
		
public:
		/// @brief Describes in which direction the next animation frame lies
		enum AnimationDirection
		{
			UP,
			DOWN,
			LEFT,
			RIGHT
		};
		VecI2 frameIndex; //index of the current frame
		VecI2 animationStartIndex; //Index of the first frame of the animation
		short animationFrameCount; //Number of frames in current animation
		float framesPerSecond; //Animation speed
		AnimationDirection animationDirection;
		bool isPlaying;
		VecI2 scale; //Negative values equel their absolute reciprocal. E.g. -5 == 1/5
		bool flipX;
		bool flipY;

		Sprite() = default;

		/// @brief 
		/// @param image The underlying image
		/// @param frameCount The amount of frames in x and y direction
		/// @param frameIndex The index of the active frame
		Sprite(std::shared_ptr<Image> image, VecI2 frameCount, VecI2 frameIndex = VecI2{0});
		
		/// @brief Creates an Image object and assigns it to this sprite. You can use the same image data by calling Sprite.GetImage()
		/// @param path A path to the image
		/// @param frameCount The amount of frames in x and y direction
		/// @param frameIndex The index of the active frame
		Sprite(const char* path, VecI2 frameCount, VecI2 frameIndex = VecI2{0});
		
		std::shared_ptr<Image> GetImage();
		VecI2 GetFrameSize();
		
		/// @brief 
		/// @return The offset of the active frame inside the image in pixels
		VecI2 GetFrameOffset();

		/// @brief Sets up an animation. For starting the animation set isPlaying to true
		/// @param startFrame the index of the first frame of the animation
		/// @param length The number of frames of the animation
		/// @param framesPerSecond Animation speed
		/// @param direction Into which direction the animation in the spritesheet progresses
		void SetupAnimation(VecI2 startFrame, short length, float framesPerSecond, AnimationDirection direction = RIGHT);

		//This just calls Halib::Draw(...)
		void Draw(VecI2 position);

		//This just calls Halib::Draw(...)
		void Draw(VecI2 position, const Camera &camera);

		/// @brief This calls Halib::Draw(...) AND advances its timer for animation. If timePerFrame is surpassed, the next frame will be shown
		/// @param deltaTime The time that passed
		void Draw(VecI2 position, float deltaTime);

		/// @brief This calls Halib::Draw(...) AND advances its timer for animation. If timePerFrame is surpassed, the next frame will be shown
		/// @param deltaTime The time that passed
		void Draw(VecI2 position, float deltaTime, const Camera &camera);
	};
} // namespace Halib
