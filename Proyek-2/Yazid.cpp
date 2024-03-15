#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

void recordHistory(char username[], char filename[]) {
    FILE *historyFile;
    time_t rawtime;
    struct tm *timeinfo;
    char timeString[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeinfo);

    historyFile = fopen("history.txt", "a"); // Buka file teks untuk menambahkan (append)

    if (historyFile == NULL) {
        printf("Error saat membuka file history.txt\n");
        exit(1);
    }

    fprintf(historyFile, "[%s] User '%s' membuka file '%s'\n", timeString, username, filename);

    fclose(historyFile);
}

void getCurrentTime(char *timeString) {
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    strftime(timeString, 30, "%Y-%m-%d %H:%M:%S", localTime);
}


void historylogin(char *username) {
    char timeString[30];
    getCurrentTime(timeString);

    FILE *file = fopen(historylogin.txt, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "%s\t%s\n", username, timeString);
    fclose(file);

}

void historyregistered(char *username) {
    char timeString[30];
    getCurrentTime(timeString);

    FILE *file = fopen(historyregister.txt, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "%s\t%s\n", username, timeString);
    fclose(file);

}
