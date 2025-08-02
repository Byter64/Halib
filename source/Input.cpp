#include "Input.h"
#include "Engine.h"


namespace Engine
{
	namespace Input
	{
		static const int CONTROLLER_COUNT = 2;
		static Hall::ControllerState oldState[CONTROLLER_COUNT];
		static Hall::ControllerState newState[CONTROLLER_COUNT];
		static Hall::ControllerState pressedState[CONTROLLER_COUNT];
		static Hall::ControllerState releasedState[CONTROLLER_COUNT];

		void UpdateInputs()
		{
			for(int i = 0; i < CONTROLLER_COUNT; i++)
			{
				oldState[i] = newState[i];
				newState[i] = Hall::GetController(i);
				pressedState[i] = ~oldState[i] & newState[i];
				releasedState[i] = oldState[i] & ~newState[i];
			}
		}
		
	} // namespace Input
} // namespace Engine
