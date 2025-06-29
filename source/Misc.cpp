#include "Misc.h"
#include <Hall/Hall.h>

float Halib::Misc::GetTimeSinceStartup()
{
	return Hall::GetSystemTime() / (float)Hall::SYSTEM_CLK_FREQUENCY;
}