#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "emergency_request.h"

typedef struct {
    EmergencyRequest requests[MAX_REQUESTS];
    int size;
} PriorityQueue;

void initPriorityQueue(PriorityQueue *queue);
int insertRequest(PriorityQueue *queue, EmergencyRequest request);
int removeRequest(PriorityQueue *queue, EmergencyRequest *request);
void displayQueue(const PriorityQueue *queue);
int isQueueEmpty(const PriorityQueue *queue);

#endif
