#include "Graphic/Font.h"
#include <cstdio>

FT_Library freetypeLibrary;

Halib::Font::Font(const char* path, int face)
{
	this->path = path;
	int error = FT_New_Face(freetypeLibrary, path, face, &this->face);
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
}

void Halib::Font::SetSize(int targetPixelSize)
{
	int error = FT_Set_Pixel_Sizes(face, targetPixelSize, targetPixelSize);
	if(error)
	{
		printf("SetSize did not work\n");
		printf("Asset: %s\n", path);
		printf("Attempted size: %i\n", targetPixelSize);
		printf("Errorcode: %i\n", error);
	}
}