#pragma once
#include <functional>
namespace Engine
{
	class RenderSystem;
	class SpriteRenderer;
	class TextRenderer;
	class RectangleRenderer;

	struct RenderHelper
	{
	private:
		friend class RenderSystem;
		friend class SpriteRenderer;
		friend class TextRenderer;
		friend class RectangleRenderer;
		enum Type
		{
			NONE,
			SPRITE,
			RECTANGLE,
			TEXT
		};

		Type type;
		int layer;
		Type type = NONE;
		void DetermineType();
	public:
		bool isActive = true;

		int GetLayer() const;
		void SetLayer(int layer);
	};
} // namespace Engine
