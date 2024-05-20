#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"
#include <ctime>
#include <windows.h>
#include "yazid.h"
#include "alya.h"
#include "Asidiq.h"
#include <direct.h>
#include "Dafni.h"

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
        printf(RED"Error opening file!\n");
        printf(BLACK"");
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

void showuser(char filename[], char* curruser) {
    FILE* file = fopen(filename, "r");
    list mylist;
    pointer p, new_node;

    if (file == NULL) {
        printf("Error: Tidak dapat membuka file %s\n", filename);
        exit(1);
    }

    char name[100], pass[100], privatek[100], publick[100], product[100];

    mylist.First = NULL;

    while (fscanf(file, "%s %s %s %s %s", name, pass, privatek, publick, product) == 5) {
        caesarDecrypt(name, 3);
        if (strcmp(name, curruser) == 0) {
            continue;
        }

        new_node = (pointer)malloc(sizeof(struct prvuser));
        strcpy(new_node->info, name);
        new_node->prev = NULL;
        new_node->next = NULL;

        if (mylist.First == NULL) {
            mylist.First = new_node;
        }
        else {
            p = mylist.First;
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = new_node;
            new_node->prev = p;
        }
    }

    fclose(file);

    p = mylist.First;
    while (p != NULL) {
        printf("%s\n", p->info);
        pointer temp = p;
        p = p->next;
        free(temp); 
    }
}



void encrypt_friend(char curruser[100], char friendname[100]) {
    FILE* file = fopen("credentials.txt", "r");
    if (file == NULL) {
        printf(RED"Error: Tidak dapat membuka file %s\n", "credentials.txt");
        printf(BLACK"");
        exit(1);
    }

    char name[100], pass[100], privatek[100], publick[100], product[100]; // Corrected data types
    while (fscanf(file, "%s %s %s %s %s", name, pass, privatek, publick, product) == 5) {
        caesarDecrypt(name, 3);
        caesarDecrypt(privatek, 3);
        caesarDecrypt(product, 3);

        unsigned long long prvkey = strtoull(privatek, NULL, 10);
        unsigned long long prdct = strtoull(product, NULL, 10);

        if (strcmp(name, curruser) == 0) {
            continue;
        }

        if (strcmp(name, friendname) == 0) {
            char path[] = "Direktori";
            char filenames[100][256];
            int file_count;

            printf(PURPLE"Daftar file dalam direktori:\n");
            listFiles(path, filenames, &file_count);

            if (file_count == 0) {
                printf(RED"Tidak ada file dalam direktori.\n");
                return;
            }

            for (int i = 0; i < file_count; i++) {
                printf("%d. %s\n", i + 1, filenames[i]);
            }

            printf(BLACK"");
            printf("\nMasukkan indeks file yang ingin Anda enkripsi: ");
            int index;
            scanf("%d", &index);
            getchar();

            if (index >= 1 && index <= file_count) {
                char selectedFilename[256];
                strcpy(selectedFilename, filenames[index - 1]);
                printf(BLUE"Anda memilih file: %s\n", selectedFilename);

                char filepath[256];
                snprintf(filepath, sizeof(filepath), "%s/%s", path, selectedFilename);

                FILE* file = fopen(filepath, "r");
                if (file == NULL) {
                    printf(RED"Gagal membuka file.");
                    return;
                }
                recordHistory(curruser, selectedFilename);
                char pesan[100];
                fgets(pesan, sizeof(pesan), file);
                if (pesan[strlen(pesan) - 1] == '\n')
                    pesan[strlen(pesan) - 1] = '\0';

                printf("Isi file: %s\n", pesan);

                // Mengisi cipher dengan nilai ASCII dari pesan yang dienkripsi
                unsigned long long int cipher[100]; // Maksimal 100 karakter
                int length = 0; // Menyimpan panjang pesanInteger
                for (int i = 0; i < strlen(pesan); i++) {
                    cipher[length++] = fastExponentiation(pesan[i], prvkey, prdct);
                }

                // Menampilkan hasil enkripsi
                printf("Cipher : ");
                for (int i = 0; i < length; i++) {
                    printf("%llu", cipher[i]); // Tampilkan cipher ASCII dengan spasi sebagai pemisah
                }
                printf("\n");

                // Simpan cipher ke dalam file dengan nama yang sama di folder "user/(username)"
                char userFolder[256];
                snprintf(userFolder, sizeof(userFolder), "user/%s/%s", friendname,curruser);
                //char userFolder2[256];
                //snprintf(userFolder2, sizeof(userFolder2), "%s/%s",userFolder, curruser);
                char encryptedFilename[256];
                snprintf(encryptedFilename, sizeof(encryptedFilename), "%s/%s", userFolder, selectedFilename);
                FILE* encryptedFile = fopen(encryptedFilename, "w");
                if (encryptedFile == NULL) {
                    printf(RED"Gagal membuat atau membuka file untuk menyimpan cipher.");
                    return;
                }

                for (int i = 0; i < length; i++) {
                    fprintf(encryptedFile, "%llu ", cipher[i]); // Tulis cipher ke file dengan spasi sebagai pemisah
                }

                fclose(encryptedFile);
                printf(BLACK"");
            }
            else {
                printf(RED"Indeks file tidak valid.\n");
                printf(BLACK"");
                return;
            }
        }
    }
    fclose(file); // Close the credentials file
}



