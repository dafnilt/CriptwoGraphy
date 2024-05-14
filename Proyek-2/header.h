#pragma warning(disable : 4996)
#pragma once
#ifndef header_h
#define header_h

#include <stdint.h>
#include <time.h>

typedef struct {
    uint64_t privateKey;
    uint64_t publicKey;
    uint64_t product;
}RSAkey;

typedef struct followLs {
    char username[100];
    struct followLs* next;
}followLs;

typedef followLs* fAddress;

typedef struct userLs {
    char username[100];
    struct userLs* nextUser;
    fAddress follow;
}userLs;

typedef userLs* uAddress;


// Struktur data untuk menyimpan informasi pengguna
struct User {
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


// Definisi struktur untuk menyimpan kunci RSA yang telah dienkripsi
struct EncryptedRSAKeys {
    char privateKey[20];
    char publicKey[20];
    char product[20];
};



typedef struct {
    char user[10][100];
    time_t history[];
} timestamps;

typedef struct prvuser *pointer;
typedef struct prvuser {
    char info[100];
    pointer prev;
    pointer next;
}us;

typedef struct {
    pointer First;
}list;

/*
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
*/


//#define MAX_FILE_SIZE 1024

    //#define MAXrng 50000 reivan
//test

    /*
    typedef struct {
        uint64_t privateKey;
        uint64_t publicKey;
        uint64_t product;
    }RSAkey;                    reivan
    */






    /*
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
            
            reivan
    */
/*
void listFiles(const char* path, char filenames[][256], int* file_count);
void displayFileContent(const char* path, const char* filename);

void show_files(const char* directory_path);
char* choose_file(const char* directory_path, int selected_file_index);

void mainLogic();
*/

#endif
