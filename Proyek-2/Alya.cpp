#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

// Fungsi untuk melakukan enkripsi Caesar cipher
void caesarEncrypt(char* text, int shift) {
    int i = 0;
    while (text[i] != '\0') {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z')) {
            // Untuk huruf
            if (text[i] >= 'a' && text[i] <= 'z') {
                text[i] = 'a' + (text[i] - 'a' + shift) % 26;
            }
            else {
                text[i] = 'A' + (text[i] - 'A' + shift) % 26;
            }
        }
        else if (text[i] >= '0' && text[i] <= '9') {
            // Untuk angka
            text[i] = '0' + (text[i] - '0' + shift) % 10;
        }
        i++;
    }
}

// Fungsi untuk melakukan dekripsi Caesar cipher
void caesarDecrypt(char* text, int shift) {
    int i = 0;
    while (text[i] != '\0') {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z')) {
            // Untuk huruf
            if (text[i] >= 'a' && text[i] <= 'z') {
                text[i] = 'a' + (text[i] - 'a' - shift + 26) % 26;
            }
            else {
                text[i] = 'A' + (text[i] - 'A' - shift + 26) % 26;
            }
        }
        else if (text[i] >= '0' && text[i] <= '9') {
            // Untuk angka
            text[i] = '0' + (text[i] - '0' - shift + 10) % 10;
        }
        i++;
    }
}

// Fungsi untuk menyimpan data pengguna ke dalam file
void simpanCredential(struct User user) {
    FILE* file = fopen("credentials.txt", "a");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file\n");
        exit(1);
    }

    // Lakukan enkripsi pada username dan password sebelum disimpan
    caesarEncrypt(user.username, 3); // Misalnya menggunakan Caesar cipher dengan shift 3
    caesarEncrypt(user.password, 3); // Misalnya menggunakan Caesar cipher dengan shift 3

    fprintf(file, "%s %s\n", user.username, user.password);

    fclose(file);
}

// Fungsi untuk mengecek apakah username telah terdaftar sebelumnya
int cekUsername(char* username, char* password) {
    FILE* file = fopen("credentials.txt", "r");
    if (file == NULL) {
        return 0; // File kosong, username belum terdaftar
    }

    char existingUsername[100];
    char existingPassword[100];

    while (fscanf(file, "%s %s", existingUsername, existingPassword) != EOF) {
        // Dekripsi username dari cipher text sebelum membandingkan
        caesarDecrypt(existingUsername, 3); // Misalnya menggunakan Caesar cipher dengan shift 3
        caesarDecrypt(existingPassword, 3); // Misalnya menggunakan Caesar cipher dengan shift 3

        if (strcmp(username, existingUsername) == 0 && strcmp(password, existingPassword) == 0) {
            fclose(file);
            return 1; // Username dan password cocok
        }
    }

    fclose(file);
    return 0; // Username atau password tidak cocok
}

// Fungsi untuk melakukan proses login
void login() {
    char inputUsername[100];
    char inputPassword[100];

    printf("\nLogin\n");
    printf("Input username: ");
    scanf("%s", inputUsername);
    printf("Input password: ");
    scanf("%s", inputPassword);

    // Periksa apakah username dan password cocok
    if (cekUsername(inputUsername, inputPassword)) {
        printf("Login berhasil. Selamat datang, %s!\n", inputUsername);
    }
    else {
        printf("Login gagal. Username atau password salah.\n");
    }
}

// Fungsi untuk melakukan proses registrasi
void registrasi() {
    struct User newUser;

    printf("\nRegistrasi\n");
    printf("Input username: ");
    scanf("%s", newUser.username);

    // Periksa apakah username sudah terdaftar
    if (cekUsername(newUser.username, NULL)) {
        printf("Username telah terdaftar. Silakan gunakan username lain.\n");
    }
    else {
        printf("Input password: ");
        scanf("%s", newUser.password);

        // Simpan username dan password ke dalam file dengan enkripsi Caesar cipher
        simpanCredential(newUser);

        printf("Registrasi berhasil. Silakan login.\n");
    }

}
