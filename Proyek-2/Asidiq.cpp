#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include "header.h"

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

void firstmodul(unsigned long long int e, unsigned long long int n, char q[]) {
    char path[] = "Direktori";
    char filenames[100][256];
    int file_count;

    printf("Daftar file dalam direktori:\n");
    listFiles(path, filenames, &file_count);

    if (file_count == 0) {
        printf("Tidak ada file dalam direktori.\n");
        return;
    }

    for (int i = 0; i < file_count; i++) {
        printf("%d. %s\n", i + 1, filenames[i]);
    }

    printf("\nMasukkan indeks file yang ingin Anda enkripsi: ");
    int index;
    scanf("%d", &index);
    getchar();

    if (index >= 1 && index <= file_count) {
        char selectedFilename[256];
        strcpy(selectedFilename, filenames[index - 1]);
        printf("Anda memilih file: %s\n", selectedFilename);

        char filepath[256];
        snprintf(filepath, sizeof(filepath), "%s/%s", path, selectedFilename);

        FILE* file = fopen(filepath, "r");
        if (file == NULL) {
            printf("Gagal membuka file.");
            return;
        }
        recordHistory(q, selectedFilename);
        char pesan[100];
        fgets(pesan, sizeof(pesan), file);
        if (pesan[strlen(pesan) - 1] == '\n')
            pesan[strlen(pesan) - 1] = '\0';

        printf("Isi file: %s\n", pesan);

        // Mengisi cipher dengan nilai ASCII dari pesan yang dienkripsi
        unsigned long long int cipher[100]; // Maksimal 100 karakter
        int length = 0; // Menyimpan panjang pesanInteger
        for (int i = 0; i < strlen(pesan); i++) {
            cipher[length++] = fastExponentiation(pesan[i], e, n);
        }

        // Menampilkan hasil enkripsi
        printf("Cipher : ");
        for (int i = 0; i < length; i++) {
            printf("%llu", cipher[i]); // Tampilkan cipher ASCII dengan spasi sebagai pemisah
        }
        printf("\n");

        // Simpan cipher ke dalam file dengan nama yang sama di folder "user/(username)"
        char userFolder[256];
        snprintf(userFolder, sizeof(userFolder), "user/%s", q);
        char encryptedFilename[256];
        snprintf(encryptedFilename, sizeof(encryptedFilename), "%s/%s", userFolder, selectedFilename);
        FILE* encryptedFile = fopen(encryptedFilename, "w");
        if (encryptedFile == NULL) {
            printf("Gagal membuat atau membuka file untuk menyimpan cipher.");
            return;
        }

        for (int i = 0; i < length; i++) {
            fprintf(encryptedFile, "%llu ", cipher[i]); // Tulis cipher ke file dengan spasi sebagai pemisah
        }

        fclose(encryptedFile);

    }
    else {
        printf("Indeks file tidak valid.\n");
        return;
    }
}
