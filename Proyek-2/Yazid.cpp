#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "header.h"

void p_time(const char* filename, timestamps* ts) {

    time_t current_time;
    time(&current_time);


    struct tm* local_time = localtime(&current_time);

    FILE* file;

    if ((file = fopen(filename, "wb")) == NULL) {
        printf("Failed to open file!\n");
        exit(1);
    }
    else {
        int i = 0;
        strcpy(ts->user[i], "buUdi");
        ts->history[i] = current_time;
        fprintf(file, "%s %s", ts->user[i], asctime(local_time));
    }

    fclose(file);
}

