#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(void)
{
    Graph graph;
    Vehicle vehicle;
    Request request;

    int numberOfRoads;
    int i;

    char sourceName[MAX_NAME];
    char destinationName[MAX_NAME];

    double dist[MAX_LOCATIONS];
    int parent[MAX_LOCATIONS];

    double routeDistance;
    double trafficIndex;
    double predictedTime;

    int hasMedium;
    int hasHigh;

    int source;
    int destination;

    initializeGraph(&graph);

    /* =========================
       VEHICLE INPUT
       ========================= */
    printf("========== VEHICLE DETAILS ==========\n");

    printf("Enter Vehicle ID: ");
    scanf("%d", &vehicle.id);

    printf("Enter Vehicle Type: ");
    scanf(" %29[^\n]", vehicle.type);

    printf("\n");

    /* =========================
       LOCATION INPUT
       ========================= */
    printf("========== LOCATION DETAILS ==========\n");

    printf("Enter Source Location: ");
    scanf(" %59[^\n]", sourceName);

    printf("Enter Destination Location: ");
    scanf(" %59[^\n]", destinationName);

    source = getLocation(&graph, sourceName);
    destination = getLocation(&graph, destinationName);

    if (source == -1 || destination == -1)
    {
        printf("Invalid location.\n");
        return 1;
    }

    vehicle.currentLocation = source;

    /* =========================
       ROAD INPUT
       ========================= */
    printf("\n========== ROAD DETAILS ==========\n");

    printf("Enter number of roads: ");
    scanf("%d", &numberOfRoads);

    if (numberOfRoads < 0)
    {
        printf("Invalid number of roads.\n");
        return 1;
    }

    for (i = 0; i < numberOfRoads; i++)
    {
        char fromName[MAX_NAME];
        char toName[MAX_NAME];
        double distance;
        int traffic;

        int from;
        int to;

        printf("\nRoad %d\n", i + 1);

        printf("From: ");
        scanf(" %59[^\n]", fromName);

        printf("To: ");
        scanf(" %59[^\n]", toName);

        printf("Distance (km): ");
        scanf("%lf", &distance);

        printf("Traffic (1-Low, 2-Medium, 3-High): ");
        scanf("%d", &traffic);

        from = getLocation(&graph, fromName);
        to = getLocation(&graph, toName);

        if (from == -1 || to == -1)
        {
            printf("Invalid location. Road skipped.\n");
            continue;
        }

        addRoad(&graph, from, to, distance, traffic);
    }

    /* =========================
       REQUEST INPUT
       ========================= */
    printf("\n========== EMERGENCY REQUEST ==========\n");

    printf("Enter Request ID: ");
    scanf("%d", &request.id);

    printf("Enter Priority: ");
    scanf("%d", &request.priority);

    request.vehicleId = vehicle.id;
    request.source = source;
    request.destination = destination;

    /* =========================
       PROCESSING
       ========================= */
    printf("\n");
    printf("========== PROCESSING EMERGENCY ==========\n");

    printf("Request ID: %d\n", request.id);
    printf("Vehicle ID: %d\n", request.vehicleId);
    printf("Source: %s\n", graph.name[source]);
    printf("Destination: %s\n", graph.name[destination]);
    printf("Priority: %d\n", request.priority);

    /* =========================
       DIJKSTRA
       ========================= */
    dijkstra(&graph, source, destination, dist, parent);

    printf("\n");
    printf("========== DIJKSTRA ROUTE ==========\n");

    if (dist[destination] == INF)
    {
        printf("No route available.\n");
        return 0;
    }

    printf("Shortest effective cost = %.0f\n",
           dist[destination]);

    printf("Route: ");
    displayRoute(&graph, destination, parent);

    /* =========================
       ROUTE INFORMATION
       ========================= */
    routeInformation(&graph,
                     source,
                     destination,
                     parent,
                     &routeDistance,
                     &trafficIndex,
                     &hasMedium,
                     &hasHigh);

    /* =========================
       AI PREDICTION
       ========================= */
    predictedTime =
        predictTravelTime(routeDistance, trafficIndex);

    printf("\n");
    printf("========== AI TRAVEL-TIME PREDICTION ==========\n");

    printf("Regression Equation: "
           "Travel Time = -10.30 + "
           "1.80(Distance) + "
           "7.41(Traffic)\n");

    printf("Route Distance: %.2f km\n",
           routeDistance);

    displayTraffic(hasMedium, hasHigh, trafficIndex);

    printf("Traffic Index: %.2f\n",
           trafficIndex);

    printf("Predicted Travel Time: %.2f minutes\n",
           predictedTime);

    /* =========================
       SYSTEM COMPLETE
       ========================= */
    printf("\n");
    printf("========== SYSTEM COMPLETED ==========\n");
    printf("[Process completed - press Enter]\n");

    getchar();
    getchar();

    return 0;
}
