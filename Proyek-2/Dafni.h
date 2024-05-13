#pragma once
#pragma warning(disable : 4996)
#pragma once
#ifndef dafni_h
#define dafni_h
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include "dirent.h"
#include <string.h>
#include <time.h>
#include <random>
#include <stdint.h>
#include <direct.h>
#include <ctype.h>
#include <stdbool.h>
#include "header.h"

//Fungsi untuk menampilkan list files yang ada di direktori
void listFiles(const char* path, char filenames[][256], int* file_count);

//Fungsi untuk menampilkan isi file yang dipilih
void displayFileContent(const char* path, const char* filename);

//Fungsi untuk menampilan file yang dipilih
void show_files(const char* directory_path);

//Fungsi untuk memilih file yang ada di direktori
char* choose_file(const char* directory_path, int selected_file_index);

//Fungsi untuk menyatukan fungsi RSA milik Asidiq disatukan dengan fungsi buka file Dafni, menghasilkan file yang di dekripsi
void mainLogic();

void firstmodul(unsigned long long int e, unsigned long long int n, char q[]);

#endif