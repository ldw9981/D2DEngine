#pragma once

/*
	  |         +----------------(m_Max.x,m_Max.y)
	  |         |                      |
	  |         |                      |
	  |   (m_Min.x,m_Min.y)------------+
	--+--------------------
*/
class AABB 					
{	
public:
	AABB() : m_Min{0}, m_Max{ 0 } { }
	~AABB() {}
public:
	D2D1_POINT_2F m_Min; // x,y 축에서 작은 값들
	D2D1_POINT_2F m_Max; // x,y 축에서 큰 값들
public:
};

