#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include "header.h"
#include <windows.h>
#include <conio.h>

// Fungsi untuk melakukan pemangkatan dengan eksponensiasi cepat
unsigned long long int fastExponentiation(unsigned long long int basis, unsigned long long int pemangkat, unsigned long long int modulus) {
    unsigned long long int hasil = 1;
    basis = basis % modulus;
    while (pemangkat > 0) {
        if (pemangkat % 2 == 1) // Jika eksponen ganjil
            hasil = (hasil * basis) % modulus;
        pemangkat /= 2; // Mengurangi eksponen menjadi setengah
        basis = (basis * basis) % modulus; // Melakukan perkalian basis dengan dirinya sendiri
    }
    return hasil;
}

// Fungsi untuk mendekripsi cipher menjadi pesan
void decryptToString(unsigned long long int cipher[], int length, unsigned long long int d, unsigned long long int n) {
    for (int i = 0; i < length; i++) {
        unsigned long long int decrypted = fastExponentiation(cipher[i], d, n);
        printf("%c", decrypted); // Menampilkan karakter yang sesuai dengan kode ASCII
    }
    puts("");
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Backspace() {
    int key;
    do {
        key = getch();
    } while (key != 8); // 8 adalah kode ASCII untuk backspace
}