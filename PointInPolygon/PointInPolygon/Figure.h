#pragma once
#include<initializer_list>
#include<algorithm>
#include<limits>
using namespace std;

struct Point
{
	double x, y;
	bool operator ==(const Point& rhs) const {
		return pointsIsAlmostEqual(x, rhs.x) && pointsIsAlmostEqual(y, rhs.y);
	}

	static bool pointsIsAlmostEqual(const double& x, const double& y) {
		return abs(x - y) <= numeric_limits<double>::epsilon() * max(abs(x), abs(y));
	}
};

struct Edge
{
	Point a, b;
};

struct Figure {
	std::initializer_list<Edge> edges;
};

