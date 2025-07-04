#pragma once
#include "Halib/Graphic/Rendersystem.h"

namespace Halib
{
	extern Rendersystem rendersystem;

	enum Button
	{
		A,
		B,
		X,
		Y, 
		START,
		SELECT,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		LEFT_SHOULDER,
		RIGHT_SHOULDER
	};

	void Init();

	void Update();

	//Desktop: true, after the window has been requested to close
	//wueHans: always false
	bool GetShouldClose();

	/// @brief 
	/// @return Time since startup in seconds
	float GetTimeSinceStartup();

	/// @brief 
	/// @param controllerID Must be 0 or 1 
	/// @param button 
	/// @return True, if the button is currently held down
	bool GetButtonDown(int controllerID, Button button);
	
	/// @brief 
	/// @param controllerID Must be 0 or 1
	/// @param button 
	/// @return True, if the button was just pressed down
	bool GetButtonPressed(int controllerID, Button button);
	
	/// @brief 
	/// @param controllerID Must be 0 or 1
	/// @param button 
	/// @return True, if the button was just released
	bool GetButtonReleased(int controllerID, Button button);

} // namespace Halib
