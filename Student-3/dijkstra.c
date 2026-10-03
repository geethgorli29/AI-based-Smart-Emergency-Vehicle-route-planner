#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"
#include "traffic_weight.h"

void initGraph(Graph *graph, int vertices)
{
    int i;

    graph->vertices = vertices;
    for (i = 0; i < MAX_VERTICES; i++)
        graph->adjList[i] = NULL;
}

/* Adds one directed edge at the front of source's list. */
static int addDirectedEdge(Graph *graph, int from, int to,
                           int distance, int traffic)
{
    DNode *node = (DNode *)malloc(sizeof(DNode));

    if (node == NULL)
        return 0;

    node->destination = to;
    node->distance = distance;
    node->traffic = traffic;
    node->trafficWeight = calculateTrafficWeight(traffic);
    node->next = graph->adjList[from];
    graph->adjList[from] = node;
    return 1;
}

int addRoadWithTraffic(Graph *graph, int source, int destination,
                       int distance, int traffic)
{
    if (source < 0 || source >= graph->vertices ||
        destination < 0 || destination >= graph->vertices)
        return 0;

    if (distance <= 0 || calculateTrafficWeight(traffic) < 0)
        return 0;

    /* Roads are two-way, so store both directions. */
    return addDirectedEdge(graph, source, destination, distance, traffic) &&
           addDirectedEdge(graph, destination, source, distance, traffic);
}

/* A road added without traffic information is treated as low traffic. */
int addRoad(Graph *graph, int source, int destination, int distance)
{
    return addRoadWithTraffic(graph, source, destination, distance, 1);
}

int getEffectiveRoadCost(const DNode *node)
{
    return node->distance + node->trafficWeight;
}

static void printPath(const int parent[], int node)
{
    if (parent[node] != -1) {
        printPath(parent, parent[node]);
        printf(" -> ");
    }
    printf("%d", node);
}

void dijkstra(Graph *graph, int source, int destination)
{
    int cost[MAX_VERTICES];
    int done[MAX_VERTICES];
    int parent[MAX_VERTICES];
    int i, round, best, u;
    DNode *edge;

    for (i = 0; i < graph->vertices; i++) {
        cost[i] = INF;
        done[i] = 0;
        parent[i] = -1;
    }
    cost[source] = 0;

    for (round = 0; round < graph->vertices; round++) {
        u = -1;
        best = INF;

        for (i = 0; i < graph->vertices; i++) {
            if (!done[i] && cost[i] < best) {
                best = cost[i];
                u = i;
            }
        }

        if (u == -1 || u == destination)
            break;

        done[u] = 1;

        for (edge = graph->adjList[u]; edge != NULL; edge = edge->next) {
            int newCost = cost[u] + getEffectiveRoadCost(edge);

            if (newCost < cost[edge->destination]) {
                cost[edge->destination] = newCost;
                parent[edge->destination] = u;
            }
        }
    }

    if (cost[destination] >= INF) {
        printf("No route found.\n");
        return;
    }

    printf("Best route cost (distance + traffic): %d\n", cost[destination]);
    printf("Route: ");
    printPath(parent, destination);
    printf("\n");
}
