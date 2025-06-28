#pragma once

namespace Halib
{
	namespace Misc
	{
		void WaitForGPU();

		/// @brief Makes the image appear on screen and blocks until vSync happened
		void ShowFrame();
	}
}