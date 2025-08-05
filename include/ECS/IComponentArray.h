#pragma once
#include "Entity.h"

namespace Engine
{
    class IComponentArray
    {
    public:
        virtual void AddComponentRuntime(Entity entity, void* component) = 0;
        virtual void* GetComponentRuntime(Entity entity) = 0;
        virtual void EntityDestroyed(Entity entity) = 0;
        virtual ~IComponentArray() = default;
    };
}