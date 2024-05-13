#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Reivan.h"
#include "header.h"

int main() {
    char cont;
    int choice;
    const char* dir = "test";
    LoginResult p;

    for (;;) {
        system("cls");
        printf("\n\t\t\t\t\t==========================================\n");
        printf("\t\t\t\t\t||		CRYPTWOGRAPHY   	||\n");
        printf("\t\t\t\t\t==========================================\n");
        printf("MENU\n1. Login\n2. Registrasi\n3. History List\n4. Hentikan Program\nMasukan pilihan anda : ");
        scanf("%d", &choice);
        system("cls");
        switch (choice)
        {
        case 1:
            p = login();
            while (1) {
                printf("\n1. Enkrip File dari folder directory\n2. Dekrip File dari Folder User\n3. Keluar\n");
                printf("Pilih indeks menu :");
                int B;
                scanf("%d", &B);
                switch (B) {
                case 1:
                    system("cls");
                    firstmodul(p.key.privateKey, p.key.product, p.username);
                    break;
                case 2:
                    system("cls");
                    fileDecrypt(p);
                    break;
                case 3:
                    printf("Keluar dari menu.\n");
                    break;
                default:
                    system("cls");
                    puts("");
                    printf("Pilihan tidak valid.\n");
                }
                if (B == 3) 
                    break;
            }
            printf("\n");
      
            break;
        case 2:
            registrasi();
            printf("\nMasukan karakter apapun untuk melanjutkan ");
            scanf(" %c", &cont);
            break;
        case 3:
            int menu;
            char* isifile;
            while (1) {
                puts("1. History Login\n2. History Register akun\n3. History Enkrip\n4. History Dekrip\n5. Kembali ke menu sebelumnya");
                scanf("%d", &menu);
                switch (menu) {
                case 1:
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
                default: 
                    system("cls");
                }
                if (menu == 5) {
                    break;
                }
            }
            break;
        default:
            return 0;
        }
    }
    return 0;
}