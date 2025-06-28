#pragma once
#include <Hall/Hall.h>

namespace Halib
{
	struct Image
	{
		const short width; //In pixels
		const short height; //In pixels
		const Hall::Color* data; //pixel array

		Image();

		//Image is responsible for data and will free the data on destruction
		Image(short width, short height, Hall::Color* data);
		Image(const char* path);

		~Image();
	}
}