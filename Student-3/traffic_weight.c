#include "traffic_weight.h"

/* Traffic levels: 1 = Low, 2 = Medium, 3 = High. Returns -1 if invalid. */
int calculateTrafficWeight(int traffic)
{
    switch (traffic) {
    case 1:  return 0;
    case 2:  return 2;
    case 3:  return 4;
    default: return -1;
    }
}

int calculateRoadCost(int distance, int traffic)
{
    int weight = calculateTrafficWeight(traffic);

    if (distance <= 0 || weight < 0)
        return -1;

    return distance + weight;
}
