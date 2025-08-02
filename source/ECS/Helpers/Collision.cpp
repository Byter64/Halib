#include "ECS/Helpers/Collision.h"

namespace Engine
{
    Collision::Collision(Entity entity1, Entity entity2) :
    entity(entity1), other(entity2)
    {

    }

    Collision::Collision(Entity entity1, Entity entity2, glm::vec2 pos1, glm::vec2 pos2) : 
    entity(entity1), other(entity2), entityPos(pos1), otherPos(pos2)
    {

    }

    bool Collision::operator==(const Collision &other) const
    {
        return (entity == other.entity && this->other == other.other);
    }

    bool Collision::operator!=(const Collision &other) const
    {
        return !(*this == other);
    }

    bool Collision::operator<(const Collision &other) const
    {
        return entity < other.entity || (entity == other.entity && this->other < other.other);
    }
}