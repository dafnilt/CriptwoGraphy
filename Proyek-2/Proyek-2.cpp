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
        printf("MENU\n1. Login\n2. Registrasi\n3. Tampilkan Direktori\n4. Generate Key\n5. History List\n6. Hentikan Program\nMasukan pilihan anda : ");
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
            system("cls");
            int menu;
            char* isifile;
            puts("1. History Login\n2. History Register akun\n3. History Enkrip\n4. History Dekrip");
            scanf("%d", &menu);
            switch (menu) {
            case 1 : 
                system("cls");
                isifile = bacafile("historylogin.txt");
                if (isifile != NULL) {
                    printf("%s", isifile);
                }
                break;
            case 2:
                system("cls");
                isifile = bacafile("historyregister.txt");
                if (isifile != NULL) {
                    printf("%s", isifile);
                }
                break;
            case 3:
                system("cls");
                isifile = bacafile("historyenkrip.txt");
                if (isifile != NULL) {
                    printf("%s", isifile);
                }
                break;
            case 4:
                system("cls");
                isifile = bacafile("historydekrip.txt");
                if (isifile != NULL) {
                    printf("%s", isifile);
                }
                break;
            }
            printf("\nMasukan karakter apapun untuk melanjutkan ");
            scanf(" %c", &cont);
            break;
        default:
            return 0;
        }
    }
    return 0;
}