
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "header.h"
#include "alya.h"
#include "Dafni.h"
#include "Reivan.h"
#include "yazid.h"
#include "Asidiq.h"

userLs* head = NULL;
int main() {
    int key = 1, status = 1;
    int selectedOption = 1;
    system("COLOR E0");
    system("type file.txt");
    gotoxy(55, 9);
    printf("CRYP2GRAPHY");
    //loadingMenu();
    system("cls");
    char cont;
    int choice;
    const char* dir = "test";
    LoginResult p;

    if (isFileExist((char*)"FriendshipGraph.txt")) {
        head = loadGraph();
        //printf("hey");
    }
    else {
        printf("File tidak ada\n");
        head = createGraph();
    }

    while (status == 1) {
        saveGraph(head);
        do {
            gotoxy(40, 2); printf("==========================================\n");
            gotoxy(40, 3); printf("||              CRYP2GRAPHY             ||\n");
            gotoxy(40, 4); printf("==========================================\n");
            gotoxy(40, 6); printf(GREEN"%c Login\n", (selectedOption == 1) ? '>' : ' ');
            gotoxy(40, 7); printf(BLUE"%c Registrasi\n", (selectedOption == 2) ? '>' : ' ');
            gotoxy(40, 8); printf(PURPLE"%c History\n", (selectedOption == 3) ? '>' : ' ');
            gotoxy(40, 9); printf(RED"%c Exit\n", (selectedOption == 4) ? '>' : ' ');
            printf(BLACK" ");

            key = getch();
            switch (key) {
            case 72:  // Up arrow key
                selectedOption = (selectedOption > 1) ? selectedOption - 1 : 4;
                system("cls");
                break;
            case 80:  // Down arrow key
                selectedOption = (selectedOption < 4) ? selectedOption + 1 : 1;
                system("cls");
                break;
            case 13:  // Enter key
                switch (selectedOption) {
                case 1:
                    p = login();
                    while (1) {
                        saveGraph(head);
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
                    break;
                case 2:
                    head = loadGraph();
                    printRegisteredUsersAndFollow(head);
                    printf("\nMasukan karakter apapun untuk melanjutkan ");
                    scanf(" %c", &cont);
                    break;
                case 3:
                {
                    int menu;
                    char* isifile;
                    while (1) {
                        system("cls");
                        printf("1. History Login\n2. History Register akun\n3. History Enkrip\n4. History Dekrip\n5. Kembali ke menu sebelumnya\n");
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
                            break;
                        }
                        if (menu == 5) {
                            break;
                        }
                    }
                }
                break;
                case 4:
                    status = 0;
                    break;
                }
                system("cls");
                break;
            default:
                // Abaikan tombol lainnya
                break;
            }
        } while (key != 13 && status == 1);
    }

    if (status == 0) {
        printf("Exiting...\n");
    }

    return 0;
}