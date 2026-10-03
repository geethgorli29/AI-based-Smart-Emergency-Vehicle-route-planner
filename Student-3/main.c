#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "emergency_request.h"
#include "priority_queue.h"
#include "file_handling.h"
#include "vehicle_validation.h"
#include "dijkstra.h"
#include "traffic_weight.h"
#include "route_comparison.h"
#include "student1_graph.h"

#define REQUEST_FILE "requests.dat"

static char locationNames[MAX_VERTICES][MAX_LOCATION_NAME];
static int totalLocations = 0;
static int totalRoads = 0;

static void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/*
 * Student 1 graph integration:
 * Student 3 no longer asks the user to enter the complete graph.
 * Student 1's final locations, roads and road traffic values are supplied
 * through loadStudent1Graph() in student1_graph.c.
 */
static int loadProjectGraph(Graph *graph)
{
    if (!loadStudent1Graph(graph, locationNames,
                            &totalLocations, &totalRoads)) {
        printf("Error: Student 1 graph data could not be loaded.\n");
        return 0;
    }

    printf("\nStudent 1 project graph loaded successfully.\n");
    printf("Total Locations: %d\n", totalLocations);
    printf("Total Roads: %d\n", totalRoads);
    return 1;
}

static void displayProjectLocations(void)
{
    int i;

    printf("\n--- PROJECT LOCATIONS ---\n");
    for (i = 0; i < totalLocations; i++)
        printf("ID: %d | Name: %s\n", i, locationNames[i]);
}

static void displayProjectGraph(const Graph *graph)
{
    int i;
    DNode *temp;

    printf("\n--- ROAD NETWORK GRAPH ---\n");

    for (i = 0; i < graph->vertices; i++) {
        printf("%s: ", locationNames[i]);
        temp = graph->adjList[i];

        if (temp == NULL)
            printf("NULL");

        while (temp != NULL) {
            printf("%s (%d km, traffic %d, cost %d) -> ",
                   locationNames[temp->destination],
                   temp->distance,
                   temp->traffic,
                   getEffectiveRoadCost(temp));
            temp = temp->next;
        }

        printf("NULL\n");
    }
}

static void freeProjectGraph(Graph *graph)
{
    int i;
    DNode *temp;
    DNode *nextNode;

    for (i = 0; i < graph->vertices; i++) {
        temp = graph->adjList[i];

        while (temp != NULL) {
            nextNode = temp->next;
            free(temp);
            temp = nextNode;
        }

        graph->adjList[i] = NULL;
    }

    graph->vertices = 0;
}

static void printMenu(void)
{
    printf("\n==============================================\n");
    printf(" AI-BASED EMERGENCY VEHICLE ROUTE PLANNER\n");
    printf("==============================================\n");
    printf("1. Create Emergency Request\n");
    printf("2. View Pending Requests\n");
    printf("3. Handle Highest-Priority Request\n");
    printf("4. Find Shortest Route\n");
    printf("5. Calculate Traffic-Weighted Road Cost\n");
    printf("6. Compare Two Routes\n");
    printf("7. Load Saved Requests\n");
    printf("8. Save Current Queue\n");
    printf("9. Exit\n");
    printf("Enter choice: ");
}

static int requestIdExists(const PriorityQueue *queue, int id)
{
    int i;

    for (i = 0; i < queue->size; i++) {
        if (queue->requests[i].requestId == id)
            return 1;
    }

    return 0;
}

static void createRequest(PriorityQueue *queue)
{
    EmergencyRequest request;

    if (!inputEmergencyRequest(&request))
        return;

    if (!validateEmergencyRequest(&request)) {
        printf("Error: invalid emergency request.\n");
        return;
    }

    if (!isValidLocation(request.source, totalLocations) ||
        !isValidLocation(request.destination, totalLocations)) {
        printf("Error: invalid location ID. Valid IDs are 0 to %d.\n",
               totalLocations - 1);
        return;
    }

    if (requestIdExists(queue, request.requestId)) {
        printf("Error: duplicate request ID.\n");
        return;
    }

    if (insertRequest(queue, request)) {
        printf("Request added successfully.\n");

        if (!saveRequest(&request, REQUEST_FILE))
            printf("Warning: request was queued but could not be saved.\n");
    }
}

