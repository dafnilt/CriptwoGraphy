#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"
#include <ctime>
#include <windows.h>

void recordHistory(char username[], char filename[]) {
    FILE *historyFile;
    time_t rawtime;
    struct tm *timeinfo;
    char timeString[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeinfo);

    historyFile = fopen("historyenkrip.txt", "a");

    if (historyFile == NULL) {
        printf("Error saat membuka file history.txt\n");
        exit(1);
    }

    fprintf(historyFile, "[%s] User '%s' mengenkrip file '%s'\n", timeString, username, filename);

    fclose(historyFile);
}

void getCurrentTime(char *timeString) {
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    strftime(timeString, 30, "%Y-%m-%d %H:%M:%S", localTime);
}

void recordHistorydekrip(char username[], char filename[]) {
    FILE* historyFile;
    time_t rawtime;
    struct tm* timeinfo;
    char timeString[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", timeinfo);

    historyFile = fopen("historydekrip.txt", "a");

    if (historyFile == NULL) {
        printf("Error saat membuka file history.txt\n");
        exit(1);
    }

    fprintf(historyFile, "[%s] User '%s' mengdekrip file '%s'\n", timeString, username, filename);

    fclose(historyFile);
}


void historylogin(char *username) {
    char timeString[30];
    getCurrentTime(timeString);

    FILE *file = fopen("historylogin.txt", "a");
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

    FILE *file = fopen("historyregister.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "%s\t%s\n", username, timeString);
    fclose(file);

}


char* bacafile(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = (char*)malloc(file_size + 1);
    if (content == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(content, 1, file_size, file);
    content[bytes_read] = '\0'; 

    fclose(file);
    return content;
}
