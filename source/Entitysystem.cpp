#include "Halib/Entitysystem.h"

void Halib::Entitysystem::AddEntity(std::shared_ptr<Entity> entity)
{
	entities.push_back(entity);
}

void Halib::Entitysystem::RemoveEntity(std::shared_ptr<Entity> entity)
{
	for(int i = 0; i < entities.size(); i++)
	{
		if(entities[i] == entity)
		{
			entities[i] = entities[entities.size() - 1];
			entities.resize(entities.size() - 1);
		}
	}
}

void Halib::Entitysystem::UpdateEntities(float deltaTime)
{
	for(auto iter = entities.begin(); iter != entities.end(); iter++)
	{
		std::shared_ptr<Entity> entity = *iter;
		entity->Update(deltaTime);
	}
}
