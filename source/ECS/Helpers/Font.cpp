#include "ECS/Helpers/Font.h"
#include <cstdio>

FT_Library freetypeLibrary;

Engine::Font Engine::Font::LoadFont(const char* path, int face)
{
	Font font;
	font.path = path;
	int error = FT_New_Face(freetypeLibrary, path, face, &font.face);
	if (error == FT_Err_Unknown_File_Format)
	{
		printf("ERROR: unkown file format for font: %s\n", path);
		printf("The font file could be opened and read, but it appears that its font format is unsupported\n");
	}
	else if (error)
	{
	  printf("Could not load font: %s\n", path);
	  printf("Errorcode: %i\n", error);
	}

	font.size = -1; //How the fuck does scaling work ?!?!?!?!
	//I shoul probably read into dpi :(

	return font;
}

void Engine::Font::SetSize(int targetPixelSize)
{
	int size = targetPixelSize;
	int error = FT_Set_Pixel_Sizes(face, targetPixelSize, targetPixelSize);
	if(error)
	{
		printf("SetSize did not work\n");
		printf("Asset: %s\n", path);
		printf("Attempted size: %i\n", targetPixelSize);
		printf("Errorcode: %i\n", error);
	}
}

int Engine::Font::GetSize()
{
	return size;
}

FT_Face Engine::Font::GetFace() const
{
	return face;
}

Engine::Font::~Font()
{
	FT_Done_Face(face);
}