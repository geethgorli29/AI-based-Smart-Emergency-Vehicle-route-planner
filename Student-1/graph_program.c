#include <stdio.h>
#include <stdlib.h>

struct Node {
    int dest;
    int distance;
    struct Node *next;
};

struct Node *graph[4];

// Function to add a road (undirected graph)
void addRoad(int src, int dest, int distance) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->distance = distance;
    newNode->next = graph[src];
    graph[src] = newNode;

    newNode = malloc(sizeof(struct Node));
    newNode->dest = src;
    newNode->distance = distance;
    newNode->next = graph[dest];
    graph[dest] = newNode;
}

// Function to display the graph
void displayGraph() {
    for (int i = 0; i < 4; i++) {
        struct Node *temp = graph[i];
        printf("Location %d: ", i);
        while (temp != NULL) {
            printf("%d (%d km) -> ",
                   temp->dest, temp->distance);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    for (int i = 0; i < 4; i++) {
        graph[i] = NULL;
    }

    // Adding roads between locations
    addRoad(0, 1, 5);
    addRoad(0, 2, 8);
    addRoad(1, 3, 4);
    addRoad(2, 3, 6);

    displayGraph();
    return 0;
}
