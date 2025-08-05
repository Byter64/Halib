#include "ECS/ComponentManager.h"

namespace Engine
{
    void ComponentManager::AddComponent(Entity entity, void* component, ComponentType componentType)
    {
        GetComponentArray(componentType)->AddComponentRuntime(entity, component);
    }

    std::shared_ptr<IComponentArray> ComponentManager::GetComponentArray(ComponentType componentType)
    {
        return componentTypeToComponentArrays[componentType];
    }

    void* ComponentManager::GetComponent(Entity entity, ComponentType componentType)
    {
        return GetComponentArray(componentType)->GetComponentRuntime(entity);
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
} //Engine