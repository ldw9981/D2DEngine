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
	D2D1_VECTOR_2F m_Center; // �߾�
	D2D1_VECTOR_2F m_Extend; // x,y�� Ȯ�尪
	// minX = m_Center.x - m_Extend.x
	// maxX = m_Center.x + m_Extend.x
	// minY = m_Center.y - m_Extend.y
	// maxY = m_Center.y + m_Extend.y
public:
};

