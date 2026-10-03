#include <stdio.h>
#include "priority_queue.h"

void initPriorityQueue(PriorityQueue *queue)
{
    queue->size = 0;
}

int isQueueEmpty(const PriorityQueue *queue)
{
    return queue->size == 0;
}

/* Keeps the array sorted: highest priority first, oldest first on ties. */
int insertRequest(PriorityQueue *queue, EmergencyRequest request)
{
    int pos;

    if (queue->size >= MAX_REQUESTS)
        return 0;

    pos = queue->size;
    while (pos > 0 && queue->requests[pos - 1].priority < request.priority) {
        queue->requests[pos] = queue->requests[pos - 1];
        pos--;
    }

    queue->requests[pos] = request;
    queue->size++;
    return 1;
}

int removeRequest(PriorityQueue *queue, EmergencyRequest *request)
{
    int i;

    if (isQueueEmpty(queue))
        return 0;

    *request = queue->requests[0];

    for (i = 1; i < queue->size; i++)
        queue->requests[i - 1] = queue->requests[i];

    queue->size--;
    return 1;
}

void displayQueue(const PriorityQueue *queue)
{
    int i;

    if (isQueueEmpty(queue)) {
        printf("\nNo pending emergency requests.\n");
        return;
    }

    printf("\n--- PENDING REQUESTS (%d) ---\n", queue->size);
    for (i = 0; i < queue->size; i++)
        displayEmergencyRequest(&queue->requests[i]);
}
