#include "TimeManager.h"
#include <Hall/Hall.h>

namespace Engine
{
    float TimeManager::ToSeconds(unsigned long long time)
    {
        return time / (float)Hall::SYSTEM_CLK_FREQUENCY;
    }

    TimeManager::TimeManager()
    {
        startTime = Hall::GetSystemTime();
    }

    float TimeManager::GetTimeSinceStartup()
    {
        return ToSeconds(GetTimeSinceStartupWithoutPauses() - timePaused);
    }

    float TimeManager::GetTimeSinceStartupWithoutPauses()
    {
        unsigned long long duration = Hall::GetSystemTime() - startTime;
        return ToSeconds(duration);
    }

    void TimeManager::OnPause()
    {
        startTimePause = Hall::GetSystemTime();
    }

    void TimeManager::OnContinue()
    {
        unsigned long long duration = Hall::GetSystemTime() - startTimePause;
        timePaused += duration;
    }

    void TimeManager::SetTargetFramerate(int framerate)
    {
        timePerFrame = 1.0f / framerate;
#ifdef DESKTOP
	    Hall::RaylibSetTargetFramerate(framerate);
#endif
    }

    float TimeManager::GetTargetTimePerFrame()
    {
        return timePerFrame;
    }
} // Engine