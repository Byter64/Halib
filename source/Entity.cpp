#include "Halib/Entity.h"
#include "Halib/Graphic/Rendersystem.h"
#include "Halib/System.h"

Halib::Entity::Entity() : sprite(Sprite()), position(Vec3()), isActive(true), selfReference(this)
{
	rendersystem.AddEntity(selfReference);
}

Halib::Entity::Entity(Sprite sprite, Vec3 position) : sprite(sprite), position(position), isActive(true), selfReference(this)
{
	rendersystem.AddEntity(selfReference);
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

std::shared_ptr<Halib::Entity> Halib::Entity::GetShared()
{
	return selfReference;
}

void Halib::Entity::Destroy()
{
	rendersystem.RemoveEntity(selfReference);
	selfReference = std::shared_ptr<Entity>(nullptr);
}