#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Halib
{
	class Font
	{
		//This comes from freetype
		FT_Face face;
		const char* path;
		int size;

public:
		Font(const char* path, int face = 0);
		
		/// @brief Sets the size of the font. The result might not be exactly the given target size. See freetypes documentation for more
		/// @param targetPixelSize
		void SetSize(int targetPixelSize);
		int GetSize();

		FT_Face GetFace() const;
	};
} // namespace Halib
