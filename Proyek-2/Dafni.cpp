#include <stdio.h>
#include <stdlib.h>
#include "dirent.h"
#include <string.h>
#include "header.h"
#include "Dafni.h"
#include "Asidiq.h"
#include "yazid.h"
#include "Reivan.h"

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

void firstmodul(unsigned long long int e, unsigned long long int n, char q[]) {
    char path[] = "Direktori";
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

    printf("\nMasukkan indeks file yang ingin Anda enkripsi: ");
    int index;
    scanf("%d", &index);
    getchar();

    if (index >= 1 && index <= file_count) {
        char selectedFilename[256];
        strcpy(selectedFilename, filenames[index - 1]);
        printf("Anda memilih file: %s\n", selectedFilename);

        char filepath[256];
        snprintf(filepath, sizeof(filepath), "%s/%s", path, selectedFilename);

        FILE* file = fopen(filepath, "r");
        if (file == NULL) {
            printf("Gagal membuka file.");
            return;
        }
        recordHistory(q, selectedFilename);
        char pesan[100];
        fgets(pesan, sizeof(pesan), file);
        if (pesan[strlen(pesan) - 1] == '\n')
            pesan[strlen(pesan) - 1] = '\0';

        printf("Isi file: %s\n", pesan);

        // Mengisi cipher dengan nilai ASCII dari pesan yang dienkripsi
        unsigned long long int cipher[100]; // Maksimal 100 karakter
        int length = 0; // Menyimpan panjang pesanInteger
        for (int i = 0; i < strlen(pesan); i++) {
            cipher[length++] = fastExponentiation(pesan[i], e, n);
        }

        // Menampilkan hasil enkripsi
        printf("Cipher : ");
        for (int i = 0; i < length; i++) {
            printf("%llu", cipher[i]); // Tampilkan cipher ASCII dengan spasi sebagai pemisah
        }
        printf("\n");

        // Simpan cipher ke dalam file dengan nama yang sama di folder "user/(username)"
        char userFolder[256];
        snprintf(userFolder, sizeof(userFolder), "user/%s", q);
        char encryptedFilename[256];
        snprintf(encryptedFilename, sizeof(encryptedFilename), "%s/%s", userFolder, selectedFilename);
        FILE* encryptedFile = fopen(encryptedFilename, "w");
        if (encryptedFile == NULL) {
            printf("Gagal membuat atau membuka file untuk menyimpan cipher.");
            return;
        }

        for (int i = 0; i < length; i++) {
            fprintf(encryptedFile, "%llu ", cipher[i]); // Tulis cipher ke file dengan spasi sebagai pemisah
        }

        fclose(encryptedFile);

    }
    else {
        printf("Indeks file tidak valid.\n");
        return;
    }
}

// Fungsi untuk menambahkan user ke daftar user
void insertUser(char username[100], uAddress head) {
    uAddress newUser = createNodeUser(username);
    if (head == NULL) {
        head = newUser;
    }
    else {
        uAddress temp = head;
        while (temp->nextUser != NULL) {
            temp = temp->nextUser;
        }
        temp->nextUser = newUser;
    }
}

// Fungsi untuk melihat daftar pengguna yang terdaftar dan mengikuti pengguna lain
void printRegisteredUsersAndFollow(uAddress head) {
    if (head == NULL) {
        printf("Tidak ada pengguna yang terdaftar.\n");
        return;
    }

    uAddress temp = head;
    int userIndex = 1;
    char users[100][100];
    int userCount = 0;

    printf("Daftar pengguna yang terdaftar:\n");
    while (temp != NULL) {
        printf("%d. %s\n", userIndex, temp->username);
        strcpy(users[userCount], temp->username);
        userCount++;
        userIndex++;
        temp = temp->nextUser;
    }

    int choice;
    printf("Masukkan nomor pengguna yang ingin Anda ikuti, atau 0 untuk batal: ");
    scanf("%d", &choice);

    if (choice > 0 && choice <= userCount) {
        char currentUsername[100];
        printf("Masukkan username Anda: ");
        scanf("%s", currentUsername);

        // Cek apakah user yang memberikan perintah ada dalam daftar user
        temp = head;
        bool userExists = false;
        while (temp != NULL) {
            if (strcmp(temp->username, currentUsername) == 0) {
                userExists = true;
                break;
            }
            temp = temp->nextUser;
        }

        if (userExists) {
            insertFollowing(head, currentUsername, users[choice - 1]);
            saveGraph(head);
        }
        else {
            printf("USER %s TIDAK ADA!\n", currentUsername);
        }
    }
    else if (choice == 0) {
        printf("Tidak ada pengguna yang diikuti.\n");
    }
    else {
        printf("Pilihan tidak valid.\n");
    }
}


//void displayFileContent(const char *path, const char *filename) {
//    char filepath[256];
//    snprintf(filepath, sizeof(filepath), "%s\\%s", path, filename);
//
//    FILE *file = fopen(filepath, "r");
//    if (file) {
//        printf("Isi file %s:\n", filename);
//        char buffer[256];
//        while (fgets(buffer, sizeof(buffer), file)) {
//            printf("%s", buffer);
//        }
//        fclose(file);
//    } else {
//        perror("Tidak dapat membuka file");
//        exit(1);
//    }
//}
//
//void mainLogic() {
//    char path[] = "Direktori";
//    char filenames[100][256];
//    int file_count;
//
//    printf("Daftar file dalam direktori:\n");
//    listFiles(path, filenames, &file_count);
//
//    if (file_count == 0) {
//        printf("Tidak ada file dalam direktori.\n");
//        return;
//    }
//
//    for (int i = 0; i < file_count; i++) {
//        printf("%d. %s\n", i + 1, filenames[i]);
//    }
//
//    printf("\nMasukkan indeks file yang ingin Anda tampilkan: ");
//    int index;
//    scanf(" %d", &index);
//    getchar();
//
//    if (index >= 1 && index <= file_count) {
//        displayFileContent(path, filenames[index - 1]);
//    } else {
//        printf("Indeks file tidak valid.\n");
//        return;
//    }
//}