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
        if (isalpha(text[i]) || isdigit(text[i]) || ispunct(text[i])) {
            if (isalpha(text[i])) {
                char upperLimit = isupper(text[i]) ? 'Z' : 'z';
                char lowerLimit = isupper(text[i]) ? 'A' : 'a';
                text[i] = lowerLimit + (text[i] - lowerLimit + shift) % 26;
            }
            else if (isdigit(text[i])) {
                text[i] = '0' + (text[i] - '0' + shift) % 10;
            }
            else if (ispunct(text[i])) {
                text[i] = '!' + (text[i] - '!' + shift) % 94;
            }
        }
        i++;
    }
}

// Fungsi untuk melakukan dekripsi Caesar cipher
void caesarDecrypt(char* text, int shift) {
    int i = 0;
    while (text[i] != '\0') {
        if (isalpha(text[i]) || isdigit(text[i]) || ispunct(text[i])) {
            if (isalpha(text[i])) {
                char upperLimit = isupper(text[i]) ? 'Z' : 'z';
                char lowerLimit = isupper(text[i]) ? 'A' : 'a';
                text[i] = lowerLimit + (text[i] - lowerLimit - shift + 26) % 26;
            }
            else if (isdigit(text[i])) {
                text[i] = '0' + (text[i] - '0' - shift + 10) % 10;
            }
            else if (ispunct(text[i])) {
                text[i] = '!' + (text[i] - '!' - shift + 94) % 94;
            }
        }
        i++;
    }
}


// Fungsi untuk menghasilkan kunci RSA dan mengenkripsinya sebelum disimpan
RSAkey genEncryptedRSAkeys() {
    RSAkey key = genRSAkeys();

    // Cetak kunci RSA sebelum dienkripsi
    printf("Public Key (Sebelum Enkripsi): %llu\nPrivate Key (Sebelum Enkripsi): %llu\nProduct (Sebelum Enkripsi): %llu\n\n", key.publicKey, key.privateKey, key.product);

    // Lakukan enkripsi pada kunci RSA
    char privateKeyStr[20], publicKeyStr[20], productStr[20];
    sprintf(privateKeyStr, "%llu", key.privateKey);
    sprintf(publicKeyStr, "%llu", key.publicKey);
    sprintf(productStr, "%llu", key.product);

    caesarEncrypt(privateKeyStr, 3);
    caesarEncrypt(publicKeyStr, 3);
    caesarEncrypt(productStr, 3);

    sscanf(privateKeyStr, "%llu", &key.privateKey);
    sscanf(publicKeyStr, "%llu", &key.publicKey);
    sscanf(productStr, "%llu", &key.product);

    // Cetak kunci RSA yang sudah dienkripsi
    printf("Encrypted RSA Key:\n");
    printf("Private Key: %llu\n", key.privateKey);
    printf("Public Key: %llu\n", key.publicKey);
    printf("Product: %llu\n", key.product);

    return key;
}

// Fungsi untuk melakukan dekripsi kunci RSA yang dibaca dari file
RSAkey decryptRSAkeysFromFile(char* encryptedPrivateKey, char* encryptedPublicKey, char* encryptedProduct) {
    RSAkey decryptedKey;

    // Parse encrypted keys from strings to integers
    sscanf(encryptedPrivateKey, "%llu", &decryptedKey.privateKey);
    sscanf(encryptedPublicKey, "%llu", &decryptedKey.publicKey);
    sscanf(encryptedProduct, "%llu", &decryptedKey.product);

    // Dekripsi kunci RSA
    caesarDecrypt(encryptedPrivateKey, 3);
    caesarDecrypt(encryptedPublicKey, 3);
    caesarDecrypt(encryptedProduct, 3);

    // Parse decrypted keys from strings to integers
    sscanf(encryptedPrivateKey, "%llu", &decryptedKey.privateKey);
    sscanf(encryptedPublicKey, "%llu", &decryptedKey.publicKey);
    sscanf(encryptedProduct, "%llu", &decryptedKey.product);

    return decryptedKey;
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


// Fungsi untuk menyimpan kredensial pengguna ke dalam file
void simpanCredential(struct User user, RSAkey key) {
    if (!createFolder(user.username)) {
        exit(1);
    }

    FILE* file = fopen("credentials.txt", "a");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file\n");
        exit(1);
    }

    caesarEncrypt(user.username, 3);
    caesarEncrypt(user.password, 3);

    RSAkey encryptedKey = genEncryptedRSAkeys();

    fprintf(file, "%s %s %I64u %I64u %I64u\n", user.username, user.password, encryptedKey.privateKey, encryptedKey.publicKey, encryptedKey.product);
    fclose(file);
}

