#pragma once
#include "Quadtrees/QTBase.h"
#include <cstdint>
#include <cmath>
#include "Point.h"
namespace QT
{
	struct AABB
	{
		uint32_t minX, minY, maxX, maxY;

		AABB(uint32_t TopLeftX, uint32_t TopLeftY, uint32_t BottomRightX, uint32_t BottomRightY)
			:minX(TopLeftX), minY(TopLeftY), maxX(BottomRightX), maxY(BottomRightY)
		{   }

		AABB(const AABB& other)
			: minX(other.minX), minY(other.minY), maxX(other.maxX), maxY(other.maxY)
		{   }

		bool Contains(const Point& point) const;

		/* test if two rectangles overlap
			https://silentmatt.com/rectangle-intersection/
			https://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other
		*/
		bool Intersect(const AABB& other) const;

		inline uint32_t GetLeft()   const { return minX; }
		inline uint32_t GetRight()  const { return maxX; }
		inline uint32_t GetTop()    const { return minY; }
		inline uint32_t GetBottom() const { return maxY; }

		inline uint32_t GetWidth()  const { return (int)(maxX - minX); }
		inline uint32_t GetHeight() const { return (int)(maxY - minY); }

	};
}