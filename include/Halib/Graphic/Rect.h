#pragma once
#include "Halib/Entity.h"
#include "Halib/Graphic/Color.h"

namespace Halib
{
	class Rect : public Entity
	{
		Color color;
		
		public:
		Rect(VecI2 position, VecI2 size, Color color);
		
		void Update(float deltaTime) override;
	};
} // namespace Halib