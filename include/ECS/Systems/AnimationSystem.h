#pragma once
#include "ECS/System.h"
#include <map>
#include "ECS/Components/Animation.h"
#include "ECS/Components/Transform.h"

namespace Engine
{

    class AnimationSystem : public System
    {
        void EntityAdded(Entity entity) override;
        void EntityRemoved(Entity entity) override;

    public:
        void Update(float deltaTime);
    };

} // Engine
