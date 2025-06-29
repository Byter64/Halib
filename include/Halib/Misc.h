#pragma once
#include "Color.h"

namespace Halib
{
	namespace Misc
	{
		void WaitForGPU();

		/// @brief Makes the image appear on screen and blocks until vSync happened
		void ShowFrame();

		void ClearFrame(Halib::Color color);

		/// @brief 
		/// @return Time since startup in seconds
		float GetTimeSinceStartup();
	}
}