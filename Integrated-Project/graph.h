#ifndef GRAPH_H
#define GRAPH_H

#include "structures.h"

double trafficWeight(int traffic);
const char *trafficName(int traffic);

void initializeGraph(Graph *g);
int getLocation(Graph *g, const char name[]);
void addEdge(Graph *g, int from, int to, double distance, int traffic);
void addRoad(Graph *g, int from, int to, double distance, int traffic);

void dijkstra(Graph *g, int source, int destination,
              double dist[], int parent[]);

void displayRoute(Graph *g, int destination, int parent[]);

void routeInformation(Graph *g, int source, int destination,
                      int parent[], double *distance,
                      double *trafficIndex, int *hasMedium,
                      int *hasHigh);

void displayTraffic(int hasMedium, int hasHigh, double trafficIndex);

double predictTravelTime(double distance, double trafficIndex);

#endif
