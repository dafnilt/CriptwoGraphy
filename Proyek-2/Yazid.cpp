#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"
#include <ctime>
#include <windows.h>
#include "yazid.h"
#include "alya.h"

void recordHistory(char username[], char filename[]) {
    FILE* historyFile;
    time_t rawtime;
    struct tm* timeinfo;
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

void getCurrentTime(char* timeString) {
    time_t currentTime;
    struct tm* localTime;

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


void historylogin(char* username) {
    char timeString[30];
    getCurrentTime(timeString);

    FILE* file = fopen("historylogin.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "%s\t%s\n", username, timeString);
    fclose(file);

}

void historyregistered(char* username) {
    char timeString[30];
    getCurrentTime(timeString);

    FILE* file = fopen("historyregister.txt", "a");
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

void showuser(char filename[]) {
    FILE* file = fopen(filename, "r");
    list mylist;
    pointer p;

    if (file == NULL) {
        printf("Error: Tidak dapat membuka file credentials.txt\n");
        exit(1);
    }

    char name[100]; char pass[100]; char privatek[100]; char publick[100]; char product[100];

    mylist.First = (pointer)malloc(sizeof(struct prvuser));
    p = mylist.First;

    while (fscanf(file, "%s %s %s %s %s", name, pass, privatek, publick, product) == 5) {
        caesarDecrypt(name, 3);

        strcpy(p->info, name);
        p->prev = NULL;
        p->next = NULL;


        p->next = (pointer)malloc(sizeof(struct prvuser));
        p->next->prev = p;
        p = p->next;
    }

    p = mylist.First;
    while (p != NULL) {
        printf("%s", p->info);
        puts("");
        p = p->next;
    }
}
