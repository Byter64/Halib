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

extern FT_Library freetypeLibrary;
void GameMain()
{
    Hall::Init();
    int error = FT_Init_FreeType(&freetypeLibrary);
	if(error)
	{
		printf("FreeType init failed\n");
		printf("Text will not be available\n");
		printf("Error code: %i\n", error);
	}
    
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
        Engine::ecsSystem->DeletePurgatory();

        Engine::Systems::renderSystem->Render();
        //Engine::Systems::textRenderSystem->Render();
        if (!Engine::areAnimationsPaused)
            Engine::Systems::animationSystem->Update(deltaTime);

        ShowRender();

        float time2 = Engine::Systems::timeManager->GetTimeSinceStartupWithoutPauses();
        while (time2 - time1 < Engine::Systems::timeManager->GetTargetTimePerFrame())
            time2 = Engine::Systems::timeManager->GetTimeSinceStartupWithoutPauses();

        deltaTime = time2 - time1;
        time1 = time2;
    }

    OnEndGame();
    std::cout << "Game Time: " << Engine::Systems::timeManager->GetTimeSinceStartupWithoutPauses() - gameTime1 << " s" << std::endl;
    Engine::ecsSystem->Uninit();
}

void InitializeECS()
{
    Engine::ecsSystem = std::make_shared<Engine::ECSSystem>();
    Engine::ecsSystem->Init();
    Engine::ecsSystem->RegisterComponent<Engine::Name>();
    Engine::ecsSystem->RegisterComponent<Engine::Transform>();
    Engine::ecsSystem->RegisterComponent<Engine::Sprite>();
    Engine::ecsSystem->RegisterComponent<Engine::Text>();
    Engine::ecsSystem->RegisterComponent<Engine::Rectangle>();
    Engine::ecsSystem->RegisterComponent<Engine::Renderer>();
    Engine::ecsSystem->RegisterComponent<Engine::BoxCollider>();
    Engine::ecsSystem->RegisterComponent<Engine::TilemapCollider>();
    Engine::ecsSystem->RegisterComponent<Engine::Animator>();
    Engine::ecsSystem->RegisterComponent<Engine::Animation>();

    Engine::ecsSystem->RegisterDependency(Engine::ecsSystem->GetComponentType<Engine::Rectangle>(), Engine::ecsSystem->GetComponentType<Engine::Renderer>());
    Engine::ecsSystem->RegisterDependency(Engine::ecsSystem->GetComponentType<Engine::Sprite>(), Engine::ecsSystem->GetComponentType<Engine::Renderer>());
    Engine::ecsSystem->RegisterDependency(Engine::ecsSystem->GetComponentType<Engine::Text>(), Engine::ecsSystem->GetComponentType<Engine::Renderer>());
    

    Engine::ecsSystem->RegisterSystem<Engine::TransformParentSystem>();
    Engine::Signature transformSignature;
    transformSignature.set(Engine::ecsSystem->GetComponentType<Engine::Transform>());
    Engine::ecsSystem->AddSystemSignature<Engine::TransformParentSystem>(transformSignature);

    Engine::Systems::renderSystem = Engine::ecsSystem->RegisterSystem<Engine::RenderSystem>();
    Engine::Signature renderSignature;
    renderSignature.set(Engine::ecsSystem->GetComponentType<Engine::Transform>());
    renderSignature.set(Engine::ecsSystem->GetComponentType<Engine::Renderer>());
    Engine::ecsSystem->AddSystemSignature<Engine::RenderSystem>(renderSignature);

    Engine::Systems::collisionSystem = Engine::ecsSystem->RegisterSystem<Engine::CollisionSystem>();
    Engine::Signature collisionSignature;
    collisionSignature.set(Engine::ecsSystem->GetComponentType<Engine::Transform>());
    collisionSignature.set(Engine::ecsSystem->GetComponentType<Engine::BoxCollider>());
    Engine::ecsSystem->AddSystemSignature<Engine::CollisionSystem>(collisionSignature);

    collisionSignature.set(Engine::ecsSystem->GetComponentType<Engine::BoxCollider>(), false);
    collisionSignature.set(Engine::ecsSystem->GetComponentType<Engine::TilemapCollider>());
    Engine::ecsSystem->AddSystemSignature<Engine::CollisionSystem>(collisionSignature);

    //Engine::Systems::textRenderSystem = Engine::ecsSystem->RegisterSystem<Engine::TextRenderSystem>();
    //Engine::Signature textRenderSignature;
    //textRenderSignature.set(Engine::ecsSystem->GetComponentType<Engine::Text>());
    //Engine::ecsSystem->AddSystemSignature<Engine::TextRenderSystem>(textRenderSignature);

    Engine::Systems::animationSystem = Engine::ecsSystem->RegisterSystem<Engine::AnimationSystem>();
    Engine::Signature animationSignature;
    animationSignature.set(Engine::ecsSystem->GetComponentType<Engine::Animator>());
    animationSignature.set(Engine::ecsSystem->GetComponentType<Engine::Animation>());
    animationSignature.set(Engine::ecsSystem->GetComponentType<Engine::Sprite>());
    Engine::ecsSystem->AddSystemSignature<Engine::AnimationSystem>(animationSignature);
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