#pragma once
#include <memory>
#include <set>
#include "ECS/EntityManager.h"
//#include "ECS/ComponentManager.h"
#include "ECS/SystemManager.h"

namespace Engine
{
    class ComponentManager;
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
        void AddComponentRuntime(Entity entity, ComponentType componentType);
        void AddComponentRuntime(Entity entity, void* component, ComponentType componentType);

        //You found a secret! Please do not use this function. It is for internal use only
        void RemoveComponent(Entity entity, ComponentType componentType);

        ///Returns true, if the entity has not been destroyed by a call to RemoveEntity() or similar
        bool IsEntityActive(Entity entity);

        ///WARNING: all variables with entity IDs will be invalid after calling this function. New once need to be inquired with "CreateEntity()"
        void RemoveAllEntities();
        void DeletePurgatory();

        template<typename T>
        void RegisterComponent();

        //Component data is default initialized, when using this AddComponent overload
        template<typename T>
        T& AddComponent(Entity entity);

        template<typename T>
        void AddComponent(Entity entity, T component);

        template<typename T>
        void RemoveComponent(Entity entity);

        template<typename T>
        T& GetComponent(Entity entity);
        
        template<typename T>
        bool HasComponent(Entity entity);

        template<typename T>
        int GetNumberOfComponents();

        /// @brief Sets a dependency. From now on, it is assured, that a component of type "type" will only exist, if a component of type "neededType" also exists for an entity. This means, that if "type" is added to an entity without "neededType", "neededType" will automatically added BEFORE "type" is added. When "neededType" is removed, "type" will be automatically removed BEFORE "neededType" is removed.
        /// @param type The main type
        /// @param neededType The type that "type" is dependent on
        void RegisterDependency(ComponentType type, ComponentType neededType);
        
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
        Entity GetEntity(T const& component);

        template<typename T>
        ComponentType GetComponentType();

        template<typename T>
        std::shared_ptr<T> RegisterSystem();

        //Adds a signature to the system. All entities having this signature will now be available for the system
        template<typename T>
        void AddSystemSignature(Signature signature);
    };

    extern std::shared_ptr<ECSSystem> ecsSystem;
} // Engine

