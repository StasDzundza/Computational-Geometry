#pragma once
#include"Figure.h"
#include<limits>
using namespace std;

class PointInPolygon {
public:
	static bool contains(const Point& p,const Figure& figure);
	static bool contains2(const Point& p,const Figure& figure);
private:
	static bool isIntersectionBetweenRayAndEdge(const Point& p, const Edge& e);
	static int isIntersectionBetweenRayAndEdge2(const Point& p, const Edge& e);
	static bool pointsIsAlmostEqual(const double& x, const double& y);
	static const double MIN;
	static const double MAX;
};

