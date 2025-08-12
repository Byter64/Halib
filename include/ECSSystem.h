#pragma once
#include <memory>
#include <set>
#include "ECSSystem_Header.h"
#include "ECS/EntityManager.h"
#include "ECS/ComponentManager.h"
#include "ECS/SystemManager.h"

namespace Engine
{
    template<typename T>
    void ECSSystem::RegisterComponent()
    {
        componentManager->RegisterComponent<T>();
    }

    //Component data is default initialized, when using this AddComponent overload
    template<typename T>
    T& ECSSystem::AddComponent(Entity entity)
    {
        T& component = componentManager->AddComponent<T>(entity);
        auto signature = entityManager->GetSignature(entity);
        signature.set(componentManager->GetComponentType<T>(), true);
        entityManager->SetSignature(entity, signature);
        systemManager->EntitySignatureChanged(entity, signature);
        return component;
    }

    template<typename T>
    void ECSSystem::AddComponent(Entity entity, T component)
    {
        componentManager->AddComponent<T>(entity, component);
        auto signature = entityManager->GetSignature(entity);
        signature.set(componentManager->GetComponentType<T>(), true);
        entityManager->SetSignature(entity, signature);
        systemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    void ECSSystem::RemoveComponent(Entity entity)
    {
        auto signature = entityManager->GetSignature(entity);
        signature.set(componentManager->GetComponentType<T>(), false);
        entityManager->SetSignature(entity, signature);
        systemManager->EntitySignatureChanged(entity, signature);
        componentManager->RemoveComponent<T>(entity);
    }

    template<typename T>
    T& ECSSystem::GetComponent(Entity entity)
    {
        return componentManager->GetComponent<T>(entity);
    }
    
    template<typename T>
    bool ECSSystem::HasComponent(Entity entity)
    {
        return componentManager->HasComponent<T>(entity);
    }

    template<typename T>
    int ECSSystem::GetNumberOfComponents()
    {
        return componentManager->GetNumberOfComponents<T>();
    }
    
    template<typename T>
    Entity ECSSystem::GetEntity(T const& component)
    {
        return componentManager->GetEntity(component);
    }

    template<typename T>
    ComponentType ECSSystem::GetComponentType()
    {
        return componentManager->GetComponentType<T>();
    }

    template<typename T>
    std::shared_ptr<T> ECSSystem::RegisterSystem()
    {
        return systemManager->RegisterSystem<T>();
    }
    
    //Adds a signature to the system. All entities having this signature will now be available for the system
    template<typename T>
    void ECSSystem::AddSystemSignature(Signature signature)
    {
        systemManager->AddSignature<T>(signature);
    }
    
    extern std::shared_ptr<ECSSystem> ecsSystem;
} // Engine

