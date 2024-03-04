#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include <string.h>
#include "header.h"

void p_time(const char *filename, timestamps *ts, const char *username) {
    
    time_t current_time;
    time(&current_time);
    
    struct tm *local_time = localtime(&current_time);
    FILE *file;

    if ((file = fopen(filename, "ab")) == NULL) {
    
        printf("Failed to open file!\n");
        exit(1);
    
    } else {
    
        strcpy(ts->user, username);
        ts->history = current_time;
        fprintf(file, "%s %s", ts->user, asctime(local_time));
    }
    fclose(file);
}

