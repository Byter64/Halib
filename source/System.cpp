#include "Halib/System.h"
#include <Hall/Hall.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <cstdio>
#include "Halib/Graphic.h"

//Defined in Font.cpp
extern FT_Library freetypeLibrary;

Halib::Rendersystem Halib::rendersystem;
Halib::Entitysystem Halib::entitysystem;

static const int CONTROLLER_COUNT = 2;
static Hall::ControllerState oldState[CONTROLLER_COUNT];
static Hall::ControllerState newState[CONTROLLER_COUNT];
static Hall::ControllerState pressedState[CONTROLLER_COUNT];
static Hall::ControllerState releasedState[CONTROLLER_COUNT];

static float timePoint;
static float newTimePoint;
static float deltaTime;
static float timePerFrame; //in seconds

void Halib::Init()
{
	Hall::Init();
	int error = FT_Init_FreeType(&freetypeLibrary);
	if(error)
	{
		printf("FreeType init failed\n");
		printf("Text will not be available\n");
		printf("Error code: %i\n", error);
	}
	
	timePoint = Halib::GetTimeSinceStartup();
	newTimePoint = Halib::GetTimeSinceStartup();
	deltaTime = 1 / 30.0f;
	SetTargetFramerate(30);
}

static void UpdateInputs()
{
	for(int i = 0; i < CONTROLLER_COUNT; i++)
	{
		oldState[i] = newState[i];
		newState[i] = Hall::GetController(i);
		pressedState[i] = ~oldState[i] & newState[i];
		releasedState[i] = oldState[i] & ~newState[i];
	}
}

static void UpdateTime()
{
	timePoint = newTimePoint;
	deltaTime = newTimePoint - timePoint;
	while(deltaTime <= timePerFrame)
	{
		newTimePoint = Halib::GetTimeSinceStartup();
		deltaTime = newTimePoint - timePoint;
	}
}

void Halib::Update()
{
	UpdateInputs();

	entitysystem.UpdateEntities(deltaTime);
	rendersystem.Draw(deltaTime);

	UpdateTime();
}

void Halib::AddEntity(std::shared_ptr<Entity> entity)
{
	entitysystem.AddEntity(entity);
	rendersystem.AddEntity(entity);
}

void Halib::RemoveEntity(std::shared_ptr<Entity> entity)
{
	entitysystem.RemoveEntity(entity);
	rendersystem.RemoveEntity(entity);
}

void Halib::RemoveEntity(Entity* entity)
{
	entitysystem.RemoveEntity(entity);
	rendersystem.RemoveEntity(entity);
}


bool Halib::GetShouldClose()
{
	return Hall::ShouldClose();
}

float Halib::GetTimeSinceStartup()
{
	return Hall::GetSystemTime() / (float)Hall::SYSTEM_CLK_FREQUENCY;
}

float Halib::GetDeltaTime()
{
	return deltaTime;
}

void Halib::SetTargetFramerate(int framerate)
{
	timePerFrame = 1.0f / framerate;
#ifdef DESKTOP
	Hall::RaylibSetTargetFramerate(framerate);
#endif
}

Halib::VecI2 Halib::GetScreenSize()
{
	return Halib::VecI2(Hall::SCREEN_WIDTH, Hall::SCREEN_HEIGHT);
}

bool Halib::GetButtonDown(int controllerID, Button button)
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

bool Halib::GetButtonPressed(int controllerID, Button button)
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

bool Halib::GetButtonReleased(int controllerID, Button button)
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
