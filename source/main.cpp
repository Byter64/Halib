#include <iostream>
#include <cmath>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Engine.h"
#include "GlobalGameEvents.h"
#include "CrashHandler.h"
#include <fstream>
#include <string>
#include "EngineException.h"

namespace Engine
{
    extern bool isGamePaused;
    extern bool areAnimationsPaused;
}

int screenWidth = 1920;
int screenHeight = 1080;
GLFWwindow *window;
std::chrono::time_point<std::chrono::steady_clock> time1;

int SetupWindow();
void InitializeECS();
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void window_pos_callback(GLFWwindow *window, int x, int y);
void GameMain();

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
    Engine::CrashHandler::SetupCrashHandler();

    Engine::Systems::timeManager = std::make_shared<Engine::TimeManager>();
    if (SetupWindow() == -1) throw std::exception("Window could not be set up. Help");
    InitializeECS();
    Engine::Systems::inputSystem = std::make_shared<Engine::InputSystem>(window);
    Engine::Systems::sceneManager = std::make_shared<Engine::SceneManager>();
    sceneManager->Initialize();

    OnStartGame(screenWidth, screenHeight);
    float passedTimeInSeconds = 1.0f / 60;
    glfwSetTime(passedTimeInSeconds);

    std::chrono::high_resolution_clock::time_point gameTime1 = std::chrono::high_resolution_clock::now();
    std::cout << "Engine initialization took " << Engine::Systems::timeManager->GetTimeSinceStartup() << " s" << std::endl;
    while (!glfwWindowShouldClose(window))
    {
        time1 = std::chrono::high_resolution_clock::now();

        glfwPollEvents();
        Engine::Systems::inputSystem->Update();

        UpdateWithoutPause();
        sceneManager->GetActiveScene<Engine::Scene>().UpdateWithoutPause();
        if (!Engine::isGamePaused)
        {
            Update(passedTimeInSeconds);
            sceneManager->GetActiveScene<Engine::Scene>().Update(passedTimeInSeconds);
            Engine::Systems::collisionSystem->CheckCollisions();
        }
        sceneManager->Update();
        ecsSystem->DeletePurgatory();

        Engine::Systems::renderSystem->Render();
        Engine::Systems::textRenderSystem->Render();
        if (!Engine::areAnimationsPaused)
            Engine::Systems::animationSystem->Update(passedTimeInSeconds);

        glfwSwapBuffers(window);

        auto time2 = std::chrono::high_resolution_clock::now();
        while (std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() < FRAMETIME)
            time2 = std::chrono::high_resolution_clock::now();

        auto delta = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1);
        passedTimeInSeconds = ((float) delta.count());
        passedTimeInSeconds = passedTimeInSeconds > FRAMETIME * 14 ? FRAMETIME * 14 : passedTimeInSeconds;
        passedTimeInSeconds /= 1000000;

    }

    OnEndGame();
    std::cout << "Game Time: " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - gameTime1).count() / 1000000 << " s" << std::endl;
    ecsSystem->Uninit();
    glfwTerminate();
}

int SetupWindow()
{
    glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_FALSE);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(screenWidth, screenHeight, "GameLabIII", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowPosCallback(window, window_pos_callback);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    return 0;
}

void InitializeECS()
{
    ecsSystem = std::make_shared<Engine::ECSSystem>();
    ecsSystem->Init();
    ecsSystem->RegisterComponent<Engine::Name>();
    ecsSystem->RegisterComponent<Engine::Transform>();
    ecsSystem->RegisterComponent<Engine::MeshRenderer>();
    ecsSystem->RegisterComponent<Engine::BoxCollider>();
    ecsSystem->RegisterComponent<Engine::TilemapCollider>();
    ecsSystem->RegisterComponent<Engine::Text>();
    ecsSystem->RegisterComponent<Engine::Animator>();

    ecsSystem->RegisterSystem<Engine::TransformParentSystem>();
    Engine::Signature transformSignature;
    transformSignature.set(ecsSystem->GetComponentType<Engine::Transform>());
    ecsSystem->AddSystemSignature<Engine::TransformParentSystem>(transformSignature);

    Engine::Systems::renderSystem = ecsSystem->RegisterSystem<Engine::RenderSystem>();
    Engine::Signature renderSignature;
    renderSignature.set(ecsSystem->GetComponentType<Engine::Transform>());
    renderSignature.set(ecsSystem->GetComponentType<Engine::MeshRenderer>());
    ecsSystem->AddSystemSignature<Engine::RenderSystem>(renderSignature);

    Engine::Systems::collisionSystem = ecsSystem->RegisterSystem<Engine::CollisionSystem>();
    Engine::Signature collisionSignature;
    collisionSignature.set(ecsSystem->GetComponentType<Engine::Transform>());
    collisionSignature.set(ecsSystem->GetComponentType<Engine::BoxCollider>());
    ecsSystem->AddSystemSignature<Engine::CollisionSystem>(collisionSignature);

    collisionSignature.set(ecsSystem->GetComponentType<Engine::BoxCollider>(), false);
    collisionSignature.set(ecsSystem->GetComponentType<Engine::TilemapCollider>());
    ecsSystem->AddSystemSignature<Engine::CollisionSystem>(collisionSignature);

    Engine::Systems::textRenderSystem = ecsSystem->RegisterSystem<Engine::TextRenderSystem>();
    Engine::Signature textRenderSignature;
    textRenderSignature.set(ecsSystem->GetComponentType<Engine::Text>());
    ecsSystem->AddSystemSignature<Engine::TextRenderSystem>(textRenderSignature);

    Engine::Systems::animationSystem = ecsSystem->RegisterSystem<Engine::AnimationSystem>();
    Engine::Signature animationSignature;
    animationSignature.set(ecsSystem->GetComponentType<Engine::Animator>());
    animationSignature.set(ecsSystem->GetComponentType<Engine::Transform>());
    ecsSystem->AddSystemSignature<Engine::AnimationSystem>(animationSignature);
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    time1 = std::chrono::high_resolution_clock::now();
    glViewport(0, 0, width, height);
    Engine::Systems::textRenderSystem->SetViewport(width, height);
}

void window_pos_callback(GLFWwindow *window, int x, int y)
{
    time1 = std::chrono::high_resolution_clock::now();
}