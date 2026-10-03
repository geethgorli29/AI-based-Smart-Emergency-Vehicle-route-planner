#ifndef C_STRUCTURES_H
#define C_STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEHICLES 100
#define MAX_LOCATIONS 100
#define MAX_REQUESTS 100
#define MAX_NAME 50
#define MAX_TYPE 20

// 1. Vehicle structure
typedef struct {
    int vehicleId;
    char vehicleType[MAX_TYPE];
    int status;
    int currentLocation;
} Vehicle;

// 2. Location structure
typedef struct {
    int locationId;
    char name[MAX_NAME];
    char type[MAX_TYPE];
} Location;

// 3. Road structure
typedef struct {
    int destination;
    int distance;
    int trafficWeight;
} Road;

// 4. Emergency Request structure
typedef struct {
    int requestId;
    int vehicleId;
    int source;
    int destination;
    int priority;
} EmergencyRequest;

// 5. Graph Node structure
typedef struct Node {
    int destination;
    int distance;
    int trafficWeight;
    struct Node *next;
} Node;

// 6. Graph structure
typedef struct {
    int vertices;
    Node *adjList[MAX_LOCATIONS];
} Graph;

#endif
