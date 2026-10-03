#include <stdio.h>
#include <string.h>
#include "emergency_request.h"

static void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

static int readInt(const char *prompt, int *value)
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

int inputEmergencyRequest(EmergencyRequest *request)
{
    printf("\n--- Create Emergency Request ---\n");

    if (!readInt("Enter Request ID: ", &request->requestId))
        return 0;

    if (!readInt("Enter Vehicle ID: ", &request->vehicleId))
        return 0;

    printf("Enter Vehicle Type: ");
    if (fgets(request->vehicleType, MAX_TEXT, stdin) == NULL)
        return 0;

    request->vehicleType[strcspn(request->vehicleType, "\n")] = '\0';

    if (!readInt("Enter Source Location ID: ", &request->source))
        return 0;

    if (!readInt("Enter Destination Location ID: ", &request->destination))
        return 0;

    if (!readInt("Enter Emergency Level (3-Critical, 2-High, 1-Normal): ",
                 &request->priority))
        return 0;

    return 1;
}

int validateEmergencyRequest(const EmergencyRequest *request)
{
    if (request->requestId <= 0 || request->vehicleId <= 0)
        return 0;

    if (strlen(request->vehicleType) == 0)
        return 0;

    if (request->source < 0 || request->destination < 0)
        return 0;

    if (request->source == request->destination)
        return 0;

    if (request->priority < 1 || request->priority > 3)
        return 0;

    return 1;
}

void displayEmergencyRequest(const EmergencyRequest *request)
{
    printf("ID: %d | Vehicle: %d (%s) | %d -> %d | Priority: %d\n",
           request->requestId,
           request->vehicleId,
           request->vehicleType,
           request->source,
           request->destination,
           request->priority);
}
