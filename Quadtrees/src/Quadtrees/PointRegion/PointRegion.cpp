#include "PointRegion.h"

namespace QT
{	             
	PointRegion::PointRegion(const AABB &bounds, uint32_t current_depth, uint32_t maximum_depth, uint32_t split_at_count)
		:m_Bounds(bounds), m_CurrentDepth(current_depth), m_MaxDepth(maximum_depth), m_SplitCount(split_at_count)
	{    }

	void PointRegion::Insert(const Point& point)
	{
		if (!m_Bounds.Contains(point))
		{
			return;
		}

		if (IsLeaf())
		{
			if (m_Data.size() < m_SplitCount)
				m_Data.push_back(point);// there is space in this layer, add the point		
			else
			{
				/* Capacity is full, create the quadrants*/
				if (m_CurrentDepth < m_MaxDepth)
				{
					/* can split it in smaller segments*/
					CreateSubDivisions(m_Bounds);

					// add the data points 			
					m_Data.push_back(point); // adding the data point so it can be re-distributed to the correct group
					for (auto& point : m_Data)
					{
						QuadSections idx = GetQuadrant(point, m_Bounds);
						if (idx != QuadSections::Invalid)
							m_Children[static_cast<size_t>(idx)]->Insert(point);
						else
						{			
							__debugbreak();							
						}
					}
					m_Data.clear();
				}
				else
				{
					/* max depth reached so have to just add more data nodes */
					m_Data.push_back(point);
				}
			}
		}
		else
		{
			// find which quadrant this belongs too and insert
			auto quadrant = GetQuadrant(point, m_Bounds);
			m_Children[static_cast<std::size_t>(quadrant)]->Insert(point);
		}
	}

	std::vector<QT::Point> PointRegion::Query(const AABB& rect) const
	{
		std::vector<Point> values;
		if (IsLeaf())
		{
			// check the data points of the leaf if they intersect with the rect;
			for (const Point& c : m_Data)
			{
				if (rect.Contains(c))
					values.push_back(c);
			}
		}
		else
		{
			// iterate through children
			for (const auto& c : m_Children)
			{
				if (c->m_Bounds.Intersect(rect))
				{
					auto result = c->Query(rect);
					values.insert(values.end(), result.begin(), result.end());
				}
			}
		}
		return values;
	}

	/* Clear the quad tree.	*/
	void PointRegion::Clear()
	{
		if (IsLeaf())
		{
			m_Data.clear();
		}
		else
		{
			for (auto& child : m_Children)
				child.reset();

		}
	}

	/* determines which of the Quadrant a point belongs too */
	PointRegion::QuadSections PointRegion::GetQuadrant(const Point& point, const AABB& bounds)
	{
		uint16_t midX = bounds.GetLeft() + bounds.GetWidth() / 2;
		uint16_t midY = bounds.GetTop() + bounds.GetHeight() / 2;
		if (point.y < midY)
		{
			// north
			if (point.x >= midX)
			{
				return QuadSections::NorthEast;// east			
			}
			else if (point.x < midX)
			{
				return QuadSections::NorthWest;//west 
			}
		}
		else if (point.y >= midY)
		{
			//south
			if (point.x >= midX)
			{
				return QuadSections::SouthEast;// east
			}
			else if (point.x < midX)
			{
				return QuadSections::SouthWest;//west 
			}
		}
		return QuadSections::Invalid;
	}

	/* creates 4 subregions from the a given bounds (square) */
	void PointRegion::CreateSubDivisions(const AABB& bounds)
	{
		uint16_t hWidth = m_Bounds.GetWidth() / 2;
		uint16_t hHeight = m_Bounds.GetHeight() / 2;

		/* calculate the bounds for each quadrant */
		AABB NorthWestRect(m_Bounds.GetLeft(), m_Bounds.GetTop(), m_Bounds.GetLeft() + hWidth, m_Bounds.GetTop() + hHeight);
		AABB NorthEastRect(m_Bounds.GetLeft() + hWidth, m_Bounds.GetTop(), m_Bounds.GetRight(), m_Bounds.GetTop() + hHeight);
		AABB SouthWestRect(m_Bounds.GetLeft(), m_Bounds.GetTop() + hHeight, m_Bounds.GetLeft() + hWidth, m_Bounds.GetBottom());
		AABB SouthEastRect(m_Bounds.GetLeft() + hWidth, m_Bounds.GetTop() + hHeight, m_Bounds.GetRight(), m_Bounds.GetBottom());

		//create the regions
		m_Children[std::size_t(QuadSections::NorthEast)] = std::move(std::make_unique<PointRegion>(NorthEastRect, m_CurrentDepth + 1, m_MaxDepth, m_SplitCount));

		m_Children[std::size_t(QuadSections::NorthWest)] = std::move(std::make_unique<PointRegion>(NorthWestRect, m_CurrentDepth + 1, m_MaxDepth, m_SplitCount));
		m_Children[std::size_t(QuadSections::SouthEast)] = std::move(std::make_unique<PointRegion>(SouthEastRect, m_CurrentDepth + 1, m_MaxDepth, m_SplitCount));
		m_Children[std::size_t(QuadSections::SouthWest)] = std::move(std::make_unique<PointRegion>(SouthWestRect, m_CurrentDepth + 1, m_MaxDepth, m_SplitCount));

	}

	/* determine if this node is a leaf*/
	bool PointRegion::IsLeaf() const
	{
		return !static_cast<bool>(m_Children[0]);
	}
}