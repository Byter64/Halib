#include "Halib/Graphic/Rect.h"
#include "Halib/Entity.h"
#include "Halib/Math/Vec.h"

Halib::Rect::Rect(VecI2 position, VecI2 size, Halib::Color color) : Halib::Entity(Halib::Sprite(size.x, size.y, color), Halib::Vec3(position, 0))
{

}

void Halib::Rect::Update(float deltaTime)
{

}