#pragma once
#include <memory>
#include <set>
#include "ECS/EntityManager.h"
#include "ECS/ComponentManager.h"
#include "ECS/SystemManager.h"

namespace Engine
{

    class ECSSystem
    {
        std::unique_ptr<EntityManager> entityManager;
        std::unique_ptr<ComponentManager> componentManager;
        std::unique_ptr<SystemManager> systemManager;

        std::set<Entity> entityPurgatory;

    public:
        void Init();
        void Uninit();

        Entity CreateEntity();
        void DestroyEntity(Entity entity);
        void RemoveEntity(Entity entity);

        //You found a secret! Please do not use this function. It is for internal use only
        void AddComponent(Entity entity, void* component, ComponentType componentType);

        ///Returns true, if the entity has not been destroyed by a call to RemoveEntity() or similar
        bool IsEntityActive(Entity entity);

        ///WARNING: all variables with entity IDs will be invalid after calling this function. New once need to be inquired with "CreateEntity()"
        void RemoveAllEntities();
        void DeletePurgatory();

        template<typename T>
        void RegisterComponent()
        {
            componentManager->RegisterComponent<T>();
        }

        //Component data is default initialized, when using this AddComponent overload
        template<typename T>
        T& AddComponent(Entity entity)
        {
            T& component = componentManager->AddComponent<T>(entity);

            auto signature = entityManager->GetSignature(entity);
            signature.set(componentManager->GetComponentType<T>(), true);
            entityManager->SetSignature(entity, signature);

            systemManager->EntitySignatureChanged(entity, signature);

            return component;
        }

        template<typename T>
        void AddComponent(Entity entity, T component)
        {
            componentManager->AddComponent<T>(entity, component);

            auto signature = entityManager->GetSignature(entity);
            signature.set(componentManager->GetComponentType<T>(), true);
            entityManager->SetSignature(entity, signature);

            systemManager->EntitySignatureChanged(entity, signature);
        }

        template<typename T>
        void RemoveComponent(Entity entity)
        {

            auto signature = entityManager->GetSignature(entity);
            signature.set(componentManager->GetComponentType<T>(), false);
            entityManager->SetSignature(entity, signature);
            systemManager->EntitySignatureChanged(entity, signature);

            componentManager->RemoveComponent<T>(entity);
        }

        template<typename T>
        T& GetComponent(Entity entity)
        {
            return componentManager->GetComponent<T>(entity);
        }
        
        template<typename T>
        bool HasComponent(Entity entity)
        {
            return componentManager->HasComponent<T>(entity);
        }

        template<typename T>
        int GetNumberOfComponents()
        {
            return componentManager->GetNumberOfComponents<T>();
        }

        ComponentType GetNumberOfRegisteredComponents();
        const char *GetComponentTypeName(ComponentType componentType);

        /// Runtime component check. ONLY USE THIS IF YOU KNOW WHAT YOU ARE DOING
        /// \param entity
        /// \return
        bool HasComponent(Entity entity, ComponentType componentType);

        /// @brief Runtime get component. ONLY USE THIS IF YOU KNOW WHAT YOU ARE DOING
        /// @param entity 
        /// @return 
        void* GetComponent(Entity entity, ComponentType componentType);

        Signature GetSignature(Entity entity);

        template<typename T>
        Entity GetEntity(T const& component)
        {
            return componentManager->GetEntity(component);
        }


        template<typename T>
        ComponentType GetComponentType()
        {
            return componentManager->GetComponentType<T>();
        }

        template<typename T>
        std::shared_ptr<T> RegisterSystem()
        {
            return systemManager->RegisterSystem<T>();
        }

        //Adds a signature to the system. All entities having this signature will now be available for the system
        template<typename T>
        void AddSystemSignature(Signature signature)
        {
            systemManager->AddSignature<T>(signature);
        }
    };

} // Engine

extern std::shared_ptr<Engine::ECSSystem> ecsSystem;
