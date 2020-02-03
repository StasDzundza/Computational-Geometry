#include "PointInPolygon.h"
#include <cmath>

const double PointInPolygon::MIN = numeric_limits<double>::min();
const double PointInPolygon::MAX = numeric_limits<double>::max();

bool PointInPolygon::contains(const Point& p, const Figure& figure)
{
	int number_of_intersections = 0;
	for (auto& edge : figure.edges) {
		if (isIntersectionBetweenRayAndEdge(p, edge))
			number_of_intersections++;
	}
	return (number_of_intersections % 2 == 0) ? false : true;
}

bool PointInPolygon::isIntersectionBetweenRayAndEdge(const Point& p, const Edge& edge)
{
	double m_red, m_blue;
	Point tmp_p = p;
	const Point& a = edge.a, & b = edge.b;
	if (a.y > b.y)
		return isIntersectionBetweenRayAndEdge(p, Edge{ b, a });
	if (pointsIsAlmostEqual(p.y, a.y) || pointsIsAlmostEqual(p.y, b.y))
		return true;
	if (tmp_p.y<a.y || tmp_p.y>b.y)
		return false;
	else if (tmp_p.x >= fmax(a.x, b.x))
		return false;
	else {
		if (tmp_p.x < fmin(a.x, b.x))
			return true;
		else {
			if (!pointsIsAlmostEqual(a.x,b.x))
				m_red = (b.y - a.y) / (b.x - a.x);
			else
				m_red = MAX;
			
			if (!pointsIsAlmostEqual(a.x, tmp_p.x))
				m_blue = (tmp_p.y - a.y) / (tmp_p.x - a.x);
			else
				m_blue = MAX;

			if (pointsIsAlmostEqual(m_blue,m_red))
				return false;
			else
				return m_blue>=m_red;
		}
	}
}

bool PointInPolygon::pointsIsAlmostEqual(const double& x, const double& y)
{
	return abs(x - y) <= numeric_limits<double>::epsilon() * fmax(abs(x), abs(y));
}
