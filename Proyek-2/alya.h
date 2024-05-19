#pragma once

#ifndef alya_h
#define alya_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <ctype.h>
#include <stdbool.h>
#include "header.h"


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

char* printFollowersAndChooseUser(uAddress currentUser);

void makeFriendFolder(const char followingUsername[], const char loggedInUsername[]);

void kirimFile(uAddress head, LoginResult p);

#endif

