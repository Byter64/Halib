#pragma once
#include <chrono>

namespace Engine
{
    class TimeManager
    {
        unsigned long long startTime;
        unsigned long long startTimePause;

        unsigned long long timePaused = 0;

        float timePerFrame = 1/60.0f;
    public:
        float ToSeconds(unsigned long long time);
        
        TimeManager();
        float GetTimeSinceStartup();
        float GetTimeSinceStartupWithoutPauses();
        void OnPause();
        void OnContinue();

        /// @brief Sets the target framerate. Currently, the framerate is vsynced, so it can only be a divider of 60 Hz, other numbers will be ceiled to the next divider of 60. Values higher than 60 might not work as expected on desktop
	    /// @param framerate
	    void SetTargetFramerate(int framerate);
        float GetTargetTimePerFrame();
    };
} // Engine
