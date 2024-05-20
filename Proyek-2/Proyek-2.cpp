
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



userLs* headPtr = NULL;
extern LoginResult currentUser;

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
    char teman[100];

    if (isFileExist((char*)"FriendshipGraph.txt")) {
        headPtr = loadGraph();
    }
    else {
        headPtr = createGraph();
    }

labelMainMenu:
    system("cls");

    while (status == 1) {
        saveGraph(headPtr);
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
            case 72: {// Up arrow key
                selectedOption = (selectedOption > 1) ? selectedOption - 1 : 4;
                system("cls");
            }
                   break;
            case 80:{  // Down arrow key
                selectedOption = (selectedOption < 4) ? selectedOption + 1 : 1;
                system("cls");
            }
                break;
            case 13: {  // Enter key
                switch (selectedOption) {
                case 1:
                {
                    system("cls");
                    p = login();
                    int subMenu = 1;
                    loadingMenu();

                    while (1) {
                        saveGraph(headPtr);
                        system("cls");
                        gotoxy(40, 2); printf("==========================================\n");
                        gotoxy(40, 3); printf("||        Enkripsi & Dekripsi Menu      ||\n");
                        gotoxy(40, 4); printf("==========================================\n");
                        gotoxy(40, 5); printf(GREEN"%c Enkrip File dari folder directory\n", (subMenu == 1) ? '>' : ' ');
                        gotoxy(40, 6); printf(BLUE"%c Dekrip File dari Folder User\n", (subMenu == 2) ? '>' : ' ');
                        gotoxy(40, 7); printf(RED"%c Follow User\n", (subMenu == 3) ? '>' : ' ');
                        gotoxy(40, 8); printf(PURPLE"%c Kirim File\n", (subMenu == 4) ? '>' : ' ');
                        gotoxy(40, 9); printf(CYAN"%c Dekrip File Dari Inbox\n", (subMenu == 5) ? '>' : ' ');
                        gotoxy(40, 10); printf(WHITE"%c Keluar\n", (subMenu == 6) ? '>' : ' ');
                        printf(BLACK"");

                        int key = getch();
                        switch (key) {
                        case 72: {  // Up arrow key
                            subMenu = (subMenu > 1) ? subMenu - 1 : 6;
                        }
                            break;
                        case 80: {  // Down arrow key
                            subMenu = (subMenu < 6) ? subMenu + 1 : 1;
                        }
                            break;
                        case 13: {  // Enter key
                            switch (subMenu) {
                            case 1:{
                                system("cls");
                                firstmodul(p.key.privateKey, p.key.product, p.username);
                                printf("\nTekan tombol apapun untuk melanjutkan");
                                getch();
                            }
                                break;
                            case 2: {
                                system("cls");
                                fileDecrypt(p);
                                printf("\nTekan tombol apapun untuk melanjutkan");
                                getch();
                            }
                                break;
                            case 3: {
                                system("cls");
                                printRegisteredUsersAndFollow();
                                printf("\nTekan tombol apapun untuk melanjutkan");
                                getch();
                            }
                                break;
                            case 4: {
                                system("cls");
                                printf("Masukan nama Teman : ");
                                scanf("%s", teman);
                                encrypt_friend(p.username, teman);
                                printf("\nTekan tombol apapun untuk melanjutkan");
                                getch();
                            }
                                break;
                            case 5: {
                                system("cls");
                                decryptShare();
                                printf("\nTekan tombol apapun untuk melanjutkan");
                                getch();
                            }
                                  break;
                            case 6: {
                                system("cls");
                                gotoxy(50, 3); printf(RED"Keluar dari menu.\n");
                                printf(BLACK"");
                                loadingMenu();
                                goto labelMainMenu;
                            }
                                break;
                            default: {
                                system("cls");
                                puts("");
                                printf("Pilihan tidak valid.\n");
                            }
                            }
                            if (selectedOption == 6)
                                break;
                        }
                            break;
                        default:
                            // Ignore other keys
                            break;
                        }
                    }
                }
                break;
                case 2: {
                    system("cls");
                    registrasi();
                    gotoxy(40,16); printf("Masukan karakter apapun untuk melanjutkan ");
                    scanf(" %c", &cont);
                }
                    break;
                case 3: {
                    system("cls");
                    historyMenu();
                }
                    break;
                case 4: {
                    status = 0;
                }
                    break;
                }
                system("cls");
            }
                break;
            default:
                // Abaikan tombol lainnya
                break;
            }
        } while (key != 13 && status == 1);
    }

    if (status == 0) {
        printf(RED"Exiting...\n");
        printf(BLACK"");
    }

    return 0;
}
