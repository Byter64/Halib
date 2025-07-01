#include "Halib/System.h"
#include <Hall/Hall.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <cstdio>

//Defined in Font.cpp
extern FT_Library freetypeLibrary;

void Halib::Init()
{
	Hall::Init();
	int error = FT_Init_FreeType(&freetypeLibrary);
	if(error)
	{
		printf("FreeType init failed\n");
		printf("Text will not be available\n");
		printf("Error code: %i\n", error);
	}
}

bool Halib::GetShouldClose()
{
	return Hall::ShouldClose();
}

float Halib::GetTimeSinceStartup()
{
	return Hall::GetSystemTime() / (float)Hall::SYSTEM_CLK_FREQUENCY;
}