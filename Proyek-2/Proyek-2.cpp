#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main() {
    char cont;
    int choice;
    const char* dir = "test";
    for (;;) {
        system("cls");
        printf("MENU\n1. Login\n2. Registrasi\n3. Tampilkan Direktori\n4. Generate Private Key\n5. Enkripsi Dekripsi\n6. Hentikan Program\nMasukan pilihan anda : ");
        scanf("%d", &choice);
        system("cls");
        switch (choice)
        {
        case 1:
            login();
            printf("\nMasukan karakter apapun untuk melanjutkan ");
            scanf(" %c", &cont);
            break;
        case 2:
            registrasi();
            printf("\nMasukan karakter apapun untuk melanjutkan ");
            scanf(" %c", &cont);
            break;
        case 3:
            mainLogic();
            break;
        case 4:
            uint64_t p, q, prod, totient, privKey;
            p = genPrime(1, MAX);
            printf("Bilangan prima random p adalah : %I64u\n", p);
            q = genPrime(1, MAX);
            printf("Bilangan prima random q adalah : %I64u\n", q);
            prod = p * q;
            printf("Hasil perkalian p dan q adalah : %I64u\n", prod);
            totient = phi(p, q);
            printf("Phi Euler (Totient) dari p dan q adalah : %I64u\n", totient);
            privKey = genPrivateKey(prod, totient);
            printf("Private key yang dihasilkan adalah : %I64u\n\nMasukan karakter apapun untuk melanjutkan ", privKey);
            scanf(" %c", &cont);
            break;
        case 5:
            firstmodul();
            printf("\nMasukan karakter apapun untuk melanjutkan ");
            scanf(" %c", &cont);
            break;
        default:
            return 0;
        }
    }
    return 0;
}