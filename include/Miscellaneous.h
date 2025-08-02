#pragma once

namespace Engine
{
    bool GetShouldGameClose();
    void EndGame();
    void PauseGame(bool pauseAnimations = true);
    void ContinueGame();
    bool GetIsGamePaused();

} // Engine
