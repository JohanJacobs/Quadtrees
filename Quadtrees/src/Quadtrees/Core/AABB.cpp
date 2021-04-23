#include "AABB.h"
namespace QT
{

	bool AABB::Contains(const Point& point) const
	{
		if ((point.x < minX) || (point.x >= maxX))
			return false;

		if ((point.y < minY) || (point.y >= maxY))
			return false;

		return true;
	}

	bool AABB::Intersect(const AABB& other) const
	{
		return (GetLeft() < other.GetRight() && GetRight() > other.GetLeft() &&
			GetTop() < other.GetBottom() && GetBottom() > other.GetTop());
	}

}
