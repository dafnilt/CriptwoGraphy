#pragma warning(disable : 4996)
#pragma once
#ifndef header_h
#define header_h
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include "dirent.h"
#include <string.h>
#include <time.h>
#include <random>
#include <stdint.h>
#include <direct.h>
#include <ctype.h>
#include <stdbool.h>



#define MAX_FILE_SIZE 1024

#define MAX 5000




typedef struct {
    uint64_t privateKey;
    uint64_t publicKey;
    uint64_t product;
}RSAkey;

// Struktur data untuk menyimpan informasi pengguna
struct User{
    char username[100];
    char password[100];
    char encryptedPrivateKey[100];
    char encryptedPublicKey[100];
    char encryptedProduct[100];
    RSAkey key; // RSA keys added
    bool isValid; // Indicates whether the user is valid or not
};

//Untuk menyimpan kunci RSA dan username
typedef struct {
    RSAkey key;
    char username[100];
} LoginResult;

typedef struct {
    char ussr[];
} akun;

typedef struct {
    char user[10][100];
    time_t history[];
} timestamps;






// Fungsi untuk mengenkripsi string menggunakan Caesar cipher
void caesarEncrypt(char* text, int shift);

// Fungsi untuk melakukan dekripsi Caesar cipher
void caesarDecrypt(char* text, int shift);

// Modul untuk dekripsi kunci RSA
RSAkey decryptRSAkeys(RSAkey encryptedKey);

// Fungsi untuk menghasilkan kunci RSA dan mengenkripsinya sebelum disimpan
RSAkey genEncryptedRSAkeys();


// Fungsi untuk membuat folder baru dengan nama username
int createFolder(const char* username);

// Fungsi untuk menyimpan data pengguna ke dalam file
void simpanCredential (struct User user, RSAkey key);

// Fungsi untuk mengecek apakah username telah terdaftar sebelumnya
struct User cekUsername(char* username);

// Fungsi untuk melakukan proses login dan mengembalikan kunci RSA dan username yang sesuai
LoginResult login();

// Prosedur untuk melakukan registrasi
void registrasi();

// Fungsi untuk memeriksa apakah string mengandung setidaknya satu huruf besar
bool containsUppercase(char* str);

// Fungsi untuk memeriksa apakah string mengandung setidaknya satu angka
bool containsDigit(char* str);

// Fungsi untuk memeriksa apakah string mengandung setidaknya satu simbol
bool containsSymbol(char* str);

// Fungsi untuk melakukan pemangkatan dengan eksponensiasi cepat
unsigned long long int fastExponentiation(unsigned long long int basis, unsigned long long int pemangkat, unsigned long long int modulus);

// Fungsi untuk mendekripsi cipher menjadi pesan
void decryptToString(unsigned long long int cipher[], int length, unsigned long long int d, unsigned long long int n);

// Fungsi untuk mengembalikan hasil dari modul pertama
void firstmodul(unsigned long long int e, unsigned long long int n, char q[]);

// Fungsi untuk melakukan pemangkatan dengan eksponensiasi cepat
uint64_t modExpo(uint64_t base, uint64_t power, uint64_t divisor);

// Fungsi untuk menghitung fungsi phi Euler
uint64_t phi(uint64_t prime1, uint64_t prime2);

// Fungsi untuk melakukan uji keprimaan Miller-Rabin
bool millerRabinTest(uint64_t n, uint64_t i);

// Fungsi untuk menguji apakah suatu bilangan prima
bool isPrime(uint64_t number);

// Fungsi untuk menghasilkan bilangan prima dalam rentang tertentu
uint64_t genPrime(uint64_t lowerBound, uint64_t upperBound);

// Fungsi untuk menghasilkan kunci privat
uint64_t genPrivateKey(uint64_t totient);

//function untuk mencari modular multiplicative inverse menggunakan extended euclidian alg
//dan menghitung GCD(greatest common divisor)(FPB) menggunakan euclidian alg
uint64_t euclidianAlg(uint64_t s, uint64_t l, int64_t prevRemainder, int64_t* t1, int64_t* t2);

//function euclidianAlg dengan validator dan tambahan program jika hasil t1 negatif 
uint64_t modInverse(uint64_t s, uint64_t l);

//function yang mengenerate private key, public key, dan product (perkalian 2 bil prima)
RSAkey genRSAkeys();

//procedure dekripsi file yang terenkripsi dan print isinya ke layar
void fileDecrypt(LoginResult info);

void listFiles(const char* path, char filenames[][256], int* file_count);
void displayFileContent(const char* path, const char* filename);

void show_files(const char* directory_path);
char* choose_file(const char* directory_path, int selected_file_index);

void mainLogic();

void recordHistory(char username[], char filename[]); 

void getCurrentTime(char *timeString);

void historylogin(char *username);

void historyregistered(char *username);

char* bacafile(const char* file_path);


#endif
