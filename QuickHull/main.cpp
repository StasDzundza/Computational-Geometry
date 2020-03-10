#include "QuickHull.h"

int main(){
    point a[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                 {0, 0}, {1, 2}, {3, 1}, {3, 3},{10,10},{-10,-10},{2,1}};
    int n = sizeof(a)/sizeof(a[0]);
    QuickHull quickHull;
    quickHull.printHull(a, n);
    return 0;
}