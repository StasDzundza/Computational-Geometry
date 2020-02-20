#include "PointInPolygon.h"
#include <cmath>
#include <algorithm>

const double PointInPolygon::MIN = numeric_limits<double>::min();
const double PointInPolygon::MAX = numeric_limits<double>::max();

int PointInPolygon::isIntersectionBetweenRayAndEdge2(const Point& p, const Edge& edge) {
	const auto& a = edge.a, & b = edge.b;
	if (a.y > b.y)
		return isIntersectionBetweenRayAndEdge2(p, Edge{ b, a });
	else if (p == a || p == b)
		return 0;
	else if (Point::pointsIsAlmostEqual(p.y, a.y) || Point::pointsIsAlmostEqual(p.y, b.y))
		return isIntersectionBetweenRayAndEdge2({ p.x, p.y + numeric_limits<float>::epsilon() * abs(p.y) }, edge);
	else if (p.y > b.y || p.y < a.y || p.x > max(a.x, b.x))
		return -1;
	else if (p.x < min(a.x, b.x))
		return 1;
	else {
		auto blue_angle = !Point::pointsIsAlmostEqual(a.x, p.x) ? (p.y - a.y) / (p.x - a.x) : MAX;
		auto red_angle = !Point::pointsIsAlmostEqual(a.x, b.x) ? (b.y - a.y) / (b.x - a.x) : MAX;
		return Point::pointsIsAlmostEqual(blue_angle, red_angle) ? 0 : blue_angle >= red_angle ? 1 : -1;
	}
}

bool PointInPolygon::contains2(const Point& p, const Figure& figure)
{
	bool c = 0;
	for (auto& e : figure.edges) {
		int intersects = isIntersectionBetweenRayAndEdge2(p, e);
		if (intersects == 1)
			c = !c;
		else if (!intersects)
			return true;
	}
	return c;
}

