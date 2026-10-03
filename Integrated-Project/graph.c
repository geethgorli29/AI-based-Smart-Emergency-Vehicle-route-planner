#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

/* =========================
   TRAFFIC WEIGHT
   ========================= */
double trafficWeight(int traffic)
{
    if (traffic == 1)
        return 0.0;   /* Low */

    if (traffic == 2)
        return 3.0;   /* Medium */

    if (traffic == 3)
        return 6.0;   /* High */

    return 0.0;
}

/* =========================
   TRAFFIC NAME
   ========================= */
const char *trafficName(int traffic)
{
    if (traffic == 1)
        return "Low";

    if (traffic == 2)
        return "Medium";

    if (traffic == 3)
        return "High";

    return "Unknown";
}

/* =========================
   INITIALIZE GRAPH
   ========================= */
void initializeGraph(Graph *g)
{
    int i;

    g->count = 0;

    for (i = 0; i < MAX_LOCATIONS; i++)
        g->adj[i] = NULL;
}

/* =========================
   GET LOCATION
   ========================= */
int getLocation(Graph *g, const char name[])
{
    int i;

    for (i = 0; i < g->count; i++)
    {
        if (strcmp(g->name[i], name) == 0)
            return i;
    }

    if (g->count >= MAX_LOCATIONS)
        return -1;

    strcpy(g->name[g->count], name);
    g->count++;

    return g->count - 1;
}

/* =========================
   ADD EDGE
   ========================= */
void addEdge(Graph *g, int from, int to,
             double distance, int traffic)
{
    Node *newNode;

    newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    newNode->destination = to;
    newNode->distance = distance;
    newNode->traffic = traffic;
    newNode->next = g->adj[from];

    g->adj[from] = newNode;
}

/* =========================
   ADD ROAD
   ========================= */
void addRoad(Graph *g, int from, int to,
             double distance, int traffic)
{
    if (from < 0 || to < 0 ||
        from >= g->count || to >= g->count ||
        distance <= 0 || traffic < 1 || traffic > 3)
    {
        printf("Invalid road details!\n");
        return;
    }

    addEdge(g, from, to, distance, traffic);
    addEdge(g, to, from, distance, traffic);
}

/* =========================
   DIJKSTRA
   ========================= */
void dijkstra(Graph *g, int source, int destination,
              double dist[], int parent[])
{
    int visited[MAX_LOCATIONS];
    int i, count;

    (void)destination;

    for (i = 0; i < g->count; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[source] = 0;

    for (count = 0; count < g->count; count++)
    {
        int u = -1;
        double min = INF;

        for (i = 0; i < g->count; i++)
        {
            if (!visited[i] && dist[i] < min)
            {
                min = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        Node *temp = g->adj[u];

        while (temp != NULL)
        {
            double cost;

            cost = temp->distance + trafficWeight(temp->traffic);

            if (dist[u] + cost < dist[temp->destination])
            {
                dist[temp->destination] =
                    dist[u] + cost;

                parent[temp->destination] = u;
            }

            temp = temp->next;
        }
    }
}

/* =========================
   DISPLAY ROUTE
   ========================= */
void displayRoute(Graph *g, int destination, int parent[])
{
    int path[MAX_LOCATIONS];
    int count = 0;
    int current = destination;
    int i;

    while (current != -1 && count < MAX_LOCATIONS)
    {
        path[count++] = current;
        current = parent[current];
    }

    for (i = count - 1; i >= 0; i--)
    {
        printf("%s", g->name[path[i]]);

        if (i != 0)
            printf(" -> ");
    }

    printf("\n");
}

/* =========================
   ROUTE INFORMATION
   ========================= */
void routeInformation(Graph *g, int source, int destination,
                      int parent[], double *distance,
                      double *trafficIndex, int *hasMedium,
                      int *hasHigh)
{
    int current = destination;

    *distance = 0;
    *trafficIndex = 0;
    *hasMedium = 0;
    *hasHigh = 0;

    while (current != source && current != -1 &&
           parent[current] != -1)
    {
        int previous = parent[current];
        Node *temp = g->adj[previous];

        while (temp != NULL)
        {
            if (temp->destination == current)
            {
                *distance += temp->distance;
                *trafficIndex += temp->traffic;

                if (temp->traffic == 2)
                    *hasMedium = 1;

                if (temp->traffic == 3)
                    *hasHigh = 1;

                break;
            }

            temp = temp->next;
        }

        current = previous;
    }
}

/* =========================
   TRAFFIC DISPLAY
   ========================= */
void displayTraffic(int hasMedium, int hasHigh,
                    double trafficIndex)
{
    int level;

    (void)trafficIndex;

    if (hasMedium && hasHigh)
    {
        level = 3;
        printf("Traffic Level: %d (Medium + High)\n", level);
    }
    else if (hasHigh)
    {
        level = 3;
        printf("Traffic Level: %d (High)\n", level);
    }
    else if (hasMedium)
    {
        level = 2;
        printf("Traffic Level: %d (Medium)\n", level);
    }
    else
    {
        level = 1;
        printf("Traffic Level: %d (Low)\n", level);
    }
}

/* =========================
   AI PREDICTION
   ========================= */
double predictTravelTime(double distance, double trafficIndex)
{
    /*
       Regression model:
       Travel Time =
       -10.30 + 1.80(Distance) + 7.41(Traffic)
    */

    return -10.30
           + 1.80 * distance
           + 7.41 * trafficIndex;
}
