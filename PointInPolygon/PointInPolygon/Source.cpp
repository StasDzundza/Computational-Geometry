#include<iostream>
#include"PointInPolygon.h"

int main() {
	const initializer_list<Point> points = { {10,10}, { 5.0, 5.0}, {0,0}, {-8.0,1.0}, {0.0, 6.0}, {5.0, 6.0} };
	const Figure square = {
		{  {{0.0, 0.0}, {10.0, 0.0}}, {{10.0, 0.0}, {10.0, 10.0}}, {{10.0, 10.0}, {0.0, 10.0}}, {{0.0, 10.0}, {0.0, 0.0}} }
	};
	const Figure triangle = {
		{  {{0.0, 0.0}, {5.0, 10.0}}, 
		{	{5.0, 10.0}, {10.0, 0}},
		{	{10.0, 0}, {0.0, 0.0}}	}
	};
	cout << "square" << endl;
	for (auto& p : points) {
		cout << PointInPolygon::contains(p, square);
	}
	cout << "\ntriangle" << endl;
	for (auto& p : points) {
		cout << PointInPolygon::contains(p, triangle);
	}
	return 0;
}