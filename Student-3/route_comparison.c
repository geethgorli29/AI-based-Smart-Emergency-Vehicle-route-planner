#include <stdio.h>
#include "route_comparison.h"

void compareRoutes(int distance1, int distance2)
{
    printf("Route 1 cost: %d\n", distance1);
    printf("Route 2 cost: %d\n", distance2);

    if (distance1 == distance2)
        printf("Both routes have the same cost.\n");
    else if (distance1 < distance2)
        printf("Route 1 is better (lower by %d).\n", distance2 - distance1);
    else
        printf("Route 2 is better (lower by %d).\n", distance1 - distance2);
}
