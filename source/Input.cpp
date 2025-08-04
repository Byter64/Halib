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
		
		
		bool GetButtonPressed(int controllerID, Button button)
		{
			switch (button) 
			{
			case A: return Hall::GetA(newState[controllerID]);
			case B: return Hall::GetB(newState[controllerID]);
			case X: return Hall::GetX(newState[controllerID]);
			case Y: return Hall::GetY(newState[controllerID]);
			case LEFT: return Hall::GetLeft(newState[controllerID]);
			case RIGHT: return Hall::GetRight(newState[controllerID]);
			case UP: return Hall::GetUp(newState[controllerID]);
			case DOWN: return Hall::GetDown(newState[controllerID]);
			case START: return Hall::GetStart(newState[controllerID]);
			case SELECT: return Hall::GetSelect(newState[controllerID]);
			case LEFT_SHOULDER: return Hall::GetL(newState[controllerID]);
			case RIGHT_SHOULDER: return Hall::GetR(newState[controllerID]);
			}
		}

		bool GetButtonDown(int controllerID, Button button)
		{
			switch (button) 
			{
			case A: return Hall::GetA(pressedState[controllerID]);
			case B: return Hall::GetB(pressedState[controllerID]);
			case X: return Hall::GetX(pressedState[controllerID]);
			case Y: return Hall::GetY(pressedState[controllerID]);
			case LEFT: return Hall::GetLeft(pressedState[controllerID]);
			case RIGHT: return Hall::GetRight(pressedState[controllerID]);
			case UP: return Hall::GetUp(pressedState[controllerID]);
			case DOWN: return Hall::GetDown(pressedState[controllerID]);
			case START: return Hall::GetStart(pressedState[controllerID]);
			case SELECT: return Hall::GetSelect(pressedState[controllerID]);
			case LEFT_SHOULDER: return Hall::GetL(pressedState[controllerID]);
			case RIGHT_SHOULDER: return Hall::GetR(pressedState[controllerID]);
			}
		}

		bool GetButtonReleased(int controllerID, Button button)
		{
			switch (button) 
			{
			case A: return Hall::GetA(releasedState[controllerID]);
			case B: return Hall::GetB(releasedState[controllerID]);
			case X: return Hall::GetX(releasedState[controllerID]);
			case Y: return Hall::GetY(releasedState[controllerID]);
			case LEFT: return Hall::GetLeft(releasedState[controllerID]);
			case RIGHT: return Hall::GetRight(releasedState[controllerID]);
			case UP: return Hall::GetUp(releasedState[controllerID]);
			case DOWN: return Hall::GetDown(releasedState[controllerID]);
			case START: return Hall::GetStart(releasedState[controllerID]);
			case SELECT: return Hall::GetSelect(releasedState[controllerID]);
			case LEFT_SHOULDER: return Hall::GetL(releasedState[controllerID]);
			case RIGHT_SHOULDER: return Hall::GetR(releasedState[controllerID]);
			}
		}
	} // namespace Input
} // namespace Engine
