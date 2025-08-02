#pragma once
#include "ECS/Entity.h"
#include "glm/glm.hpp"
namespace Engine
{
    struct Collision
    {
        enum State
        {
            ENTER,
            STAY,
            EXIT
        };

        Entity entity;
        Entity other;

        glm::vec2 entityPos; //In case of a tilemap, this will be equal to the tile's global position
        glm::vec2 otherPos; //In case of a tilemap, this will be equal to the tile's global position
        State state;

        Collision() = default;
        Collision(Entity entity1, Entity entity2);
        Collision(Entity entity1, Entity entity2, glm::vec2 pos1, glm::vec2 pos2);

        bool operator==(const Collision &other) const;
        bool operator!=(const Collision &other) const;
        bool operator<(const Collision &other) const;
    };

} // Engine
