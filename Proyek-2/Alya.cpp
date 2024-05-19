#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <ctype.h>
#include <stdbool.h>
#include "header.h"
#include "alya.h"
#include "Reivan.h"
#include "yazid.h"


// Fungsi untuk melakukan enkripsi Caesar cipher
void caesarEncrypt(char* text, int shift) {
    int i = 0;
    while (text[i] != '\0') {
        if (isalpha(text[i]) || isdigit(text[i])) {
            if (isalpha(text[i])) {
                char upperLimit = isupper(text[i]) ? 'Z' : 'z';
                char lowerLimit = isupper(text[i]) ? 'A' : 'a';
                text[i] = lowerLimit + (text[i] - lowerLimit + shift) % 26;
            }
            else if (isdigit(text[i])) {
                text[i] = '0' + (text[i] - '0' + shift) % 10;
            }
        }
        i++;
    }
}

// Fungsi untuk melakukan dekripsi Caesar cipher
void caesarDecrypt(char* text, int shift) {
    int i = 0;
    while (text[i] != '\0') {
        if (isalpha(text[i]) || isdigit(text[i])) {
            if (isalpha(text[i])) {
                char upperLimit = isupper(text[i]) ? 'Z' : 'z';
                char lowerLimit = isupper(text[i]) ? 'A' : 'a';
                text[i] = lowerLimit + (text[i] - lowerLimit - shift + 26) % 26;
            }
            else if (isdigit(text[i])) {
                text[i] = '0' + (text[i] - '0' - shift + 10) % 10;
            }
        }
        i++;
    }
}



// Fungsi untuk menghasilkan kunci RSA dan mengenkripsinya sebelum disimpan
struct EncryptedRSAKeys genEncryptedRSAkeys() {
    RSAkey key = genRSAkeys();
    struct EncryptedRSAKeys encryptedKeys;

    printf("\n");
    printf("Kunci RSA Anda (Sebelum Enkripsi):\n");
    printf("Private Key: %llu\n", key.privateKey);
    printf("Public Key: %llu\n", key.publicKey);
    printf("Product: %llu\n", key.product);
    printf("\n");

    // Lakukan enkripsi pada kunci RSA
    sprintf(encryptedKeys.privateKey, "%llu", key.privateKey);
    sprintf(encryptedKeys.publicKey, "%llu", key.publicKey);
    sprintf(encryptedKeys.product, "%llu", key.product);

    caesarEncrypt(encryptedKeys.privateKey, 3);
    caesarEncrypt(encryptedKeys.publicKey, 3);
    caesarEncrypt(encryptedKeys.product, 3);

    // Cetak kunci RSA yang sudah dienkripsi
    printf("Encrypted RSA Key:\n");
    printf("Private Key: %s\n", encryptedKeys.privateKey);
    printf("Public Key: %s\n", encryptedKeys.publicKey);
    printf("Product: %s\n", encryptedKeys.product);

    return encryptedKeys;
}

