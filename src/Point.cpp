#include "Point.h"

namespace joblevel
{

const Point Point::NULL_POINT;

Point::Point()
	: m_x(-1), m_y(-1) 
{
}

Point::Point(int x, int y)
	: m_x(x), m_y(y)
{
}

int Point::x() const
{
	return m_x;
}

void Point::x(int newX)
{
	m_x = newX;
}

int Point::y() const
{
	return m_y;
}

void Point::y(int newY)
{
	m_y = newY;
}

bool Point::operator==(const Point& rhs) const
{
	return m_x == rhs.m_x && m_y == rhs.m_y;
}

bool Point::operator<(const Point& rhs) const
{
	return m_x < rhs.m_x || 
		   (m_x == rhs.m_x && m_y < rhs.m_y);
}

}
