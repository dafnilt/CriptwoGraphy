
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

    if (isFileExist((char*)"FriendshipGraph.txt")) {
        headPtr = loadGraph();
        //printf("hey");
    }
    else {
        printf("File tidak ada\n");
        headPtr = createGraph();
    }

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
            case 72: { // Up arrow key

                selectedOption = (selectedOption > 1) ? selectedOption - 1 : 4;
                system("cls");}
                break;
            case 80: { // Down arrow key
                selectedOption = (selectedOption < 4) ? selectedOption + 1 : 1;
                system("cls");}
                break;
            case 13: { // Enter key
                switch (selectedOption) {
                case 1:
                {
                    system("cls");
                    p = login();
                    int selectedOption = 1;

                    while (1) {
                        saveGraph(headPtr);
                        system("cls");
                        printf("==========================================\n");
                        printf("||        Enkripsi & Dekripsi Menu        ||\n");
                        printf("==========================================\n");
                        printf(GREEN"%c Enkrip File dari folder directory\n", (selectedOption == 1) ? '>' : ' ');
                        printf(BLUE"%c Dekrip File dari Folder User\n", (selectedOption == 2) ? '>' : ' ');
                        printf(RED"%c Follow User\n", (selectedOption == 3) ? '>' : ' ');
                        printf(PURPLE"%c Kirim File\n", (selectedOption == 4) ? '>' : ' ');
                        printf(WHITE"%c Keluar\n", (selectedOption == 5) ? '>' : ' ');
                        printf(BLACK"");

                        int key = getch();
                        switch (key) {
                        case 72: {  // Up arrow key
                            selectedOption = (selectedOption > 1) ? selectedOption - 1 : 4;
                        }
                               break;
                        case 80: { // Down arrow key
                            selectedOption = (selectedOption < 4) ? selectedOption + 1 : 1;
                        }
                               break;
                        case 13: {  // Enter key
                            switch (selectedOption) {
                            case 1: {
                                system("cls");
                                firstmodul(p.key.privateKey, p.key.product, p.username);
                            }
                                  break;
                            case 2: {
                                system("cls");
                                fileDecrypt(p);
                            }
                                  break;
                            case 3: {
                                system("cls");
                                headPtr = loadGraph();
                                printRegisteredUsersAndFollow(headPtr);
                                printf("\nMasukan karakter apapun untuk melanjutkan ");
                                scanf(" %c", &cont);
                            }
                                  break;
                            case 4: {
                                system("cls");
                                uAddress headPtr = loadGraph();
                                LoginResult currentUser;
                                kirimFile(headPtr, currentUser);
                                return 0;
                            }
                                  break;
                            case 5: {
                                printf("Keluar dari menu.\n");
                            }
                                  break;
                            default: {
                                system("cls");
                                puts("");
                                printf("Pilihan tidak valid.\n");
                            }
                            }
                            if {(selectedOption == 4)}
                            break;
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
                    printf("\nMasukan karakter apapun untuk melanjutkan ");
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
        printf("Exiting...\n");
    }

    return 0;
}