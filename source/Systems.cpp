#pragma once
#include "Systems.h"

extern std::shared_ptr<Engine::ECSSystem> ecsSystem;
namespace Engine::Systems
{
    std::shared_ptr<ECSSystem>& ecsSystem = ::ecsSystem;
    std::shared_ptr<RenderSystem> renderSystem;
    std::shared_ptr<CollisionSystem> collisionSystem;
    //std::shared_ptr<TextRenderSystem> textRenderSystem;
    std::shared_ptr<AnimationSystem> animationSystem;
    std::shared_ptr<TimeManager> timeManager;
    std::shared_ptr<SceneManager> sceneManager;
} // Engine::Systems