// Fungsi untuk memeriksa apakah username telah terdaftar sebelumnya
struct User cekUsername(char* username) {
    FILE* file = fopen("credentials.txt", "r");
    struct User user;
    user.isValid = false;

    if (file == NULL) {
        printf("Error: Tidak dapat membuka file credentials.txt\n");
        exit(1);
    }

    char existingUsername[100];
    char existingPassword[100];
    char encryptedPrivateKey[100], encryptedPublicKey[100], encryptedProduct[100];

    // Baca baris demi baris dari file credentials.txt
    while (fscanf(file, "%s %s %s %s %s", existingUsername, existingPassword, encryptedPrivateKey, encryptedPublicKey, encryptedProduct) != EOF) {
        // Dekripsi username dan password
        caesarDecrypt(existingUsername, 3);
        caesarDecrypt(existingPassword, 3);

        // Jika username cocok dengan yang dicari
        if (strcmp(username, existingUsername) == 0) {
            // Isi informasi pengguna
            strcpy(user.username, existingUsername);
            strcpy(user.password, existingPassword);

            // Simpan kunci RSA yang dienkripsi
            strcpy(user.encryptedPrivateKey, encryptedPrivateKey);
            strcpy(user.encryptedPublicKey, encryptedPublicKey);
            strcpy(user.encryptedProduct, encryptedProduct);

            user.isValid = true;

            // Keluar dari loop setelah menemukan username yang cocok
            break;
        }
    }

    fclose(file);
    return user;
}

// Fungsi untuk login
LoginResult login() {
    LoginResult result;
    char inputUsername[100];
    char inputPassword[100];

    printf("\nLogin\n");
    printf("Input username: ");
    scanf("%s", inputUsername);
    printf("Input password: ");
    scanf("%s", inputPassword);

    struct User loggedInUser = cekUsername(inputUsername);
    if (loggedInUser.isValid) {
        printf("Login berhasil. Selamat datang, %s!\n", inputUsername);
        historylogin(inputUsername);

        // Print nilai kunci RSA sebelum dekripsi
        printf("Encrypted RSA Key:\n");
        printf("Private Key: %s\n", loggedInUser.encryptedPrivateKey);
        printf("Public Key: %s\n", loggedInUser.encryptedPublicKey);
        printf("Product: %s\n", loggedInUser.encryptedProduct);

        // Dekripsi kunci RSA
        RSAkey decryptedKey = decryptRSAkeysFromFile(loggedInUser.encryptedPrivateKey, loggedInUser.encryptedPublicKey, loggedInUser.encryptedProduct);

        // Print nilai kunci RSA setelah dekripsi
        printf("Decrypted RSA Key:\n");
        printf("Private Key: %llu\n", decryptedKey.privateKey);
        printf("Public Key: %llu\n", decryptedKey.publicKey);
        printf("Product: %llu\n", decryptedKey.product);

        strcpy(result.username, inputUsername);
        result.key = decryptedKey;

        return result;
    }
    else {
        printf("Login gagal. Username atau password salah.\n");
        exit(1);
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



// Fungsi untuk melakukan proses registrasi
void registrasi() {
    struct User newUser;

    printf("\nRegistrasi\n");
    printf("Input username: ");
    scanf("%s", newUser.username);

    if (cekUsername(newUser.username).isValid) {
        printf("Username telah terdaftar. Silakan gunakan username lain.\n");
        return;
    }

    printf("Input password: ");
    scanf("%s", newUser.password);

    if (strlen(newUser.password) < 8) {
        printf("Password harus terdiri dari minimal 8 karakter.\n");
        return;
    }

    if (!containsUppercase(newUser.password) || !containsDigit(newUser.password)) {
        printf("Password harus mengandung setidaknya satu huruf besar dan satu angka.\n");
        return;
    }

    RSAkey key = genRSAkeys();

    simpanCredential(newUser, key);

    // Registrasi berhasil
    printf("Registrasi berhasil. Silakan login.\n");
    historyregistered(newUser.username);
}


