#include "ECS/Entity.h"
#include "Engine.h"

namespace Engine
{
    bool Entity::operator==(const Entity &other) const
    {
        return id == other.id;
    }

    bool Entity::operator!=(const Entity &other) const
    {
        return !(*this == other);
    }

    bool Entity::operator<(const Entity &other) const
    {
        return id < other.id;
    }

    bool Entity::operator>(const Entity &other) const
    {
        return id > other.id;
    }

    Entity Entity::operator+(const Entity &other) const
    {
        return Entity{id + other.id};
    }

    Entity Entity::operator-(const Entity &other) const
    {
        return Entity{id - other.id};
    }

    Entity Entity::operator*(const Entity &other) const
    {
        return Entity{id * other.id};
    }

    Entity Entity::operator/(const Entity &other) const
    {
        return Entity{id * other.id};
    }

    Entity Entity::operator%(const Entity &other) const
    {
        return Entity{id % other.id};
    }

    Entity Entity::operator^(const Entity &other) const
    {
        return Entity{id ^ other.id};
    }

    Entity Entity::operator&(const Entity &other) const
    {
        return Entity{id & other.id};
    }

    Entity Entity::operator|(const Entity &other) const
    {
        return Entity{id | other.id};
    }

    Entity Entity::operator~() const
    {
        return Entity{~id};
    }

    Entity Entity::operator!() const
    {
        return Entity{!id};
    }

    Entity Entity::operator<<(const Entity &other) const
    {
        return Entity{id << other.id};
    }

    Entity Entity::operator>>(const Entity &other) const
    {
        return Entity{id >> other.id};
    }

    bool Entity::operator&&(const Entity &other) const
    {
        return id && other.id;
    }

    bool Entity::operator||(const Entity &other) const
    {
        return id || other.id;
    }

    Entity::Entity(int id) : id(id) { }

    Entity::Entity(std::uint32_t id) : id(id) { }

    std::ostream& operator<<(std::ostream& os, const Entity& entity)
    {
        return (os << entity.id);
    }

    std::string Entity::ComponentsToString() const
    {
        std::string text = "";
        for (ComponentType i = 0; i < ecsSystem->GetNumberOfRegisteredComponents(); i++)
        {
            if (ecsSystem->HasComponent(*this, i))
            {
                text += std::to_string(i) + ": ";
                text += ecsSystem->GetComponentTypeName(i);
                text += "\n";
            }
        }
        return text;
    }
}