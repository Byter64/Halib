#pragma once
#include "Entity.h"
#include "ComponentType.h"

namespace Engine
{
    class IComponentArray
    {
    public:
        virtual void AddComponentRuntime(Entity entity) = 0;
        virtual void* GetComponentRuntime(Entity entity) = 0;
        virtual bool HasComponent(Entity entity) = 0;
        virtual void RemoveComponent(Entity entity) = 0;
        virtual void EntityDestroyed(Entity entity) = 0;
        virtual ~IComponentArray() = default;
    };
}