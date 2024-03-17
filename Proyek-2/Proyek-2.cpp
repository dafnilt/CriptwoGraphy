#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main() {
    char cont;
    int choice;
    const char* dir = "test";
    LoginResult p;

    for (;;) {
        system("cls");
        printf("MENU\n1. Login\n2. Registrasi\n3. Tampilkan Direktori\n4. Generate Key\n5. Enkripsi Dekripsi\n6. Hentikan Program\nMasukan pilihan anda : ");
        scanf("%d", &choice);
        system("cls");
        switch (choice)
        {
        case 1:
            p = login();
            printf("\n");
            firstmodul(p.key.privateKey, p.key.product, p.username);
            fileDecrypt(p);
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
            printf("\nMasukan karakter apapun untuk melanjutkan ");
            scanf(" %c", &cont);
            break;
        case 4:
            RSAkey key;
            key = genRSAkeys();
            printf("Public key: %I64u\nPrivate key: %I64u\nProduct: %I64u\n\n", key.privateKey, key.publicKey, key.product);
            printf("\nMasukan karakter apapun untuk melanjutkan ");
            scanf(" %c", &cont);
            break;
        case 5:
            printf("\nMasukan karakter apapun untuk melanjutkan ");
            scanf(" %c", &cont);
            break;
        default:
            return 0;
        }
    }
    return 0;
}