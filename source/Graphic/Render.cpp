#include "Halib/Graphic/Render.h"
#include <memory>
#include <unordered_map>


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

struct CacheEntry
{
	std::shared_ptr<Hall::IndexContainer[]> indexContainers;
	int width;
	int height;
	char offsetLeft;
	char offsetTop;
};

template<>
struct std::hash<GlyphID>
{
	std::size_t operator()(const GlyphID& glyphID) const
	{
		std::size_t h1 = std::hash<FT_Face>{}(glyphID.face);
		std::size_t h2 = std::hash<int>{}(glyphID.glyphIndex);
		std::size_t h3 = std::hash<int>{}(glyphID.size);
		std::size_t h = h1 ^ (h2 << 1);
		h = h ^ (h3 << 1);
		return h;
	}
};

static std::unordered_map<GlyphID, CacheEntry> glyphCache;
static Halib::Camera camera;


static std::shared_ptr<Hall::IndexContainer[]> GlyphToIndexContainer(FT_Bitmap& bitmap)
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

void Halib::WaitForGPU()
{
	while(Hall::GetIsGPUBusy());
}

void Halib::Draw(Image &image, VecI2 position)
{
	WaitForGPU();

#ifdef DESKTOP
	if(image.GetWasDataRequested())
	{
		Hall::UpdateRaylibTexture((Hall::Color*)image.GetData());
	}
#endif

	Hall::SetImage((Hall::Color*)image.GetData(), image.GetWidth(), image.GetHeight());
	Hall::SetExcerpt(0, 0, image.GetWidth(), image.GetHeight());
	Hall::SetScale(1, 1);
	Hall::SetFlip(false, false);
	Hall::SetColorTable(Hall::NONE);
	Hall::SetColorSource(Hall::MEMORY);
	Hall::SetShape(Hall::RECTANGLE);
	Hall::SetScreenPosition(position.x, position.y);

	Hall::Draw();
}

void Halib::Draw(const std::string &text, VecI2 position, Font& font, Color color)
{
	WaitForGPU();

	Hall::COLOR_TABLE_MEMORY[0] = 0;
	Hall::COLOR_TABLE_MEMORY[1] = color.GetHallColor();
	FT_Face face = font.GetFace();
	for(char c : text)
	{
		unsigned int glyphIndex = FT_Get_Char_Index(face, c);
		GlyphID glyphID{ face, glyphIndex, font.GetSize() };
		FT_Load_Glyph(face, glyphIndex, FT_LOAD_DEFAULT);
		if (!glyphCache.count(glyphID))
		{
			FT_Render_Glyph(face->glyph, FT_RENDER_MODE_MONO);

			CacheEntry cacheEntry;

			cacheEntry.indexContainers = GlyphToIndexContainer(face->glyph->bitmap);
			cacheEntry.width = face->glyph->bitmap.width;
			cacheEntry.height = face->glyph->bitmap.rows;
			cacheEntry.offsetLeft = face->glyph->bitmap_left;
			cacheEntry.offsetTop = face->glyph->bitmap_top;
			glyphCache[glyphID] = cacheEntry;
		}

		CacheEntry cacheEntry = glyphCache[glyphID];
		Hall::SetColorTable(Hall::BIT_1, 0);
		Hall::SetColorSource(Hall::MEMORY);
		Hall::SetImage(cacheEntry.indexContainers.get(), cacheEntry.width, cacheEntry.height);
		Hall::SetExcerpt(0, 0, cacheEntry.width, cacheEntry.height);
		Hall::SetScreenPosition(position.x - cacheEntry.offsetLeft, position.y - cacheEntry.offsetTop);
		Hall::SetScale(1, 1);
		Hall::SetFlip(false, false);
		Hall::SetShape(Hall::RECTANGLE);
		Hall::Draw();

		position.x += face->glyph->advance.x / 64;
		position.y += face->glyph->advance.y / 64;
	}
}

void Halib::Draw(const Rectangle &rect, VecI2 position, Color color)
{
	WaitForGPU();

	Hall::SetScale(1, 1);
	Hall::SetFlip(false, false);
	Hall::SetColor(color.GetHallColor());
	Hall::SetColorTable(Hall::NONE);
	Hall::SetColorSource(Hall::COLOR);
	Hall::SetShape(Hall::RECTANGLE);
	Hall::SetRectangle(rect.x, rect.y, rect.width, rect.height);

	Hall::Draw();
}

void Halib::Draw(Sprite &sprite, VecI2 position)
{
	auto image = sprite.GetImage();
	VecI2 frameOffset = sprite.GetFrameOffset();
	VecI2 frameSize = sprite.GetFrameSize();
	WaitForGPU();

#ifdef DESKTOP
	if(image->GetWasDataRequested())
	{
		Hall::UpdateRaylibTexture((Hall::Color*)image->GetData());
	}
#endif

	Hall::SetImage((Hall::Color*)image->GetData(), image->GetWidth(), image->GetHeight());
	Hall::SetExcerpt(frameOffset.x, frameOffset.y, frameSize.x, frameSize.y);
	Hall::SetScale(sprite.scale.x, sprite.scale.y);
	Hall::SetFlip(sprite.flipX, sprite.flipY);
	Hall::SetColorTable(Hall::NONE);
	Hall::SetColorSource(Hall::MEMORY);
	Hall::SetShape(Hall::RECTANGLE);
	Hall::SetScreenPosition(position.x, position.y);

	Hall::Draw();
}

void Halib::Draw(Image &image, VecI2 position, const Camera& camera)
{
	Draw(image, position - camera.position);
}

void Halib::Draw(const std::string &text, VecI2 position, Font& font, const Camera& camera, Color color)
{
	Draw(text, position - camera.position, font, color);
}

void Halib::Draw(const Rectangle &rect, VecI2 position, Color color, const Camera& camera)
{
	Draw(rect, position - camera.position, color);
}

void Halib::Draw(Sprite &sprite, VecI2 position, const Camera& camera)
{
	Draw(sprite, position - camera.position);
}

void Halib::Show()
{
	WaitForGPU();

	bool isVsync = Hall::GetVSync();
	bool newIsVsync = Hall::GetVSync();
	while(!(!isVsync && newIsVsync))
	{
		isVsync = newIsVsync;
		newIsVsync = Hall::GetVSync();
	}
	
	Hall::SetCommandSwapBuffers();
}

void Halib::Clear(Halib::Color color)
{
	WaitForGPU();

	//This is ugly but I want to hide color.color. I hope the compiler optimises this away
	Hall::Color* hallColor = (Hall::Color*)(&color);

	Hall::SetScale(1, 1);
	Hall::SetFlip(false, false);
	Hall::SetColor(*hallColor);
	Hall::SetColorTable(Hall::NONE);
	Hall::SetColorSource(Hall::COLOR);
	Hall::SetShape(Hall::RECTANGLE);
	Hall::SetRectangle(0, 0, Hall::SCREEN_WIDTH, Hall::SCREEN_HEIGHT);

	Hall::Draw();
}