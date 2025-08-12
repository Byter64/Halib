#pragma once
#include <unordered_map>
#include <set>
#include <memory>
#include <stdexcept>
#include "ComponentType.h"
#include "IComponentArray.h"
#include "ComponentArray.h"
#include "EngineException.h"
#include "ECSSystem_Header.h"

namespace Engine
{

    extern std::shared_ptr<ECSSystem> ecsSystem;

    class ComponentManager
    {
        friend class ECSSystem;

        std::unordered_map<const char*, ComponentType> nameToType;
        std::unordered_map<ComponentType, const char*> typeToName;
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> typeToComponentArrays;
        std::unordered_map<ComponentType, std::shared_ptr<IComponentArray>> componentTypeToComponentArrays;
        //key needs all components in value
        std::unordered_map<ComponentType, std::set<ComponentType>> dependencies;
        std::unordered_map<ComponentType, std::set<ComponentType>> inverseDependencies;

        ComponentType nextFreeComponentType;

        template<typename T>
        std::shared_ptr<ComponentArray<T>> GetComponentArray()
        {
            const char* typeName = typeid(T).name();

            if(nameToType.find(typeName) == nameToType.end())
            {
                std::string message{"Component \""};
                message += typeName;
                message += "\" has not been registered yet";
                throw EngineException("COMPONENT NOT REGISTERED", message);
            }

            return std::static_pointer_cast<ComponentArray<T>>(typeToComponentArrays[typeName]);
        }

        //This is only meant for the CopyEntity function
        void AddComponent(Entity entity, void* component, ComponentType componentType);
        std::shared_ptr<IComponentArray> GetComponentArray(ComponentType componentType);
        void* GetComponent(Entity entity, ComponentType componentType);
        bool HasComponent(Entity entity, ComponentType componentType);
        void RemoveComponent(Entity entity, ComponentType componentType);
        
        public:
        template<typename T>
        void RegisterComponent()
        {
            const char* typeName = typeid(T).name();

            if(nameToType.find(typeName) != nameToType.end())
            {
                std::string message{"Component \""};
                message += typeName;
                message += "\" has already been registered";
                throw EngineException("COMPONENT ALREADY REGISTERED", message);
            }

            std::shared_ptr<IComponentArray> array = std::make_shared<ComponentArray<T>>();
            typeToComponentArrays.insert({typeName, array});
            componentTypeToComponentArrays.insert({nextFreeComponentType, array});
            nameToType.insert({typeName, nextFreeComponentType});
            typeToName.insert({nextFreeComponentType, typeName});
            dependencies[nextFreeComponentType] = std::set<ComponentType>();
            inverseDependencies[nextFreeComponentType] = std::set<ComponentType>();

            nextFreeComponentType++;
        }

        template<typename T>
        ComponentType GetComponentType()
        {
            const char* typeName = typeid(T).name();

            if(nameToType.find(typeName) == nameToType.end())
            {
                std::string message{"Component \""};
                message += typeName;
                message += "\" has not been registered yet";
                throw EngineException("COMPONENT NOT REGISTERED", message);
            }

            return nameToType[typeName];
        }

        //The data of the newly created component is still undefined
        template<typename T>
        T& AddComponent(Entity entity)
        {
            ComponentType type = nameToType[typeid(T).name()];
            for(ComponentType dependency : dependencies[type])
            {
                if(!HasComponent(entity, dependency))
                    ecsSystem->AddComponent(entity, dependency);
            }

            return GetComponentArray<T>()->AddComponent(entity);
        }

        template<typename T>
        void AddComponent(Entity entity, T component)
        {
            ComponentType type = nameToType[typeid(T).name()];
            for(ComponentType dependency : dependencies[type])
            {
                if(!HasComponent(entity, dependency))
                    ecsSystem->AddComponent(entity, dependency);
            }

            GetComponentArray<T>()->AddComponent(entity, component);
        }

        template<typename T>
        void RemoveComponent(Entity entity)
        {
            //Missing: Fill out the Rectangle and Text Renderer
            for(ComponentType inverseDependency : inverseDependencies[GetComponentType<T>()])
            {
                if(HasComponent(entity, inverseDependency))
                    ecsSystem->RemoveComponent(entity, inverseDependency);
            }

            GetComponentArray<T>()->RemoveComponent(entity);
        }

        template<typename T>
        T& GetComponent(Entity entity)
        {
            return GetComponentArray<T>()->GetComponent(entity);
        }

        template<typename T>
        bool HasComponent(Entity entity)
        {
            return GetComponentArray<T>()->HasComponent(entity);
        }

        template<typename T>
        int GetNumberOfComponents()
        {
            return GetComponentArray<T>()->GetNumberOfComponents();
        }

        template<typename T>
        Entity GetEntity(T const& component)
        {
            return GetComponentArray<T>()->GetEntity(component);
        }

        void EntityDestroyed(Entity entity)
        {
            for(auto const& pair: typeToComponentArrays)
            {
                auto const& component = pair.second;
                component->EntityDestroyed(entity);
            }
        }

        const char *GetTypeName(ComponentType componentType);
        ComponentType GetNumberOfRegisteredComponents();
        void RegisterDependency(ComponentType type, ComponentType neededType);
    };

} // Engine
