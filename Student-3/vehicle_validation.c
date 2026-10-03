#include "vehicle_validation.h"

int isDuplicateVehicleId(int vehicleId, const int vehicleIds[], int count) {
    int i;
    for (i = 0; i < count; i++)
        if (vehicleIds[i] == vehicleId)
            return 1;
    return 0;
}

int isValidLocation(int locationId, int vertexCount) {
    return locationId >= 0 && locationId < vertexCount;
}

int isValidPriority(int priority) {
    return priority >= 1 && priority <= 3;
}

int isValidTraffic(int traffic) {
    return traffic >= 1 && traffic <= 3;
}
