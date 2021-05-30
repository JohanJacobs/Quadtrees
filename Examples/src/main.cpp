#include <iostream>
#include "Quadtrees\Quadtrees.h"
#include "RandomNumbers.h"
#include "SimpleTimer.h"

int main()
{
	uint32_t max_depth = 5;				// maximum depth that the quad tree will create
	uint32_t points_before_split = 50;	// How many points must be within a node before the node splits 
	uint32_t minX = 0, maxX = 1000;		// width of bounding box 
	uint32_t minY = 0, maxY = 1000;		// height of bounding box 
	std::size_t point_count = 100000000;// how many points we will create 

	/* construct a vector of random numbers */
	std::vector<QT::Point> data(point_count);	

	std::cout << "Creating "<<point_count <<" random values : \n";				
	for (std::size_t i = 0; i < point_count; i++)
	{
		uint32_t x = RandomNumbers::get<uint32_t>(minX, maxX);
		uint32_t y = RandomNumbers::get<uint32_t>(minY, maxY);
		data.push_back(QT::Point(x, y));
	}		
	
	std::cout << "Creating point_region Quad Tree\n";
	/* construct a point region Qaudtree with the initial settings */
	QT::PointRegion pr(QT::AABB(minX, minY, maxX, maxY), 0, max_depth, points_before_split); 
	// add values to Quad tree data structure 
	for (auto& p : data)
	{
		pr.Insert(p);
	}

	/* 
		query the quad tree data structure to get the count of points 
	*/
	std::cout << "Query specific region of the Quad Tree : \n";
	std::size_t values = 0;
	{
		SimpleTimer timer("Query Quad Tree");
		values = pr.Query(QT::AABB(100, 100, 200, 200)).size();
	}
	std::cout << "Total: " << values << "\n";

	/* 
		linear search time through std::vector 
	*/
	std::cout << "\n\nQuery specific region of std::vector : \n";
	QT::AABB rect(100, 100, 200, 200);
	values = 0;
	{
		SimpleTimer timer("Query vector");
		for (const auto& v : data)
			if (rect.Contains(v))
					values += 1;
	}
	std::cout << "Total: " << values << "\n";
	return 0;
}