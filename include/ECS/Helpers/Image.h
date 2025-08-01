#pragma once
#include "glm/vec2.hpp"
#include <memory>
#include "ECS/Helpers/Color.h"

namespace Engine
{
	/// @brief Represents image data. The image object is owner of the data and frees the data upon destruction
	class Image
	{
		std::unique_ptr<Engine::Color[]> data; //pixel array, if ctType != NONE, this is actually of type Hall::IndexContainer[]
		short width; //In pixels
		short height; //In pixels
		Hall::CTType ctType; //Color table type

		//This is only needed for Visual Studio compiler, but #ifdef made vs die -_-
		bool wasDataRequested = false;


public:
		Image();
		//Image is responsible for data and will free the data on destruction
		Image(short width, short height, std::unique_ptr<Engine::Color[]> data);
		Image(const char* path);

		short GetWidth() const;
		short GetHeight() const;
		Hall::CTType GetCTType() const;
		Engine::Color* GetData();

#ifdef DESKTOP
		bool GetWasDataRequested() const;
#endif
	};
}