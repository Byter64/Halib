#pragma once
#include <chrono>

namespace Engine
{
    class TimeManager
    {
        unsigned long long startTime;
        unsigned long long startTimePause;

        unsigned long long timePaused = 0;

        float ToSeconds(unsigned long long time);
    public:
        TimeManager();
        float GetTimeSinceStartup();
        float GetTimeSinceStartupWithoutPauses();
        void OnPause();
        void OnContinue();
    };
} // Engine
