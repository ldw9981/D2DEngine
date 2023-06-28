#pragma once

/*                         
	  |         +----------------------max
	  |         |                      |
	  |         |		 center        |
	  |	        |          +           |
	  |         |                      |
	  |         |                      |
	  |         min--------------------+
	--+--------------------
*/
class AABB 					
{	
public:
	AABB() : m_Center{0}, m_Extend{ 0 } { }
	~AABB() {}
public:
	D2D1_VECTOR_2F m_Center; // 중앙
	D2D1_VECTOR_2F m_Extend; // x,y축 확장값	
	// minX = m_Center.x - m_Extend.x
	// maxX = m_Center.x + m_Extend.x
	// minY = m_Center.y - m_Extend.y
	// maxY = m_Center.y + m_Extend.y

	bool CheckIntersect(const AABB& other) const
	{
		// self min,max
		float S_MinX = m_Center.x - m_Extend.x;
		float S_MaxX = m_Center.x + m_Extend.x;
		float S_MinY = m_Center.y - m_Extend.y;
		float S_MaxY = m_Center.y + m_Extend.y;

		// other min,max
		float O_MinX = other.m_Center.x - other.m_Extend.x;
		float O_MaxX = other.m_Center.x + other.m_Extend.x;
		float O_MinY = other.m_Center.y - other.m_Extend.y;
		float O_MaxY = other.m_Center.y + other.m_Extend.y;

		if(S_MinX <= O_MaxX && S_MaxX >= O_MinX && S_MinY <= O_MaxY && S_MaxY >= O_MinY)
			return true;
		
		return false;
	}
};

