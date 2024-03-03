#include <stdio.h>
#include <string.h>
#include "header.h"
#pragma warning(disable : 4996)

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
}

int firstmodul() {
    int p = 7, q = 19;
    unsigned long long int n, t;
    unsigned long long int e = 29, d = 41; // Menggunakan unsigned long long int agar tidak mendapatkan desimal pada hasil pangkat
    char pesan[100];

    printf("angka prima untuk p: %d\n", p);
    printf("angka prima untuk q: %d\n", q);

    n = (unsigned long long int)p * q;
    printf("hasil n: %llu\n", n);

    t = ((unsigned long long int)p - 1) * ((unsigned long long int)q - 1);
    printf("hasil t: %llu\n", t);

    // Membaca public key dari pengguna
    printf("masukkan pesan: ");
    scanf("%llu", &e);

    // Menghitung private key (d) menggunakan algoritma extended Euclidean
    // Saya asumsikan pengguna memberikan nilai e yang valid sehingga memiliki invers modulo t
    unsigned long long int k = 1;
    while (1) {
        if ((1 + k * t) % e == 0) {
            d = (1 + k * t) / e;
            break;
        }
        k++;
    }

    printf("Masukkan pesan: ");
    fgets(pesan, sizeof(pesan), stdin); // Membaca string hingga menemui karakter baris baru

    // Menghilangkan karakter baris baru dari input
    if (pesan[strlen(pesan) - 1] == '\n')
        pesan[strlen(pesan) - 1] = '\0';

    // Menampilkan nilai ASCII dari setiap karakter dalam pesan
    printf("ASCII: ");
    for (int i = 0; i < strlen(pesan); i++) {
        printf("%d ", pesan[i]); // Tampilkan nilai ASCII dengan spasi sebagai pemisah
    }
    printf("\n");

    // Mengisi pesanInteger dengan nilai ASCII dari pesan
    unsigned long long int cipher[100]; // Maksimal 100 karakter
    int length = 0; // Menyimpan panjang pesanInteger
    for (int i = 0; i < strlen(pesan); i++) {
        cipher[length++] = fastExponentiation(pesan[i], e, n); // Mengisi array cipher dengan nilai ASCII yang dienkripsi
    }

    // Menampilkan hasil enkripsi
    printf("Maka, ciphernya adalah ");
    for (int i = 0; i < length; i++) {
        printf("%llu ", cipher[i]); // Tampilkan cipher ASCII dengan spasi sebagai pemisah
    }
    printf("\n");

    // Melakukan dekripsi pesan
    printf("Contoh dekripsi: ");
    decryptToString(cipher, length, d, n);

    printf("\n");

    return 0;
}