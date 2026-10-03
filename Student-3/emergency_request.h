#ifndef EMERGENCY_REQUEST_H
#define EMERGENCY_REQUEST_H

#define MAX_REQUESTS 100
#define MAX_TEXT 50

typedef struct {
    int requestId;
    int vehicleId;
    char vehicleType[MAX_TEXT];
    int source;
    int destination;
    int priority; /* 3 = Critical, 2 = High, 1 = Normal */
} EmergencyRequest;

int inputEmergencyRequest(EmergencyRequest *request);
int validateEmergencyRequest(const EmergencyRequest *request);
void displayEmergencyRequest(const EmergencyRequest *request);

#endif
