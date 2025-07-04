#pragma once
#include <vector>
#include "Halib/Math/Vec.h"
#include "Halib/Graphic/Sprite.h"

namespace Halib
{
	/// @brief The center is (0, 0). If indices outside its size are requested, the tile indices are clamped Consider loading the image into the fast ram!
	class Tilemap
	{
		std::vector<std::vector<std::tuple<int, int>>> indices;
		
public:
		Sprite sprite;
		struct TilemapSerialized
		{
			std::vector<std::vector<std::tuple<int, int>>> map;
		};

		Tilemap();

		/// @brief 
		/// @param graphicPath 
		/// @param graphicTileCount The number of tiles in x and y direction of the graphic
		/// @param tilemapPath A json formated 2D array of coordinates
		Tilemap(const char* graphicPath, VecI2 graphicTileCount, const char* tilemapPath);

		void SetTile(VecI2 position, VecI2 newTile);
		VecI2 GetTile(VecI2 position);

		void Draw();
		void Draw(const Camera& camera);

	};
} // namespace Halib
