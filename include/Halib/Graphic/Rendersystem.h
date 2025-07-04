#pragma once
#include <queue>
#include "Halib/Entity.h"
#include <memory>
#include "Halib/Graphic/Camera.h"
#include "Halib/Graphic/Tilemap.h"

namespace Halib
{
	class Rendersystem
	{
		std::vector<std::shared_ptr<Entity>> entities;
		
		void SortEntities();
		
public:
		std::shared_ptr<Tilemap> tilemap = nullptr;
		Color backgroundColor = Color(15, 15, 15);
		Camera camera;
		
		void AddEntity(std::shared_ptr<Entity> entity);
		void RemoveEntity(std::shared_ptr<Entity> entity);
		void RemoveEntity(Entity* entity);
		void UpdateEntities();

		void Draw(float deltaTime);

	};
} // namespace Halib
