#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include "emergency_request.h"

int saveRequest(const EmergencyRequest *request, const char *filename);
int loadRequests(EmergencyRequest requests[], int maxRequests, const char *filename);
int saveAllRequests(const EmergencyRequest requests[], int count, const char *filename);

#endif
