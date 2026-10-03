#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#define MAX_VERTICES 100
#define MAX_LOCATION_NAME 50
#define INF 9999

typedef struct DNode {
    int destination;
    int distance;
    int traffic;
    int trafficWeight;
    struct DNode *next;
} DNode;

typedef struct {
    int vertices;
    DNode *adjList[MAX_VERTICES];
} Graph;

void initGraph(Graph *graph, int vertices);

int addRoad(Graph *graph, int source, int destination, int distance);

int addRoadWithTraffic(Graph *graph, int source, int destination,
                       int distance, int traffic);

int getEffectiveRoadCost(const DNode *node);

void dijkstra(Graph *graph, int source, int destination);

#endif
