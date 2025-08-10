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
		void DetermineType();
	public:
		bool isActive = true;
	};
} // namespace Engine
