#include <stdio.h>
#include <stdlib.h>
#include "dirent.h"
#include <string.h>
#include "header.h"

#define MAX_FILE_SIZE 1024

void listFiles(const char* path, char filenames[][256], int* file_count) {
    DIR* dir;
    struct dirent* ent;
    dir = opendir(path);
    *file_count = 0;

    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
                continue;
            }
            strcpy(filenames[*file_count], ent->d_name);
            (*file_count)++;
        }
        closedir(dir);
    }
}

void displayFileContent(const char* path, const char* filename) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s\\%s", path, filename);

    FILE* file = fopen(filepath, "r");
    if (file) {
        printf("Isi file %s:\n", filename);
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file)) {
            printf("%s", buffer);
        }
        fclose(file);
    }
    else {
        perror("Tidak dapat membuka file");
        exit(1);
    }
}

void mainLogic() {
    char path[] = "D:\\DAFNI\\SEMESTER 2\\PROYEK 2\\proyek\\Proyek-2\\Direktori";
    char filenames[100][256];
    int file_count;

    printf("Daftar file dalam direktori:\n");
    listFiles(path, filenames, &file_count);

    if (file_count == 0) {
        printf("Tidak ada file dalam direktori.\n");
        return;
    }

    for (int i = 0; i < file_count; i++) {
        printf("%d. %s\n", i + 1, filenames[i]);
    }

    printf("\nMasukkan indeks file yang ingin Anda tampilkan: ");
    char input[10];
    fgets(input, sizeof(input), stdin);
    int index = atoi(input);

    if (index >= 1 && index <= file_count) {
        displayFileContent(path, filenames[index - 1]);
    }
    else {
        printf("Indeks file tidak valid.\n");
        return;
    }
}