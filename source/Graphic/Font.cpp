#include "Graphic/Font.h"
#include <cstdio>

FT_Library freetypeLibrary;

Halib::Font::Font(const char* path, int face)
{
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