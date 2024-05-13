#pragma once

#ifndef alya_h
#define alya_h

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <direct.h>
	#include <ctype.h>
	#include <stdbool.h>

    // Struktur data untuk menyimpan informasi pengguna
    struct User {
        char username[100];
        char password[100];
        char encryptedPrivateKey[100];
        char encryptedPublicKey[100];
        char encryptedProduct[100];
        RSAkey key; // RSA keys added
        bool isValid; // Indicates whether the user is valid or not
    };

    //Untuk menyimpan kunci RSA dan username
    typedef struct {
        RSAkey key;
        char username[100];
    } LoginResult;

    typedef struct {
        char ussr[];
    } akun;


    // Definisi struktur untuk menyimpan kunci RSA yang telah dienkripsi
    struct EncryptedRSAKeys {
        char privateKey[20];
        char publicKey[20];
        char product[20];
    };

    // Fungsi untuk mengenkripsi string menggunakan Caesar cipher
    void caesarEncrypt(char* text, int shift);

    // Fungsi untuk melakukan dekripsi Caesar cipher
    void caesarDecrypt(char* text, int shift);

    // Modul untuk dekripsi kunci RSA
    RSAkey decryptRSAkeysFromFile(struct EncryptedRSAKeys encryptedKeys);

    // Fungsi untuk menghasilkan kunci RSA dan mengenkripsinya sebelum disimpan
    struct EncryptedRSAKeys genEncryptedRSAkeys();


    // Fungsi untuk membuat folder baru dengan nama username
    int createFolder(const char* username);

    // Fungsi untuk menyimpan data pengguna ke dalam file
    void simpanCredential(struct User user, struct EncryptedRSAKeys encryptedKeys);

    // Fungsi untuk mengecek apakah username telah terdaftar sebelumnya
    struct User cekUsername(char* username);

    // Fungsi untuk melakukan proses login dan mengembalikan kunci RSA dan username yang sesuai
    LoginResult login();

    // Prosedur untuk melakukan registrasi
    void registrasi();

    // Fungsi untuk memeriksa apakah string mengandung setidaknya satu huruf besar
    bool containsUppercase(char* str);

    // Fungsi untuk memeriksa apakah string mengandung setidaknya satu angka
    bool containsDigit(char* str);

    // Fungsi untuk memeriksa apakah string mengandung setidaknya satu simbol
    bool containsSymbol(char* str);