// Fungsi untuk melakukan dekripsi kunci RSA yang dibaca dari file
RSAkey decryptRSAkeysFromFile(struct EncryptedRSAKeys encryptedKeys) {
    RSAkey decryptedKey;

    // Dekripsi kunci RSA
    caesarDecrypt(encryptedKeys.privateKey, 3);
    caesarDecrypt(encryptedKeys.publicKey, 3);
    caesarDecrypt(encryptedKeys.product, 3);

    // Parse decrypted keys from strings to integers
    sscanf(encryptedKeys.privateKey, "%llu", &decryptedKey.privateKey);
    sscanf(encryptedKeys.publicKey, "%llu", &decryptedKey.publicKey);
    sscanf(encryptedKeys.product, "%llu", &decryptedKey.product);

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
void simpanCredential(struct User user, struct EncryptedRSAKeys encryptedKeys) {
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

    fprintf(file, "%s %s %s %s %s\n", user.username, user.password, encryptedKeys.privateKey, encryptedKeys.publicKey, encryptedKeys.product);
    printf("\n");
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


LoginResult login() {
    LoginResult result;
    char inputUsername[100];
    char inputPassword[100];

    printf("\nLogin\n");
    printf("Input username: ");
    scanf("%s", inputUsername);
    printf("Input password: ");
    scanf("%s", inputPassword);

    // Dekripsi username dan password dari file
    struct User loggedInUser = cekUsername(inputUsername);
    if (loggedInUser.isValid) {
        // Cocokkan username yang telah didekripsi dengan input username
        if (strcmp(inputUsername, loggedInUser.username) == 0) {
            // Cocokkan password yang telah didekripsi dengan input password
            if (strcmp(inputPassword, loggedInUser.password) == 0) {
                printf("Login berhasil.\n");
                printf("\n");
                printf("Selamat datang, %s!\n", inputUsername);
                printf("\n");
                historylogin(inputUsername);

                // Print nilai kunci RSA sebelum dekripsi
                printf("Encrypted RSA Key:\n");
                printf("Private Key: %s\n", loggedInUser.encryptedPrivateKey);
                printf("Public Key: %s\n", loggedInUser.encryptedPublicKey);
                printf("Product: %s\n", loggedInUser.encryptedProduct);
                printf("\n");

                // Dekripsi kunci RSA
                struct EncryptedRSAKeys encryptedKeys;
                strcpy(encryptedKeys.privateKey, loggedInUser.encryptedPrivateKey);
                strcpy(encryptedKeys.publicKey, loggedInUser.encryptedPublicKey);
                strcpy(encryptedKeys.product, loggedInUser.encryptedProduct);

                RSAkey decryptedKey = decryptRSAkeysFromFile(encryptedKeys);

                // Print nilai kunci RSA setelah dekripsi
                printf("Decrypted RSA Key:\n");
                printf("Private Key: %llu\n", decryptedKey.privateKey);
                printf("Public Key: %llu\n", decryptedKey.publicKey);
                printf("Product: %llu\n", decryptedKey.product);
                printf("\n");

                strcpy(result.username, inputUsername);
                result.key = decryptedKey;

                return result;
            }
            else {
                printf("Login gagal. Username atau password salah.\n");
                exit(1);
            }
        }
        else {
            printf("Login gagal. Username atau password salah.\n");
            exit(1);
        }
    }
    else {
        printf("Login gagal. Username tidak terdaftar.\n");
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

// Fungsi untuk memeriksa apakah string mengandung setidaknya satu simbol
bool containsSymbol(char* str) {
    while (*str) {
        if (ispunct(*str)) {
            return true;
        }
        str++;
    }
    return false;
}




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
    fflush(stdin); // Membersihkan buffer stdin
    fgets(newUser.password, sizeof(newUser.password), stdin);

    // Memeriksa hasil dari fgets
    if (fgets(newUser.password, sizeof(newUser.password), stdin) == NULL) {
        printf("Gagal membaca input.\n");
        return;
    }


    if (strlen(newUser.password) < 8) {
        printf("Password harus terdiri dari minimal 8 karakter.\n");
        return;
    }

    if (!containsUppercase(newUser.password) || !containsDigit(newUser.password) || !containsSymbol(newUser.password)) {
        printf("Password harus mengandung setidaknya satu huruf besar, satu angka, dan satu simbol.\n");
        return;
    }

    simpanCredential(newUser, genEncryptedRSAkeys());

    // Registrasi berhasil
    printf("Registrasi berhasil. Silakan login.\n");
    historyregistered(newUser.username);


}

// Fungsi untuk mencetak daftar username yang mengikuti pengguna
void printFollowers(uAddress currentUser) {
    printf("Daftar pengguna yang mengikuti %s:\n", currentUser->username);
    fAddress follower = currentUser->follow;
    int index = 1;
    while (follower != NULL) {
        printf("%d. %s\n", index, follower->username);
        follower = follower->next;
        index++;
    }
}

// Fungsi untuk meminta input nomor indeks pengguna lain yang ingin dikirimkan file rahasia
int chooseUser(uAddress currentUser) {
    int index;
    printf("Masukkan nomor indeks pengguna lain yang ingin Anda kirimkan file rahasia: ");
    scanf("%d", &index);
    return index;
}

// Fungsi untuk mengambil public key dari pengguna yang dipilih untuk mengirimkan file
// Jika berhasil, akan mencetak dan mengembalikan public key
//char* getPublicKey(uAddress currentUser, int index) {
//    int currentIndex = 1;
//    uAddress user = currentUser;
//    while (user != NULL) {
//        if (currentIndex == index) {
//            printf("Mengambil public key dari pengguna %s\n", user->username);
//            // Ambil public key dari pengguna user
//            char* publicKey = user->publicKey; // Misalnya publicKey adalah atribut dalam struct userLs
//            printf("Public key dari pengguna %s: %s\n", user->username, publicKey);
//            return publicKey;
//        }
//        user = user->nextUser;
//        currentIndex++;
//    }
//    printf("Nomor indeks tidak valid.\n");
//    return NULL;
//}