static void loadSavedRequests(PriorityQueue *queue)
{
    EmergencyRequest saved[MAX_REQUESTS];
    int count, i;
    int insertedCount = 0;

    count = loadRequests(saved, MAX_REQUESTS, REQUEST_FILE);

    if (count == 0) {
        printf("No saved requests found.\n");
        return;
    }

    for (i = 0; i < count && queue->size < MAX_REQUESTS; i++) {
        if (validateEmergencyRequest(&saved[i]) &&
            isValidLocation(saved[i].source, totalLocations) &&
            isValidLocation(saved[i].destination, totalLocations) &&
            !requestIdExists(queue, saved[i].requestId)) {

            if (insertRequest(queue, saved[i]))
                insertedCount++;
        }
    }

    printf("Loaded %d request(s) successfully into the queue.\n",
           insertedCount);

    if (insertedCount != count)
        printf("%d saved record(s) were rejected because of invalid data, "
               "invalid location IDs, duplicate IDs, or queue capacity.\n",
               count - insertedCount);
}

static void saveCurrentQueue(const PriorityQueue *queue)
{
    if (saveAllRequests(queue->requests, queue->size, REQUEST_FILE))
        printf("Current queue saved to %s.\n", REQUEST_FILE);
    else
        printf("Error: current queue could not be saved.\n");
}

static int readMenuInteger(const char *prompt, int *value)
{
    printf("%s", prompt);

    if (scanf("%d", value) != 1) {
        clearInputBuffer();
        printf("Invalid numeric input. Please enter a number.\n");
        return 0;
    }

    clearInputBuffer();
    return 1;
}

int main(void)
{
    PriorityQueue queue;
    Graph graph;
    int choice, source, destination, distance, traffic;
    int distance1, distance2;
    EmergencyRequest request;

    initPriorityQueue(&queue);

    if (!loadProjectGraph(&graph)) {
        printf("Project graph could not be loaded. Exiting application.\n");
        return 1;
    }

    displayProjectLocations();
    displayProjectGraph(&graph);

    do {
        printMenu();

        if (!readMenuInteger("", &choice))
            continue;

        switch (choice) {
        case 1:
            createRequest(&queue);
            break;

        case 2:
            displayQueue(&queue);
            break;

        case 3:
            if (removeRequest(&queue, &request)) {
                printf("\nHandling Request ID: %d\n", request.requestId);
                printf("Vehicle: %d (%s)\n",
                       request.vehicleId, request.vehicleType);
                printf("Route: %d -> %d\n",
                       request.source, request.destination);

                if (isValidLocation(request.source, graph.vertices) &&
                    isValidLocation(request.destination, graph.vertices)) {

                    printf("Source: %s\n", locationNames[request.source]);
                    printf("Destination: %s\n",
                           locationNames[request.destination]);

                    dijkstra(&graph, request.source, request.destination);
                } else {
                    printf("Invalid location ID in emergency request.\n");
                }
            }
            break;

        case 4:
            if (!readMenuInteger("Enter source location ID: ", &source))
                break;

            if (!readMenuInteger("Enter destination location ID: ",
                                 &destination))
                break;

            if (!isValidLocation(source, graph.vertices) ||
                !isValidLocation(destination, graph.vertices)) {

                printf("Invalid location ID. Valid IDs are 0 to %d.\n",
                       graph.vertices - 1);
            } else {
                printf("Source: %s\n", locationNames[source]);
                printf("Destination: %s\n", locationNames[destination]);
                dijkstra(&graph, source, destination);
            }
            break;

        case 5:
            if (!readMenuInteger("Enter road distance: ", &distance))
                break;

            if (!readMenuInteger(
                    "Traffic level (1-Low, 2-Medium, 3-High): ",
                    &traffic))
                break;

            if (!isValidTraffic(traffic) || distance <= 0) {
                printf("Invalid distance or traffic level.\n");
            } else {
                printf("Traffic Weight = %d\n",
                       calculateTrafficWeight(traffic));
                printf("Effective Road Cost = %d\n",
                       calculateRoadCost(distance, traffic));
            }
            break;

        case 6:
            if (!readMenuInteger("Enter Route 1 cost: ", &distance1))
                break;

            if (!readMenuInteger("Enter Route 2 cost: ", &distance2))
                break;

            compareRoutes(distance1, distance2);
            break;

        case 7:
            loadSavedRequests(&queue);
            break;

        case 8:
            saveCurrentQueue(&queue);
            break;

        case 9:
            printf("Exiting application.\n");
            break;

        default:
            printf("Invalid choice. Please select 1-9.\n");
        }

    } while (choice != 9);

    freeProjectGraph(&graph);
    return 0;
}
