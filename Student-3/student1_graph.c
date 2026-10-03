/*
 * STUDENT 1 DATA INTEGRATION MODULE
 * FINAL DATA SUPPLIED BY STUDENT 1
 *
 * Each road is listed only once below. addRoadWithTraffic() automatically
 * creates both directions in the adjacency list.
 * Traffic: 1 = Low, 2 = Medium, 3 = High.
 */

#include <string.h>
#include "student1_graph.h"

typedef struct {
    int id;
    const char *name;
} Student1Location;

typedef struct {
    int source;
    int destination;
    int distance;
    int traffic;
} Student1Road;

static const Student1Location student1Locations[] = {
    {0, "Dwaraka Nagar RTC Complex"},
    {1, "Visakhapatnam Railway Station"},
    {2, "Jagadamba Junction"},
    {3, "King George Hospital (KGH)"},
    {4, "RK Beach"},
    {5, "Kailasagiri"},
    {6, "Andhra University"},
    {7, "MVP Colony"},
    {8, "Rushikonda Beach"},
    {9, "Visakhapatnam Airport"},
    {10, "Gajuwaka"},
    {11, "Simhachalam Temple"},
    {12, "NAD Junction"},
    {13, "Gopalapatnam"},
    {14, "SevenHills Hospital"},
    {15, "CARE Hospitals, Ramnagar"}
};

static const Student1Road student1Roads[] = {
    {0, 1, 4, 2},
    {0, 2, 3, 3},
    {0, 12, 7, 2},
    {1, 2, 4, 2},
    {1, 9, 14, 2},
    {2, 3, 2, 3},
    {2, 4, 2, 2},
    {2, 14, 3, 2},
    {3, 4, 2, 2},
    {3, 15, 3, 3},
    {4, 5, 6, 2},
    {4, 6, 5, 2},
    {4, 7, 5, 3},
    {5, 6, 7, 2},
    {5, 7, 5, 2},
    {6, 7, 4, 2},
    {7, 8, 8, 3},
    {8, 9, 18, 2},
    {8, 10, 20, 3},
    {9, 12, 8, 3},
    {10, 12, 12, 2},
    {10, 13, 10, 2},
    {11, 12, 6, 2},
    {11, 13, 5, 2},
    {12, 13, 4, 3},
    {13, 1, 8, 2},
    {14, 15, 4, 2}
};

#define STUDENT1_LOCATION_COUNT \
    ((int)(sizeof(student1Locations) / sizeof(student1Locations[0])))

#define STUDENT1_ROAD_COUNT \
    ((int)(sizeof(student1Roads) / sizeof(student1Roads[0])))

int loadStudent1Graph(Graph *graph,
                      char locationNames[][MAX_LOCATION_NAME],
                      int *locationCount,
                      int *roadCount)
{
    int i;

    if (STUDENT1_LOCATION_COUNT < 1 ||
        STUDENT1_LOCATION_COUNT > MAX_VERTICES) {
        return 0;
    }

    initGraph(graph, STUDENT1_LOCATION_COUNT);

    for (i = 0; i < STUDENT1_LOCATION_COUNT; i++) {
        strncpy(locationNames[i],
                student1Locations[i].name,
                MAX_LOCATION_NAME - 1);
        locationNames[i][MAX_LOCATION_NAME - 1] = '\0';
    }

    for (i = 0; i < STUDENT1_ROAD_COUNT; i++) {
        if (!addRoadWithTraffic(graph,
                                student1Roads[i].source,
                                student1Roads[i].destination,
                                student1Roads[i].distance,
                                student1Roads[i].traffic)) {
            return 0;
        }
    }

    *locationCount = STUDENT1_LOCATION_COUNT;
    *roadCount = STUDENT1_ROAD_COUNT;
    return 1;
}
