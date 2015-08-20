#ifndef JL_POINT_H
#define JL_POINT_H

namespace joblevel
{

class Point
{
public:
	static const Point NULL_POINT;

	Point();
	Point(int x, int y);
	int x() const;
	void x(int newX);
	int y() const;
	void y(int newY);
	bool operator==(const Point& rhs) const;
	bool operator<(const Point& rhs) const;

private:	
	int m_x;
	int m_y;
};

}

#endif
