#pragma once

namespace Engine
{
	namespace Input
	{	
		enum class Button : char
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
	
		/// @brief 
		/// @param controllerID Must be 0 or 1 
		/// @param button 
		/// @return True, if the button is currently held down
		bool GetButtonPressed(int controllerID, Button button);
		
		/// @brief 
		/// @param controllerID Must be 0 or 1
		/// @param button 
		/// @return True, if the button was just pressed down
		bool GetButtonDown(int controllerID, Button button);
		
		/// @brief 
		/// @param controllerID Must be 0 or 1
		/// @param button 
		/// @return True, if the button was just released
		bool GetButtonUp(int controllerID, Button button);

		/// @brief ENGINE INTERNAL
		void UpdateInputs();
	} // namespace Input
} // namespace Engine
