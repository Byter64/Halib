#include "Halib/Entitysystem.h"
#include "Halib/Graphic/Rendersystem.h"
#include "Halib/System.h"

void Halib::Entitysystem::UpdateEntities(float deltaTime)
{
	bool haveEntitiesBeenAdded = !rendersystem.toBeAdded.empty();
	while (!rendersystem.toBeAdded.empty())
	{
		rendersystem.entities.push_back(rendersystem.toBeAdded.back());
		rendersystem.toBeAdded.pop_back();
	}
	if (haveEntitiesBeenAdded)
	{
		rendersystem.SortEntities();
	}

	auto& entities = rendersystem.entities;
	for(auto iter = entities.begin(); iter != entities.end(); iter++)
	{
		std::shared_ptr<Entity> entity = *iter;
		entity->Update(deltaTime);
	}
}
