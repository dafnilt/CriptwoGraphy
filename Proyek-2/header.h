// header.h
#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include "dirent.h"
#include <string.h>

void show_files(const char* directory_path);
char* choose_file(const char* directory_path, int selected_file_index);
void example_usage();

#endif // HEADER_H
