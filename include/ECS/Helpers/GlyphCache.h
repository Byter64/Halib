#pragma once
#include <memory>
#include <unordered_map>
#include <Hall/Hall.h>
#include "ft2build.h"
#include FT_FREETYPE_H

namespace Engine
{
	struct GlyphID
	{
		FT_Face face;
		unsigned int glyphIndex;
		int size; //For now, take the x size only
		
		bool operator==(const GlyphID &other) const
		{
			return face == other.face && glyphIndex == other.glyphIndex && size == other.size;
		}
	};
}

template<>
struct std::hash<Engine::GlyphID>
{
	std::size_t operator()(const Engine::GlyphID& glyphID) const
	{
		std::size_t h1 = std::hash<FT_Face>{}(glyphID.face);
		std::size_t h2 = std::hash<int>{}(glyphID.glyphIndex);
		std::size_t h3 = std::hash<int>{}(glyphID.size);
		std::size_t h = h1 ^ (h2 << 1);
		h = h ^ (h3 << 1);
		return h;
	}
};

namespace Engine
{
	struct CacheEntry
	{
		std::shared_ptr<Hall::IndexContainer[]> indexContainers;
		int width;
		int height;
		char offsetLeft;
		char offsetTop;
	};
	
	
	std::shared_ptr<Hall::IndexContainer[]> GlyphToIndexContainer(FT_Bitmap& bitmap);
	
	extern std::unordered_map<GlyphID, CacheEntry> glyphCache;
	void RemoveFromGlyphCache(FT_Face face);
} // namespace Engine
