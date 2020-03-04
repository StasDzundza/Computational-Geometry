#include "QuickHull.h"

// Driver code
int main()
{
    point a[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                 {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    int n = sizeof(a)/sizeof(a[0]);
    QuickHull quickHull;
    quickHull.printHull(a, n);
    return 0;
}