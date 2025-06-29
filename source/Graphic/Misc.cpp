#include "Graphic/Misc.h"
#include <Hall/Hall.h>

void Halib::Misc::WaitForGPU()
{
	while(Hall::GetIsGPUBusy());
}

void Halib::Misc::ShowFrame()
{
	WaitForGPU();

	bool isVsync = Hall::GetVSync();
	bool newIsVsync = Hall::GetVSync();
	while(!(!isVsync && newIsVsync))
	{
		isVsync = newIsVsync;
		newIsVsync = Hall::GetVSync();
	}
	
	Hall::SetCommandSwapBuffers();
}

void Halib::Misc::ClearFrame(Halib::Color color)
{
	Misc::WaitForGPU();

	//This is ugly but I want to hide color.color. I hope the compiler optimises this away
	Hall::Color* hallColor = (Hall::Color*)(&color);

	Hall::SetScale(1, 1);
	Hall::SetFlip(false, false);
	Hall::SetColor(*hallColor);
	Hall::SetColorTable(Hall::NONE);
	Hall::SetColorSource(Hall::COLOR);
	Hall::SetShape(Hall::RECTANGLE);
	Hall::SetRectangle(0, 0, Hall::SCREEN_WIDTH, Hall::SCREEN_HEIGHT);

	Hall::Draw();
}

float Halib::Misc::GetTimeSinceStartup()
{
	return Hall::GetSystemTime() / (float)Hall::SYSTEM_CLK_FREQUENCY;
}