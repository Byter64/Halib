#include "ECSSystem.h"

std::shared_ptr<Engine::ECSSystem> ecsSystem;

namespace Engine
{
    void ECSSystem::Init()
    {
        entityManager = std::make_unique<EntityManager>();
        componentManager = std::make_unique<ComponentManager>();
        systemManager = std::make_unique<SystemManager>();
    }

    void ECSSystem::Uninit()
    {
        systemManager.reset();
        componentManager.reset();
        entityManager.reset();
;    }

    Entity ECSSystem::CreateEntity()
    {
        return entityManager->CreateEntity();
    }

    void ECSSystem::AddComponent(Entity entity, void* component, ComponentType componentType)
    {
        componentManager->AddComponent(entity, component, componentType);
    
        auto signature = entityManager->GetSignature(entity);
        signature.set(componentType, true);
        entityManager->SetSignature(entity, signature);
    
        systemManager->EntitySignatureChanged(entity, signature);
    }

    void ECSSystem::RemoveComponent(Entity entity, ComponentType componentType)
    {
        auto signature = entityManager->GetSignature(entity);
        signature.set(componentType, false);
        entityManager->SetSignature(entity, signature);
        systemManager->EntitySignatureChanged(entity, signature);

        componentManager->RemoveComponent(entity, componentType);
    }

    /*
     * You usually don't want to use this, as it immediately destroys the entity.
     * You should rather use RemoveEntity, which removes the entity at the end of the frame
     */
    void ECSSystem::DestroyEntity(Entity entity)
    {
        systemManager->EntityDestroyed(entity);
        entityManager->DestroyEntity(entity);
        componentManager->EntityDestroyed(entity);
    }

    Signature ECSSystem::GetSignature(Entity entity)
    {
        return entityManager->GetSignature(entity);
    }

    void ECSSystem::DeletePurgatory()
    {
        entityManager->DeletePurgatory();
    }

    /*
     * Removes the entity at the end of the frame
     */
    void ECSSystem::RemoveEntity(Entity entity)
    {
        entityManager->RemoveEntity(entity);
    }

    void ECSSystem::RegisterDependency(ComponentType type, ComponentType neededType)
    {
        componentManager->RegisterDependency(type, neededType);
    }

    ComponentType ECSSystem::GetNumberOfRegisteredComponents()
    {
        return componentManager->GetNumberOfRegisteredComponents();
    }

    const char *ECSSystem::GetComponentTypeName(ComponentType componentType)
    {
        return componentManager->GetTypeName(componentType);
    }

    bool ECSSystem::HasComponent(Entity entity, ComponentType componentType)
    {
        Signature signature = entityManager->GetSignature(entity);
        return signature[componentType];
    }

    void* ECSSystem::GetComponent(Entity entity, ComponentType componentType)
    {
        return componentManager->GetComponent(entity, componentType);
    }

    void ECSSystem::RemoveAllEntities()
    {
        entityManager->RemoveAllEntities();
    }

    bool ECSSystem::IsEntityActive(Entity entity)
    {
        return entityManager->IsEntityActive(entity);
    }
} // Engine