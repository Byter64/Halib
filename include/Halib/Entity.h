#pragma once
#include "Halib/Graphic/Sprite.h"
#include "Halib/Math/Vec.h"

namespace Halib
{
	struct Entity
	{
private:
		Vec3 position;

public:
		Sprite sprite;
		bool isActive;
		
		Entity();
		Entity(Sprite sprite, Vec3 position);
		
		virtual void Update(float deltaTime) = 0;

		Vec3 GetPosition();
		void SetPosition(Vec3 position);
		void AddPosition(Vec3 deltaPosition);
	};
} // namespace Halib
