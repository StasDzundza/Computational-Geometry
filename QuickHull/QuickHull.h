//
// Created by stas on 04.03.2020.
//

#ifndef QUICKHULL_QUICKHULL_H
#define QUICKHULL_QUICKHULL_H

#include <set>
#include <utility>

typedef std::pair<int, int> point;

class QuickHull {
public:
    void printHull(point a[], int n);

private:
    // Stores the result (points of convex hull)
    std::set<point> hull;

    int findSide(point p1, point p2, point p);

    int lineDist(point p1, point p2, point p);

    void quickHull(point a[], int n, point p1, point p2, int side);
};


#endif //QUICKHULL_QUICKHULL_H
