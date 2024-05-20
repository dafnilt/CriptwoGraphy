#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include "header.h"
#include <windows.h>
#include <conio.h>
#include "Asidiq.h"
#include "yazid.h"

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
    puts("");
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void loadingMenu() {
    gotoxy(53, 1);
    printf("Loading "); Sleep(1000);
    printf(". "); Sleep(1000);
    printf(". "); Sleep(1000);
    //printf(". "); Sleep(1000);
}

void Backspace() {
    int key;
    do {
        key = getch();
    } while (key != 8); // 8 adalah kode ASCII untuk backspace
}

void displayHistoryMenu(int selectedOption) {
    system("cls");
    gotoxy(40, 2); printf("==========================================\n");
    gotoxy(40, 3); printf("||      CRYPTWOGRAPHY HISTORY MENU      ||\n");
    gotoxy(40, 4); printf("==========================================\n");
    gotoxy(40, 6); printf(GREEN"%c History Login\n", (selectedOption == 1) ? '>' : ' ');
    gotoxy(40, 7); printf(BLUE"%c History Register akun\n", (selectedOption == 2) ? '>' : ' ');
    gotoxy(40, 8); printf(RED"%c History Enkrip\n", (selectedOption == 3) ? '>' : ' ');
    gotoxy(40, 9); printf(CYAN"%c History Dekrip\n", (selectedOption == 4) ? '>' : ' ');
    gotoxy(40, 10); printf(WHITE"%c Kembali ke menu sebelumnya\n", (selectedOption == 5) ? '>' : ' ');
    printf(BLACK""); 
}

void historyMenu() {
    int key;
    int selectedOption = 1;
    char* isifile;

    while (1) {
        displayHistoryMenu(selectedOption);

        key = getch();
        switch (key) {
        case 72:  // Up arrow key
            selectedOption = (selectedOption > 1) ? selectedOption - 1 : 5;
            break;
        case 80:  // Down arrow key
            selectedOption = (selectedOption < 5) ? selectedOption + 1 : 1;
            break;
        case 13:  // Enter key
            switch (selectedOption) {
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
            case 5:
                return;
            }
            printf("\nTekan backspace untuk kembali ke menu history...");
            while (getch() != 8); // Wait for backspace key (ASCII 8)
            break;
        default:
            // Ignore other keys
            break;
        }
    }
}