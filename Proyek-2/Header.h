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

    //#define MAXrng 50000 reivan
//test

    /*
    typedef struct {
        uint64_t privateKey;
        uint64_t publicKey;
        uint64_t product;
    }RSAkey;                    reivan
    */

typedef struct {
    char user[10][100];
    time_t history[];
} timestamps;

// Fungsi untuk melakukan pemangkatan dengan eksponensiasi cepat
unsigned long long int fastExponentiation(unsigned long long int basis, unsigned long long int pemangkat, unsigned long long int modulus);

// Fungsi untuk mendekripsi cipher menjadi pesan
void decryptToString(unsigned long long int cipher[], int length, unsigned long long int d, unsigned long long int n);

// Fungsi untuk mengembalikan hasil dari modul pertama
void firstmodul(unsigned long long int e, unsigned long long int n, char q[]);


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

void recordHistorydekrip(char username[], char filename[]);

#endif
