#include "ECS/Helpers/GlyphCache.h"

namespace Engine
{
	std::unordered_map<GlyphID, CacheEntry> glyphCache;


	std::shared_ptr<Hall::IndexContainer[]> GlyphToIndexContainer(FT_Bitmap& bitmap)
	{

		std::shared_ptr<Hall::IndexContainer[]> indexContainers;
		indexContainers = std::make_unique<Hall::IndexContainer[]>((bitmap.width * bitmap.rows / 32) + 1);

		Hall::IndexContainer* container = indexContainers.get();
		int bitCount = 0; //Pointer inside container

		int pixelCount = 0;
		int bufferCount = 7; //pointer inside the buffer byte
		int x = 0; //byte inside row
		int rowStart = 0;  //point inside buffer to start of the row
		//i is in pixels
		for (int i = 0; i < bitmap.width * bitmap.rows; i++)
		{
			int pixel = (bitmap.buffer[x + rowStart] >> bufferCount) & 1; // either 0 or 1

			bufferCount--;
			pixelCount++;
			if (bufferCount == -1)	x++;
			if (pixelCount == bitmap.width)
			{
				pixelCount = 0;
				bufferCount = 7;
				x = 0;
				rowStart += bitmap.pitch;
			}
			*container = (*container << 1) | pixel;
			bitCount++;
			if (bitCount == 32)
			{
				bitCount = 0;
				container++;
			}
		}

		*container = *container << (32 - bitCount);

		return indexContainers;
	}

	void RemoveFromGlyphCache(FT_Face face)
	{
		std::vector<GlyphID> ids;
		for (auto iter = glyphCache.begin(); iter != glyphCache.end(); iter++)
		{
			if (iter->first.face == face)
				ids.push_back(iter->first);
		}

		while (!ids.empty())
		{
			glyphCache.erase(ids.back());
			ids.pop_back();
		}
	}

} // namespace Engine
