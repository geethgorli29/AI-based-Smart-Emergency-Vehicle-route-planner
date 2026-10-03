#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_LOCATIONS 100
#define MAX_NAME 60
#define MAX_VEHICLE_TYPE 30
#define INF 999999

/* =========================
   GRAPH NODE
   ========================= */
typedef struct Node
{
    int destination;
    double distance;
    int traffic;
    struct Node *next;
} Node;

/* =========================
   GRAPH
   ========================= */
typedef struct
{
    char name[MAX_LOCATIONS][MAX_NAME];
    Node *adj[MAX_LOCATIONS];
    int count;
} Graph;

/* =========================
   VEHICLE
   ========================= */
typedef struct
{
    int id;
    char type[MAX_VEHICLE_TYPE];
    int currentLocation;
} Vehicle;

/* =========================
   EMERGENCY REQUEST
   ========================= */
typedef struct
{
    int id;
    int vehicleId;
    int source;
    int destination;
    int priority;
} Request;

#endif
