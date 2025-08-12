#include "ECS/ComponentManager.h"
#include "ECSSystem.h"

namespace Engine
{
    void ComponentManager::AddComponentRuntime(Entity entity, ComponentType componentType)
    {
        for(ComponentType dependency : dependencies[componentType])
        {
            if(!HasComponent(entity, dependency))
                ecsSystem->AddComponent(entity, dependency);
        }

        GetComponentArray(componentType)->AddComponentRuntime(entity);
    }

    std::shared_ptr<IComponentArray> ComponentManager::GetComponentArray(ComponentType componentType)
    {
        return componentTypeToComponentArrays[componentType];
    }

    void* ComponentManager::GetComponent(Entity entity, ComponentType componentType)
    {
        return GetComponentArray(componentType)->GetComponentRuntime(entity);
    }

    bool ComponentManager::HasComponent(Entity entity, ComponentType componentType)
    {
        return GetComponentArray(componentType)->HasComponent(entity);
    }

    void ComponentManager::RemoveComponent(Entity entity, ComponentType componentType)
    {
        //Missing: If a dependency is removed, remove the main type BEFORE the dependency is removed
        //Missing: Fill out the Rectangle and Text Renderer
        for(ComponentType inverseDependency : inverseDependencies[componentType])
        {
            if(HasComponent(entity, inverseDependency))
                ecsSystem->RemoveComponent(entity, inverseDependency);
        }

        GetComponentArray(componentType)->RemoveComponent(entity);
    }

    std::shared_ptr<IComponentArray> GetComponentArray(ComponentType componentType);

    const char *ComponentManager::GetTypeName(ComponentType componentType)
    {
        if(typeToName.count(componentType))
            return typeToName[componentType];
        else
            return "Unknown component";
    }

    ComponentType ComponentManager::GetNumberOfRegisteredComponents()
    {
        return nextFreeComponentType;
    }

    void ComponentManager::RegisterDependency(ComponentType type, ComponentType neededType)
    {
        dependencies[type].insert(neededType);
        inverseDependencies[neededType].insert(type);
    }
} //Engine