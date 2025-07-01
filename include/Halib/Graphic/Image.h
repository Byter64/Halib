#pragma once
#include "Halib/VecI2.h"
#include <memory>
#include "Halib/Graphic/Color.h"

namespace Halib
{
	/// @brief Represents image data. The image object is owner of the data and frees the data upon destruction
	class Image
	{
		short width; //In pixels
		short height; //In pixels
		std::unique_ptr<Halib::Color[]> data; //pixel array
#ifdef DESKTOP
		bool wasDataRequested = false;
#endif

public:
		Image();
		//Image is responsible for data and will free the data on destruction
		Image(short width, short height, std::unique_ptr<Halib::Color[]> data);
		Image(const char* path);

		short GetWidth() const;
		short GetHeight() const;
		Halib::Color* GetData();

#ifdef DESKTOP
		bool GetWasDataRequested() const;
#endif
	};
}