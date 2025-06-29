#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Halib
{
	class Font
	{
		//This comes from freetype
		FT_Face face;

public:
		Font(const char* path, int face = 0);
	};
} // namespace Halib
