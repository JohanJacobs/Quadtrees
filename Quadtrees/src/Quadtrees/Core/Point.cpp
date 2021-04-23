#include "Point.h"

namespace QT
{
	Point::Point(const Point& other) : x(other.x), y(other.y)
	{

	}

	Point::Point(uint32_t X, uint32_t Y) : x(X), y(Y)
	{

	}

}