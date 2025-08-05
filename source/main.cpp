#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <Hall/Hall.h>
#include "Engine.h"
#include "GlobalGameEvents.h"
#include "CrashHandler.h"

namespace Engine
{
    extern bool isGamePaused;
    extern bool areAnimationsPaused;
}

int screenWidth = Hall::SCREEN_WIDTH;
int screenHeight = Hall::SCREEN_HEIGHT;
float time1;

int SetupWindow();
void InitializeECS();
void GameMain();
void ShowRender();

int main()
{
    try
    {
        GameMain();
    }
    catch (Engine::EngineException& baseException)
    {
        std::cout << std::endl;
        std::cout << "ERROR: " << std::endl;
        std::cout << baseException.errorName << std::endl;
        std::cout << baseException.errorDescription << std::endl;
        std::cout << "Stacktrace:\n" << baseException.stackTrace << std::endl;
    }
    return 0;
}

void GameMain()
{
    Hall::Init();
    Engine::CrashHandler::SetupCrashHandler();

    Engine::Systems::timeManager = std::make_shared<Engine::TimeManager>();
    InitializeECS();
    Engine::Systems::sceneManager = std::make_shared<Engine::SceneManager>();
    sceneManager->Initialize();

    OnStartGame(screenWidth, screenHeight);
    Engine::Systems::timeManager->SetTargetFramerate(60);

    float gameTime1 = Engine::Systems::timeManager->GetTimeSinceStartupWithoutPauses();
    float deltaTime = 1/60.0f;
    std::cout << "Engine initialization took " << Engine::Systems::timeManager->GetTimeSinceStartupWithoutPauses() << " s" << std::endl;
    time1 = Engine::Systems::timeManager->GetTimeSinceStartupWithoutPauses();
    while (!Engine::GetShouldGameClose())
    {

        Engine::Input::UpdateInputs();

        UpdateWithoutPause();
        sceneManager->GetActiveScene<Engine::Scene>().UpdateWithoutPause();
        if (!Engine::isGamePaused)
        {
            Update(deltaTime);
            sceneManager->GetActiveScene<Engine::Scene>().Update(deltaTime);
            Engine::Systems::collisionSystem->CheckCollisions();
        }
        sceneManager->Update();
        ecsSystem->DeletePurgatory();

        Engine::Systems::renderSystem->Render();
        //Engine::Systems::textRenderSystem->Render();
        if (!Engine::areAnimationsPaused)
            Engine::Systems::animationSystem->Update(deltaTime);

        ShowRender();

        float time2 = Engine::Systems::timeManager->GetTimeSinceStartupWithoutPauses();
        while (time2 - time1 < Engine::Systems::timeManager->GetTargetTimePerFrame())
            time2 = Engine::Systems::timeManager->GetTimeSinceStartupWithoutPauses();

        std::cout << "deltaTime: " << deltaTime << std::endl;
        deltaTime = time2 - time1;
        time1 = time2;
    }

    OnEndGame();
    std::cout << "Game Time: " << Engine::Systems::timeManager->GetTimeSinceStartupWithoutPauses() - gameTime1 << " s" << std::endl;
    ecsSystem->Uninit();
}

void InitializeECS()
{
    ecsSystem = std::make_shared<Engine::ECSSystem>();
    ecsSystem->Init();
    ecsSystem->RegisterComponent<Engine::Name>();
    ecsSystem->RegisterComponent<Engine::Transform>();
    ecsSystem->RegisterComponent<Engine::SpriteRenderer>();
    ecsSystem->RegisterComponent<Engine::BoxCollider>();
    ecsSystem->RegisterComponent<Engine::TilemapCollider>();
    //ecsSystem->RegisterComponent<Engine::Text>();
    ecsSystem->RegisterComponent<Engine::Animator>();
    ecsSystem->RegisterComponent<Engine::Animation>();

    ecsSystem->RegisterSystem<Engine::TransformParentSystem>();
    Engine::Signature transformSignature;
    transformSignature.set(ecsSystem->GetComponentType<Engine::Transform>());
    ecsSystem->AddSystemSignature<Engine::TransformParentSystem>(transformSignature);

    Engine::Systems::renderSystem = ecsSystem->RegisterSystem<Engine::RenderSystem>();
    Engine::Signature renderSignature;
    renderSignature.set(ecsSystem->GetComponentType<Engine::Transform>());
    renderSignature.set(ecsSystem->GetComponentType<Engine::SpriteRenderer>());
    ecsSystem->AddSystemSignature<Engine::RenderSystem>(renderSignature);

    Engine::Systems::collisionSystem = ecsSystem->RegisterSystem<Engine::CollisionSystem>();
    Engine::Signature collisionSignature;
    collisionSignature.set(ecsSystem->GetComponentType<Engine::Transform>());
    collisionSignature.set(ecsSystem->GetComponentType<Engine::BoxCollider>());
    ecsSystem->AddSystemSignature<Engine::CollisionSystem>(collisionSignature);

    collisionSignature.set(ecsSystem->GetComponentType<Engine::BoxCollider>(), false);
    collisionSignature.set(ecsSystem->GetComponentType<Engine::TilemapCollider>());
    ecsSystem->AddSystemSignature<Engine::CollisionSystem>(collisionSignature);

    //Engine::Systems::textRenderSystem = ecsSystem->RegisterSystem<Engine::TextRenderSystem>();
    //Engine::Signature textRenderSignature;
    //textRenderSignature.set(ecsSystem->GetComponentType<Engine::Text>());
    //ecsSystem->AddSystemSignature<Engine::TextRenderSystem>(textRenderSignature);

    Engine::Systems::animationSystem = ecsSystem->RegisterSystem<Engine::AnimationSystem>();
    Engine::Signature animationSignature;
    animationSignature.set(ecsSystem->GetComponentType<Engine::Animator>());
    animationSignature.set(ecsSystem->GetComponentType<Engine::Animation>());
    animationSignature.set(ecsSystem->GetComponentType<Engine::SpriteRenderer>());
    ecsSystem->AddSystemSignature<Engine::AnimationSystem>(animationSignature);
}

void ShowRender()
{
    Engine::RenderSystem::WaitForGPU();

	bool isVsync = Hall::GetVSync();
	bool newIsVsync = Hall::GetVSync();
	while(!(!isVsync && newIsVsync))
	{
		isVsync = newIsVsync;
		newIsVsync = Hall::GetVSync();
	}
	
	Hall::SetCommandSwapBuffers();
}


#ifndef _MSC_VER
__attribute__((weak)) void OnStartGame(int screenWidth, int screenHeight)
{

}

__attribute__((weak)) void Update(float deltaTime)
{

}

__attribute__((weak)) void UpdateWithoutPause()
{

}

__attribute__((weak)) void OnEndGame()
{

}
#endif // !_MSC_VER