#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <ctype.h>
#include <stdbool.h>
#include "header.h"

// Fungsi untuk melakukan enkripsi Caesar cipher
void caesarEncrypt(char* text, int shift) {
    int i = 0;
    while (text[i] != '\0') {
        // Periksa apakah karakter merupakan huruf, angka, atau simbol
        if (isalpha(text[i]) || isdigit(text[i]) || ispunct(text[i])) {
            // Untuk huruf
            if (isalpha(text[i])) {
                // Atur batas atas dan bawah sesuai dengan huruf besar atau kecil
                char upperLimit = isupper(text[i]) ? 'Z' : 'z';
                char lowerLimit = isupper(text[i]) ? 'A' : 'a';
                text[i] = lowerLimit + (text[i] - lowerLimit + shift) % 26;
            }
            // Untuk angka
            else if (isdigit(text[i])) {
                text[i] = '0' + (text[i] - '0' + shift) % 10;
            }
            // Untuk simbol
            else if (ispunct(text[i])) {
                // Kita tambahkan 32 sebagai shift tambahan untuk simbol
                text[i] = '!' + (text[i] - '!' + shift) % 94;
            }
        }
        i++;
    }
}

// Fungsi untuk menghasilkan kunci RSA dan mengenkripsinya sebelum disimpan
RSAkey genEncryptedRSAkeys() {
    RSAkey key = genRSAkeys();

    // Lakukan enkripsi pada kunci RSA
    char privateKeyStr[20], publicKeyStr[20], productStr[20];
    sprintf(privateKeyStr, "%I64u", key.privateKey);
    sprintf(publicKeyStr, "%I64u", key.publicKey);
    sprintf(productStr, "%I64u", key.product);

    caesarEncrypt(privateKeyStr, 3); // Misalnya menggunakan Caesar cipher dengan shift 3
    caesarEncrypt(publicKeyStr, 3); // Misalnya menggunakan Caesar cipher dengan shift 3
    caesarEncrypt(productStr, 3); // Misalnya menggunakan Caesar cipher dengan shift 3

    sscanf(privateKeyStr, "%I64u", &key.privateKey);
    sscanf(publicKeyStr, "%I64u", &key.publicKey);
    sscanf(productStr, "%I64u", &key.product);

    return key;
}

// Fungsi untuk melakukan dekripsi Caesar cipher
void caesarDecrypt(char* text, int shift) {
    int i = 0;
    while (text[i] != '\0') {
        // Periksa apakah karakter merupakan huruf, angka, atau simbol
        if (isalpha(text[i]) || isdigit(text[i]) || ispunct(text[i])) {
            // Untuk huruf
            if (isalpha(text[i])) {
                // Atur batas atas dan bawah sesuai dengan huruf besar atau kecil
                char upperLimit = isupper(text[i]) ? 'Z' : 'z';
                char lowerLimit = isupper(text[i]) ? 'A' : 'a';
                text[i] = lowerLimit + (text[i] - lowerLimit - shift + 26) % 26;
            }
            // Untuk angka
            else if (isdigit(text[i])) {
                text[i] = '0' + (text[i] - '0' - shift + 10) % 10;
            }
            // Untuk simbol
            else if (ispunct(text[i])) {
                // Kita tambahkan 32 sebagai shift tambahan untuk simbol
                text[i] = '!' + (text[i] - '!' - shift + 94) % 94;
            }
        }
        i++;
    }
}


// Fungsi untuk membuat folder baru dengan nama username di dalam folder 'user'
int createFolder(const char* username) {
    // Buat folder dengan menggunakan mkdir
    char path[256]; // Path untuk folder pengguna
    sprintf(path, "user\\%s", username); // Path lengkap ke folder pengguna di dalam folder 'user'

    if (mkdir(path) == -1) {
        printf("Error: Tidak dapat membuat folder\n");
        return 0;
    }
    return 1;
}

// Fungsi untuk menyimpan data pengguna ke dalam file
void simpanCredential(struct User user, RSAkey key) {

    // Buat folder baru dengan nama username menggunakan modul createFolder
    if (!createFolder(user.username)) {
        exit(1);
    }

    FILE* file = fopen("credentials.txt", "a");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file\n");
        exit(1);
    }
    historyregistered(user.username);
    // Lakukan enkripsi pada username, password, dan kunci RSA sebelum disimpan
    caesarEncrypt(user.username, 3); // Misalnya menggunakan Caesar cipher dengan shift 3
    caesarEncrypt(user.password, 3); // Misalnya menggunakan Caesar cipher dengan shift 3

    RSAkey encryptedKey = genEncryptedRSAkeys();

    // Simpan username, password, dan kunci RSA yang sudah dienkripsi ke dalam file
    fprintf(file, "%s %s %I64u %I64u %I64u\n", user.username, user.password, encryptedKey.privateKey, encryptedKey.publicKey, encryptedKey.product);
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
        historylogin(inputUsername);
    }
    else {
        printf("Login gagal. Username atau password salah.\n");
    }
}

// Fungsi untuk memeriksa apakah string mengandung setidaknya satu huruf besar
bool containsUppercase(char* str) {
    while (*str) {
        if (isupper(*str)) {
            return true;
        }
        str++;
    }
    return false;
}

// Fungsi untuk memeriksa apakah string mengandung setidaknya satu angka
bool containsDigit(char* str) {
    while (*str) {
        if (isdigit(*str)) {
            return true;
        }
        str++;
    }
    return false;
}

// Fungsi untuk memeriksa apakah string mengandung setidaknya satu simbol
bool containsSymbol(char* str) {
    while (*str) {
        if (!isalnum(*str)) {
            return true;
        }
        str++;
    }
    return false;
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
        return;
    }

    printf("Input password: ");
    scanf("%s", newUser.password);

    // Validasi password
    if (strlen(newUser.password) < 8 || !containsUppercase(newUser.password) || !containsDigit(newUser.password) || !containsSymbol(newUser.password)) {
        printf("Password harus terdiri dari minimal 8 karakter, minimal satu huruf besar, satu angka, dan satu simbol.\n");
        return;
    }


    // Simpan kunci RSA
    RSAkey key = genRSAkeys();

    // Simpan username, password, dan kunci RSA ke dalam file dengan enkripsi Caesar cipher
    simpanCredential(newUser, key);

    // Tampilkan kunci RSA
    printf("Public key: %llu\nPrivate key: %llu\nProduct: %llu\n\n", key.publicKey, key.privateKey, key.product);

    printf("Registrasi berhasil. Silakan login.\n");
}
