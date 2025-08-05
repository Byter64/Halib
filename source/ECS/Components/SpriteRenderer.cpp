#include "ECS\Components\SpriteRenderer.h"

namespace Engine
{
	int SpriteRenderer::GetLayer()
	{
		return layer;
	}

	void SpriteRenderer::SetLayer(int layer)
	{
		this->layer = layer;
	}
} // namespace Engine
