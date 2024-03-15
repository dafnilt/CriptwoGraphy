#include <stdio.h>
#include <string.h>

unsigned long long int fastExponentiation(unsigned long long int basis, unsigned long long int pemangkat, unsigned long long int modulus) {
    unsigned long long int hasil = 1;
    basis = basis % modulus;
    while (pemangkat > 0) {
        if (pemangkat % 2 == 1)
            hasil = (hasil * basis) % modulus;
        pemangkat /= 2;
        basis = (basis * basis) % modulus;
    }
    return hasil;
}

void removeNewLine(char *string) {
    if (string[strlen(string) - 1] == '\n')
        string[strlen(string) - 1] = '\0';
}

void printASCII(const char *pesan) {
    printf("ASCII: ");
    for (int i = 0; i < strlen(pesan); i++) {
        printf("%d", pesan[i]);
    }
    printf("\n");
}

void encryptMessage(const char *pesan, unsigned long long int e, unsigned long long int n, unsigned long long int cipher[], int *length) {
    *length = 0;
    for (int i = 0; i < strlen(pesan); i++) {
        cipher[(*length)++] = fastExponentiation(pesan[i], e, n);
    }

    printf("Maka, ciphernya adalah ");
    for (int i = 0; i < *length; i++) {
        printf("%llu", cipher[i]);
    }
    printf("\n");
}

void decryptToString(unsigned long long int cipher[], int length, unsigned long long int d, unsigned long long int n) {
    for (int i = 0; i < length; i++) {
        unsigned long long int decrypted = fastExponentiation(cipher[i], d, n);
        printf("%c", decrypted);
    }
    printf("\n");
}

int main() {
    int p = 7, q = 19;
    unsigned long long int n, t;
    unsigned long long int e = 29, d = 41;
    char pesan[100];
    unsigned long long int cipher[100]; // Maksimal 100 karakter
    int length; // Menyimpan panjang pesanInteger

    printf("angka prima untuk p: %d\n", p);
    printf("angka prima untuk q: %d\n", q);

    n = (unsigned long long int)p * q;
    printf("hasil n: %llu\n", n);

    t = ((unsigned long long int)p - 1) * ((unsigned long long int)q - 1);
    printf("hasil t: %llu\n", t);

    printf("Masukkan pesan: ");
    fgets(pesan, sizeof(pesan), stdin);
    removeNewLine(pesan);
    printASCII(pesan);
    encryptMessage(pesan, e, n, cipher, &length);

    printf("Hasil dekripsi: ");
    decryptToString(cipher, length, d, n);

    return 0;
}

