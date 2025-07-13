#pragma once
#include "Halib/Graphic/Rendersystem.h"
#include "Halib/Audio/Audiosystem.h"
#include "Halib/Entitysystem.h"
#include "Halib/Entity.h"

namespace Halib
{
	extern Rendersystem rendersystem;
	extern Entitysystem entitysystem;
	extern Audiosystem audiosystem;
	
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

	/// @brief Updates the whole system. Consider using this instead of the updating the underlying systems on your one
	void Update();

	/// @brief This is a very ugly function. Use draw calls to your liking to draw the UI
	void DrawUI();

	void AddEntity(std::shared_ptr<Entity> entity);
	void RemoveEntity(std::shared_ptr<Entity> entity);
	void RemoveEntity(Entity* entity);

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

	VecI2 GetScreenSize();

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
