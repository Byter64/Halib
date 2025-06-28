#pragma once
#include <Hall/Hall.h>

namespace Halib
{
	class Image
	{
		short width; //In pixels
		short height; //In pixels
		Hall::Color* data; //pixel array

public:
		Image();
		//Image is responsible for data and will free the data on destruction
		Image(short width, short height, Hall::Color* data);
		Image(const char* path);

		~Image();
	};
}