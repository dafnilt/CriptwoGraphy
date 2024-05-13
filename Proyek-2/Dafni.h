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

void listFiles(const char* path, char filenames[][256], int* file_count);
void displayFileContent(const char* path, const char* filename);

void show_files(const char* directory_path);
char* choose_file(const char* directory_path, int selected_file_index);

void mainLogic();

#endif