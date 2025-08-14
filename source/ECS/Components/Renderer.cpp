#include "ECS/Components/Renderer.h"
#include "Engine.h"

namespace Engine
{
	void Renderer::DetermineType()
	{
		Entity entity = ecsSystem->GetEntity(*this);
		if(ecsSystem->HasComponent<Sprite>(entity))
			type = SPRITE;
		else if(ecsSystem->HasComponent<Text>(entity))
			type = TEXT;
		else if(ecsSystem->HasComponent<Rectangle>(entity))
			type = RECTANGLE;
		else
			type = NONE;
	}

	int Renderer::GetLayer() const
	{
		return layer;
	}

	void Renderer::SetLayer(int layer)
	{
		this->layer = layer;
		Systems::renderSystem->ResortEntity(ecsSystem->GetEntity(*this));
	}
} // namespace Engine
