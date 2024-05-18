#pragma warning(disable : 4996)
#pragma once
#ifndef Asidiq_h
#define Asidiq_h
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "dirent.h"
#include <string.h>
#include <time.h>
#include <random>
#include <stdint.h>
#include <direct.h>
#include <ctype.h>
#include <stdbool.h>
#include "header.h"

#define RESET "\033[0m" // Reset semua gaya dan warna teks ke default.
#define BOLD "\033[1m" // Bold (tebal).
#define REDUP "\033[2m" // teks jadi redup.
#define ITALIC "\033[3m" // Italic (miring).
#define Uline "\033[4m" // Underline (garis bawah).
#define KEDIP "\033[5m" // teks kedap-kedip.
#define BCOLOR "\033[7m" // background menyesuaikan warna teks.
#define GONE "\033[8m" // Menghilangkan teks.
#define CORET "\033[9m" // Mencoret teks.
#define BLACK "\033[30m" // Warna teks hitam.
#define RED "\033[31m" // Warna teks merah.
#define GREEN "\033[1;32m" // Warna teks hijau.
#define YELLOW "\033[33m" // Warna teks kuning.
#define BLUE "\033[34m" // Warna teks biru.
#define PURPLE "\033[35m" // Warna teks ungu.
#define CYAN "\033[36m" // Warna teks cyan/biru muda.
#define WHITE "\033[37m" // Warna teks putih.
#define BBLACK "\033[40m" // Warna latar belakang hitam.
#define BRED "\033[41m" // Warna latar belakang merah.
#define BGREEN "\033[42m" // Warna latar belakang hijau.
#define BYELLOW "\033[43m" // Warna latar belakang kuning.
#define BBLUE "\033[44m" // Warna latar belakang biru.
#define BPURPLE "\033[45m" // Warna latar belakang ungu.
#define BCYAN "\033[46m" // Warna latar belakang cyan.
#define BWHITE "\033[47m"  // Warna latar belakang putih.


// Fungsi untuk melakukan pemangkatan dengan eksponensiasi cepat
unsigned long long int fastExponentiation(unsigned long long int basis, unsigned long long int pemangkat, unsigned long long int modulus);

// Fungsi untuk mendekripsi cipher menjadi pesan
void decryptToString(unsigned long long int cipher[], int length, unsigned long long int d, unsigned long long int n);

// Fungsi untuk mengembalikan hasil dari modul pertama
void firstmodul(unsigned long long int e, unsigned long long int n, char q[]);

#endif
