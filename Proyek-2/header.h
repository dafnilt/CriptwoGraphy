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


#define MAX_FILE_SIZE 1024

#define MAX 4294967295

// Struktur data untuk menyimpan informasi pengguna
struct User {
    char username[100];
    char password[100];
};

typedef struct {
    char ussr[];
} akun;

typedef struct {
    char user[10][100];
    time_t history[];
} timestamps;


// Fungsi untuk melakukan enkripsi Caesar cipher
void caesarEncrypt(char *text, int shift);

// Fungsi untuk melakukan dekripsi Caesar cipher
void caesarDecrypt(char *text, int shift);

// Fungsi untuk menyimpan data pengguna ke dalam file
void simpanCredential(struct User user);

// Fungsi untuk mengecek apakah username telah terdaftar sebelumnya
int cekUsername(char *username, char *password);

// Prosedur untuk melakukan login
void login();

// Prosedur untuk melakukan registrasi
void registrasi();

// Fungsi untuk melakukan pemangkatan dengan eksponensiasi cepat
unsigned long long int fastExponentiation(unsigned long long int basis, unsigned long long int pemangkat, unsigned long long int modulus);

// Fungsi untuk mendekripsi cipher menjadi pesan
void decryptToString(unsigned long long int cipher[], int length, unsigned long long int d, unsigned long long int n);

// Fungsi untuk mengembalikan hasil dari modul pertama
int firstmodul();

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
uint64_t genPrivateKey(uint64_t prod, uint64_t totient);

// Fungsi untuk menghitung GCD (FPB) menggunakan algoritma Euclidean
uint64_t gcd(uint64_t s, uint64_t l);

// Fungsi untuk menghasilkan kunci publik
uint64_t genPublicKey(uint64_t privateKey, uint64_t totient);

void show_files(const char* directory_path);
char* choose_file(const char* directory_path, int selected_file_index);
void example_usage();
void mainLogic();

void p_time(const char* filename, timestamps* ts,char username);

#endif
