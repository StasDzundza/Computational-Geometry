#pragma once
#include"Figure.h"

class PointInPolygon {
public:
	static bool contains2(const Point& p,const Figure& figure);
private:
	static int isIntersectionBetweenRayAndEdge2(const Point& p, const Edge& e);
	static const double MIN;
	static const double MAX;
};

