#pragma once
#include <queue>
#include "Halib/Entity.h"
#include <memory>
#include "Halib/Graphic/Camera.h"

namespace Halib
{
	class Rendersystem
	{
		std::vector<std::shared_ptr<Entity>> entities;

		void SortEntities();

public:
		void AddEntity(std::shared_ptr<Entity> entity);
		void RemoveEntity(std::shared_ptr<Entity> entity);
		void UpdateEntities();
		void Draw(Camera& camera);

	};
} // namespace Halib
