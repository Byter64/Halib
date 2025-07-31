#include "Halib/Graphic/Tilemap.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include "Halib/Graphic/Render.h"

Halib::Tilemap::Tilemap()
{
	indices = std::vector<std::vector<std::tuple<int, int>>>();
	sprite = Sprite();
}

Halib::Tilemap::Tilemap(const char* graphicPath, VecI2 graphicTileCount, const char* tilemapPath)
{
	sprite = Sprite(graphicPath, graphicTileCount);

	std::ifstream fileStream(tilemapPath);
	nlohmann::json jsonData = nlohmann::json::parse(fileStream);
	indices = jsonData.get<std::vector<std::vector<std::tuple<int, int>>>>();
}

void  Halib::Tilemap::SetTile(VecI2 position, VecI2 newTile)
{
	indices[position.y][position.x] = std::tuple(newTile.x, newTile.y);
}

Halib::VecI2 Halib::Tilemap::GetTile(VecI2 position)
{
	std::tuple<int, int> tile = indices[position.y][position.x];
	return VecI2(std::get<0>(tile), std::get<1>(tile));
}

Halib::VecI2 Halib::Tilemap::GetSize()
{
	return VecI2(indices[0].size(), indices.size());
}

void Halib::Tilemap::Draw()
{
	Halib::Draw(*this, VecI2(0, 0));
}

void Halib::Tilemap::Draw(const Camera& camera)
{
	Halib::Draw(*this, camera);
}