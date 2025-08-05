#include "ECS\Components\SpriteRenderer.h"
#include "Engine.h"

namespace Engine
{
	int SpriteRenderer::GetLayer()
	{
		return layer;
	}

	void SpriteRenderer::SetLayer(int layer)
	{
		this->layer = layer;
		Systems::renderSystem->ResortEntity(ecsSystem->GetEntity(*this));
	}
} // namespace Engine
