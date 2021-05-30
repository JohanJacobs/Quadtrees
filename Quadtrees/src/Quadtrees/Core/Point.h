#pragma once
#include "Quadtrees/QTBase.h"
namespace QT
{
	struct Point
	{	
		uint32_t x, y;
		
		Point(uint32_t X, uint32_t Y);

		Point(const Point& other);
		Point() = default;

	};
}