#pragma once
#include <Hall/Hall.h>

namespace Halib
{
	namespace Misc
	{
		void WaitForGPU();

		/// @brief Makes the image appear on screen and blocks until vSync happened
		void ShowFrame();

		void ClearFrame(Hall::Color color);
	}
}