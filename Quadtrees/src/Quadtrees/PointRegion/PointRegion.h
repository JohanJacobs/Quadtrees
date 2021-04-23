#pragma once
#include "Quadtrees/QTBase.h"
#include "Quadtrees/core/AABB.h"
#include "Quadtrees/core/Point.h"
namespace QT
{
	/*
		https://pvigier.github.io/2019/08/04/quadtree-collision-detection.html
		http://gameprogrammingpatterns.com/spatial-partition.html
		https://stackoverflow.com/questions/41946007/efficient-and-well-explained-implementation-of-a-quadtree-for-2d-collision-det

		The Pattern:
			For a set of objects, each has a position in space, store them in a spatial data structure
			according to their position.This data structure lets you efficiently insert, remove and query
			for objects at or near a location. When a position changes, update the spatial data
			structure so that it can continue to find the object.

		When to Use It:
			When the volume of objects being searched is high enough to impact performance.

		Trade offs:
			Sacrifice memory usage (use more memory) to save some clock cycles (faster lookup). For Smaller list of objects
			the quad tree is not worth it computationally.
	*/

	class PointRegion
	{
	public:
		/* setup quad tree with initial bounds and depth*/
		PointRegion(const AABB& bounds, uint32_t current_depth, uint32_t maximum_depth, uint32_t split_at_count);

		/* add a new point to the current Boundary*/
		void Insert(const Point& point);

		/* return the nodes that is contained in a range */
		std::vector<Point> Query(const AABB& rect) const;

		/* clear the quad tree */
		void Clear();

	private:
		/* indices to keep track of the 4 quadrants */
		enum class QuadSections
		{
			Invalid = -1,
			NorthEast = 0,
			NorthWest = 1,
			SouthEast = 2,
			SouthWest = 3
		};

	private:
		QuadSections GetQuadrant(const Point& point, const AABB& bounds);
		void CreateSubDivisions(const AABB& bounds);
		bool IsLeaf() const;

	private:
		AABB m_Bounds;
		uint32_t m_CurrentDepth;
		uint32_t m_MaxDepth;
		uint32_t m_SplitCount;

		std::vector<Point> m_Data;
		std::array<std::unique_ptr<PointRegion>, 4> m_Children;
	};

}