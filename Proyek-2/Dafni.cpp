#include <stdio.h>
#include <stdlib.h>
#include "dirent.h"
#include <string.h>
#include "header.h"
#include "Dafni.h"
#include "Asidiq.h"
#include "yazid.h"
#include "Reivan.h"
#include "alya.h"

#define MAX_FILE_SIZE 1024

LoginResult currentUser;

extern userLs* headPtr;



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

char* firstmodul(unsigned long long int e, unsigned long long int n, char q[]) {
    char path[] = "Direktori";
    char filenames[100][256];
    int file_count;

    printf("Daftar file dalam direktori:\n");
    listFiles(path, filenames, &file_count);

    if (file_count == 0) {
        printf("Tidak ada file dalam direktori.\n");
        return NULL;
    }

    for (int i = 0; i < file_count; i++) {
        printf("%d. %s\n", i + 1, filenames[i]);
    }

    printf("\nMasukkan indeks file yang ingin Anda enkripsi: ");
    int index;
    scanf("%d", &index);
    getchar();



    if (index >= 1 && index <= file_count) {
        /*
        * char selectedFilename[256];
        strcpy(selectedFilename, filenames[index - 1]);
        printf("Anda memilih file: %s\n", selectedFilename);
        */

        // Menyimpan nama file yang dipilih
        char* selectedFilename = (char*)malloc(256 * sizeof(char));
        snprintf(selectedFilename, sizeof(selectedFilename), "%s", filenames[index - 1]);

        printf("Anda memilih file: %s\n", selectedFilename);

        char filepath[256];
        snprintf(filepath, sizeof(filepath), "%s/%s", path, selectedFilename);

        FILE* file = fopen(filepath, "r");
        if (file == NULL) {
            printf("Gagal membuka file.");
            return NULL;
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
            return NULL;
        }

        for (int i = 0; i < length; i++) {
            fprintf(encryptedFile, "%llu ", cipher[i]); // Tulis cipher ke file dengan spasi sebagai pemisah
        }

        fclose(encryptedFile);

        // Membebaskan memori yang dialokasikan untuk selectedFilename
        free(selectedFilename);

        // Mengembalikan nama file yang dipilih
        return selectedFilename;

    }
    else {
        printf("Indeks file tidak valid.\n");
        return NULL;
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

void printRegisteredUsersAndFollow(uAddress head, const char* currentUser) {
    FILE* file = fopen("credentials.txt", "r");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file credentials.txt\n");
        return;
    }

    printf("Daftar pengguna yang terdaftar:\n");

    char encryptedUsername[100];
    char encryptedPassword[100];
    char encryptedPrivateKey[100], encryptedPublicKey[100], encryptedProduct[100];
    int userIndex = 1;
    char users[100][100]; // Array untuk menyimpan username yang didekripsi
    int userCount = 0;

    // Baca baris demi baris dari file credentials.txt
    while (fscanf(file, "%s %s %s %s %s", encryptedUsername, encryptedPassword, encryptedPrivateKey, encryptedPublicKey, encryptedProduct) != EOF) {
        // Dekripsi username
        caesarDecrypt(encryptedUsername, 3);

        // Cetak username yang didekripsi
        printf("%d. %s\n", userIndex, encryptedUsername);
        strcpy(users[userCount], encryptedUsername);
        userCount++;
        userIndex++;
    }

    fclose(file);

    int choice;
    printf("Masukkan nomor pengguna yang ingin Anda ikuti, atau 0 untuk batal: ");
    scanf("%d", &choice);

    if (choice > 0 && choice <= userCount) {
        // Cek apakah user yang memberikan perintah ada dalam daftar user
        uAddress temp = head;
        bool userExists = false;
        while (temp != NULL) {
            if (strcmp(temp->username, currentUser) == 0) {
                userExists = true;
                break;
            }
            temp = temp->nextUser;
        }

        if (userExists) {
            printf("USER %s ditemukan dalam daftar.\n", currentUser);
            insertFollowing(head, (char*)currentUser, users[choice - 1]);
            saveGraph(head);
        }
        else {
            printf("USER %s TIDAK ADA!\n", currentUser);
        }
    }
    else if (choice == 0) {
        printf("Tidak ada pengguna yang diikuti.\n");
    }
    else {
        printf("Pilihan tidak valid.\n");
    }
}

// Fungsi untuk menambahkan pengguna yang diikuti ke daftar pengikut
/* void insertFollowing(uAddress head, char user[100], char follow[100]) {
    bool foundUser = false, foundFollow = false;
    uAddress p = head;
    fAddress q;

    // Cek apakah user ada dalam daftar user
    while (p != NULL) {
        if (strcmp(p->username, user) == 0) {
            foundUser = true;
            break;
        }
        p = p->nextUser;
    }

    if (!foundUser) {
        printf("USER %s TIDAK ADA!\n", user);
        return;
    }

    // Reset pointer ke head untuk mencari user yang akan diikuti
    p = head;
    while (p != NULL) {
        if (strcmp(p->username, follow) == 0) {
            foundFollow = true;
            break;
        }
        p = p->nextUser;
    }

    if (!foundFollow) {
        printf("USER %s TIDAK ADA!\n", follow);
        return;
    }

    // Tambahkan follower jika user dan user yang akan diikuti ditemukan
    p = head;
    while (p != NULL) {
        if (strcmp(p->username, user) == 0) {
            if (p->follow == NULL) {
                p->follow = createNodeFollowing(follow);
            }
            else {
                q = p->follow;
                while (q->next != NULL) {
                    q = q->next;
                }
                q->next = createNodeFollowing(follow);
            }
            printf("%s sekarang mengikuti %s\n", user, follow);
            return;
        }
        p = p->nextUser;
    }
}*/


// Fungsi untuk melihat daftar pengguna yang terdaftar
void printRegisteredUsers() {
    FILE* file = fopen("credentials.txt", "r");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file credentials.txt\n");
        return;
    }

    printf("Daftar pengguna yang terdaftar:\n");

    char encryptedUsername[100];
    char encryptedPassword[100];
    char encryptedPrivateKey[100], encryptedPublicKey[100], encryptedProduct[100];
    int userIndex = 1;

    // Baca baris demi baris dari file credentials.txt
    while (fscanf(file, "%s %s %s %s %s", encryptedUsername, encryptedPassword, encryptedPrivateKey, encryptedPublicKey, encryptedProduct) != EOF) {
        // Dekripsi username
        caesarDecrypt(encryptedUsername, 3);

        // Cetak username yang didekripsi
        printf("%d. %s\n", userIndex, encryptedUsername);
        userIndex++;
    }

    fclose(file);
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