#include "Halib/Entity.h"

Halib::Entity::Entity() : sprite(Sprite()), position(Vec3()), isActive(true)
{

}

Halib::Entity::Entity(Sprite sprite, Vec3 position) : sprite(sprite), position(position), isActive(true)
{

}