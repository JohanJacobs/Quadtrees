#include <iostream>
#include "Quadtrees\Quadtrees.h"
#include "Utils.h"
int main()
{
	uint32_t max_depth = 5;
	uint32_t points_before_split = 50;
	uint32_t minX = 0, maxX = 0;
	uint32_t minY = 0, maxY = 0;	
	std::size_t point_count = 5000000;
	
	ULOG_INFO("Creating point_region Quadtree");
	QT::PointRegion pr(QT::AABB(minX, minY, maxX, maxY), 0, max_depth, points_before_split);

	{
		UTILS::Timer timer1("Populating QT::PointRegion ");
		for (std::size_t i = 0; i < point_count; i++)
		{
			uint32_t x = UTILS::Random::get<uint32_t>(minX, maxX);
			uint32_t y = UTILS::Random::get<uint32_t>(minY, maxY);
			pr.Insert(QT::Point(x, y));
		}
	}
	return 0;
}