#pragma once

namespace Halib
{
	void Init();

	//Desktop: true, after the window has been requested to close
	//wueHans: always false
	bool GetShouldClose();

	/// @brief 
		/// @return Time since startup in seconds
		float GetTimeSinceStartup();
} // namespace Halib
