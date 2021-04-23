#include <iostream>
#include "Quadtrees\Quadtrees.h"
#include "Utils.h"
int main()
{
	uint32_t max_depth = 5;
	uint32_t points_before_split = 50;
	uint32_t minX = 0, maxX = 1000;
	uint32_t minY = 0, maxY = 1000;	
	std::size_t point_count = 1000000;
	
	std::cout << "Creating point_region Quadtree\n";

	QT::PointRegion pr(QT::AABB(minX, minY, maxX, maxY), 0, max_depth, points_before_split);		

	{
		std::cout << "Populating 1 million random values : ";
				
		for (std::size_t i = 0; i < point_count; i++)
		{
			uint32_t x = UTILS::Random::get<uint32_t>(minX, maxX);
			uint32_t y = UTILS::Random::get<uint32_t>(minY, maxY);
			pr.Insert(QT::Point(x, y));
		}
		std::cout << " Done\n";
	}

	{
		std::cout << "Get all nodes in a bounds: ";
		auto values = pr.Query(QT::AABB(100, 100, 200, 200));
		std::cout << values.size() << "\n";
	}
	return 0;
}