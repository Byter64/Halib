#include "Halib/Graphic/Rendersystem.h"
#include <algorithm>
#include "Halib/Graphic/Render.h"

void Halib::Rendersystem::SortEntities()
{
	//Always sorting the entities before drawing it is inefficient, but we don't have z-bufferung in the GPU
	//We could 
	auto compare = [](std::shared_ptr<Entity>& left, std::shared_ptr<Entity>& right)
	{
		return left->GetPosition().z < right->GetPosition().z;
	};
	std::sort(entities.begin(), entities.end(), compare);
}

void Halib::Rendersystem::AddEntity(std::shared_ptr<Entity> entity)
{
	entities.push_back(entity);
	SortEntities();
}

void Halib::Rendersystem::UpdateEntities()
{
	SortEntities();
}

void Halib::Rendersystem::RemoveEntity(std::shared_ptr<Entity> entity)
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

void Halib::Rendersystem::Draw(Camera& camera)
{
	for(auto iter = entities.begin(); iter != entities.end(); iter++)
	{
		std::shared_ptr<Entity> entity = *iter;
		Halib::Draw(entity->sprite, entity->GetPosition(), camera);
	}
}
