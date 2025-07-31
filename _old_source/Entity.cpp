#include "Halib/Entity.h"
#include "Halib/Graphic/Rendersystem.h"
#include "Halib/System.h"

Halib::Entity::Entity() : sprite(Sprite()), position(Vec3()), isActive(true)
{

}

Halib::Entity::Entity(Sprite sprite, Vec3 position) : sprite(sprite), position(position), isActive(true)
{

}

Halib::Vec3 Halib::Entity::GetPosition()
{
	return position;
}

void Halib::Entity::SetPosition(Vec3 position)
{
	if(position.z != this->position.z)
	{
		this->position = position;
		rendersystem.UpdateEntities();
	}
	else
	{
		this->position = position;
	}
}

void Halib::Entity::AddPosition(Vec3 deltaPosition)
{
	position += deltaPosition;
	if(deltaPosition.z != 0)
		rendersystem.UpdateEntities();
}

void Halib::Entity::Destroy()
{
	rendersystem.RemoveEntity(this);
}