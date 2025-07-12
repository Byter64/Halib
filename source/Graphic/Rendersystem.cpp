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
	toBeAdded.push_back(entity);
}

void Halib::Rendersystem::UpdateEntities()
{
	SortEntities();
}

void Halib::Rendersystem::RemoveEntity(std::shared_ptr<Entity> entity)
{
	RemoveEntity(entity.get());
}

void Halib::Rendersystem::RemoveEntity(Entity* entity)
{
	toBeRemoved.push_back(entity);
}

void Halib::Rendersystem::Draw(float deltaTime)
{
	
	//if(tilemap != nullptr)
	//	tilemap->Draw(camera);
	//else
	Clear(Halib::Color(backgroundColor));

	for(auto iter = entities.begin(); iter != entities.end(); iter++)
	{
		std::shared_ptr<Entity> entity = *iter;
		entity->sprite.Draw(entity->GetPosition(), deltaTime, camera);
	}
	Show();

	for (auto iter = toBeRemoved.begin(); iter != toBeRemoved.end(); iter++)
	{
		Entity* entity = *iter;
		for (int i = 0; i < entities.size(); i++)
		{
			if (entities[i].get() == entity)
			{
				entities[i] = entities[entities.size() - 1];
				entities.resize(entities.size() - 1);
			}
		}
	}
	toBeRemoved.clear();
}
