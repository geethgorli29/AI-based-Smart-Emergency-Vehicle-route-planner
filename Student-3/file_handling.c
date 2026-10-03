#include <stdio.h>
#include "file_handling.h"

int saveRequest(const EmergencyRequest *request, const char *filename) {
    FILE *fp = fopen(filename, "ab");
    if (fp == NULL) {
        printf("Error: unable to open %s for writing.\n", filename);
        return 0;
    }
    if (fwrite(request, sizeof(EmergencyRequest), 1, fp) != 1) {
        fclose(fp);
        printf("Error: request could not be saved.\n");
        return 0;
    }
    fclose(fp);
    return 1;
}

int loadRequests(EmergencyRequest requests[], int maxRequests, const char *filename) {
    FILE *fp = fopen(filename, "rb");
    int count;
    if (fp == NULL) {
        return 0; /* File may not exist on first run. */
    }
    count = (int)fread(requests, sizeof(EmergencyRequest), maxRequests, fp);
    fclose(fp);
    return count;
}

int saveAllRequests(const EmergencyRequest requests[], int count, const char *filename) {
    FILE *fp = fopen(filename, "wb");
    size_t written;

    if (fp == NULL) {
        printf("Error: unable to open %s for writing.\n", filename);
        return 0;
    }

    written = fwrite(requests, sizeof(EmergencyRequest), count, fp);
    if (written != (size_t)count) {
        printf("Error: failed to write all requests to %s.\n", filename);
        fclose(fp);
        return 0;
    }

    fclose(fp);
    return 1;
}
