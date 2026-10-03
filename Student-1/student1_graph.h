#ifndef STUDENT1_GRAPH_H
#define STUDENT1_GRAPH_H

#define MAX_LOCATIONS 16
#define MAX_LOCATION_NAME 60

typedef struct Edge {
    int dest;
    int distance;
    int trafficFactor;
    struct Edge *next;
} Edge;

typedef struct {
    int locationId;
    char locationName[MAX_LOCATION_NAME];
} Location;

extern Edge *graph[MAX_LOCATIONS];
extern Location locations[MAX_LOCATIONS];
extern int locationCount;

void initializeGraph(void);
void addRoad(int src, int dest, int distance, int traffic);
void loadGraph(void);
void displayLocations(void);
void displayGraph(void);

#endif
