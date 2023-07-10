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
		float minBox1X = m_Center.x - m_Extend.x;
		float maxBox1X = m_Center.x + m_Extend.x;
		float minBox1Y = m_Center.y - m_Extend.y;
		float maxBox1Y = m_Center.y + m_Extend.y;

		// other min,max
		float minBox2X = other.m_Center.x - other.m_Extend.x;
		float maxBox2X = other.m_Center.x + other.m_Extend.x;
		float minBox2Y = other.m_Center.y - other.m_Extend.y;
		float maxBox2Y = other.m_Center.y + other.m_Extend.y;

		// Check for no overlap conditions
		if (maxBox1X < minBox2X || minBox1X > maxBox2X || maxBox1Y < minBox2Y || minBox1Y > maxBox2Y) {
			return false;
		}

		return true;

	}
};

