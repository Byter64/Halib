#include "ECS/Components/RenderHelper.h"
#include "Engine.h"

namespace Engine
{
	void RenderHelper::DetermineType()
	{
		Entity entity = ecsSystem->GetEntity(*this);
		if(ecsSystem->HasComponent<SpriteRenderer>(entity))
			type = SPRITE;
		else if(ecsSystem->HasComponent<TextRenderer>(entity))
			type = TEXT;
		else if(ecsSystem->HasComponent<RectangleRenderer>(entity))
			type = RECTANGLE;
		else
			type = NONE;
	}
} // namespace Engine
