#pragma once
#include <memory>
#include "Halib/Entity.h"

namespace Halib
{
	class Entitysystem
	{
		std::vector<std::shared_ptr<Entity>> entities;
		
public:

		void AddEntity(std::shared_ptr<Entity> entity);
		void RemoveEntity(std::shared_ptr<Entity> entity);
		void UpdateEntities(float deltaTime);
	};
} // namespace Halib
