#include "Miscellaneous.h"
#include "Engine.h"
#include <Hall/Hall.h>

namespace Engine
{
    bool isGamePaused;
    bool areAnimationsPaused;
    bool shouldGameClose = false;

    bool GetShouldGameClose()
    {
        return Hall::ShouldClose() || shouldGameClose;
    }

    /*Tells the game to terminate. The current iterationuu of the game loop will still be regularly finished and
     * Engine::OnEndGame() will be called before actually closing the application.
     */
    void EndGame()
    {
        shouldGameClose = true;
    }

    /// Tells the game to pause
    /// \param pauseAnimations
    void PauseGame(bool pauseAnimations)
    {
        isGamePaused = true;
        areAnimationsPaused = pauseAnimations;
        Systems::timeManager->OnPause();
    }

    /// Tells the game to continue after a pause
    void ContinueGame()
    {
        isGamePaused = false;
        areAnimationsPaused = false;
        Systems::timeManager->OnContinue();
    }

    bool GetIsGamePaused()
    {
        return isGamePaused;
    }
} // Engine