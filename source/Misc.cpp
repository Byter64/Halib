#include "Misc.h"
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