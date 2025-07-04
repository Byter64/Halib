#pragma once
#include "Halib/Graphic/Rendersystem.h"
#include "Halib/Entitysystem.h"

namespace Halib
{
	extern Rendersystem rendersystem;
	extern Entitysystem entitysystem;

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
	/// @return The time between this and the last game tick;
	float GetDeltaTime();

	/// @brief Sets the target framerate. Currently, the framerate is vsynced, so it can only be a divider of 60 Hz, other numbers will be ceiled to the next divider of 60. Values higher than 60 might not work as expected on desktop
	/// @param framerate
	void SetTargetFramerate(int framerate);

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
