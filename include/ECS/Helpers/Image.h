#pragma once
#include "glm/vec2.hpp"
#include <memory>
#include "ECS/Helpers/Color.h"

namespace Engine
{
	/// @brief Represents image data. The image object is owner of the data and frees the data upon destruction
	class Image
	{
		enum class Type : char
		{
			TEXTURE,
			CONST_COLOR
		};

		std::unique_ptr<Halib::Color[]> data; //pixel array
		short width; //In pixels
		short height; //In pixels
		Halib::Color color;
		Type type;

		//This is only needed for Visual Studio compiler, but #define if made vs die -_-
		bool wasDataRequested = false;


public:
		Image();
		//Image is responsible for data and will free the data on destruction
		Image(short width, short height, std::unique_ptr<Halib::Color[]> data);
		Image(const char* path);

		/// @brief Instantiates a rectangle with given width and height and given color
		/// @param width 
		/// @param height 
		/// @param color 
		Image(short width, short height, Halib::Color color);

		short GetWidth() const;
		short GetHeight() const;
		Halib::Color* GetData();
		bool IsConstColor() const;
		bool IsTexture() const;
		Halib::Color GetColor() const;

#ifdef DESKTOP
		bool GetWasDataRequested() const;
#endif
	};
}