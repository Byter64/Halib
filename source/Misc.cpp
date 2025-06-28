#include "Misc.h"
#include <Hall/Hall.h>

void Halib::Misc::WaitForGPU()
{
	while(Hall::GetIsGPUBusy());
}