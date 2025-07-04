#pragma once
#include "Halib/Graphic/Sprite.h"
#include "Halib/Math/Vec.h"
#include <memory>

namespace Halib
{
	/// @brief Represents an entity. Use GetShared() to get a pointer. Use Destroy() to destroy the entity
	struct Entity
	{
private:
		Vec3 position;
		std::shared_ptr<Entity> selfReference;

public:
		Sprite sprite;
		bool isActive;
		
		Entity();
		Entity(Sprite sprite, Vec3 position);
		
		virtual void Update(float deltaTime) = 0;

		Vec3 GetPosition();
		void SetPosition(Vec3 position);
		void AddPosition(Vec3 deltaPosition);

		std::shared_ptr<Entity> GetShared();
		void Destroy();

		virtual ~Entity() = default;
	};
} // namespace Halib
