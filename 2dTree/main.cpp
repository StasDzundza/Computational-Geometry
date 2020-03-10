#include <iostream>
#include "TwoDimensionalDTree.h"

int main() {
    TwoDimensionalDTree t;
    int points[][2] = {{3,  6},
                       {17, 15},
                       {13, 15},
                       {6,  12},
                       {9,  1},
                       {2,  7},
                       {10, 19}};

    int n = sizeof(points) / sizeof(points[0]);

    for (int i = 0; i < n; i++)
        t.insert(points[i]);

    std::vector<std::pair<int, int>> points_in_area = t.findPointsInArea(0, 14, 10, 2);
    for (auto &point : points_in_area) {
        std::cout << point.first << " " << point.second << std::endl;
    }

    return 0;
}
