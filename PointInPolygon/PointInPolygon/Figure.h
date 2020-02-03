#pragma once
#include<initializer_list>

struct Point
{
	double x, y;
};

struct Edge
{
	Point a, b;
};

struct Figure {
	std::initializer_list<Edge> edges;
};