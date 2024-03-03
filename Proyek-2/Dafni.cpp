#include <stdio.h>
#include <stdlib.h>
#include "dirent.h"
#include <string.h>
#include "header.h"
#pragma warning(disable : 4996)

#define MAX_FILE_SIZE 1024

// Fungsi untuk menampilkan daftar file dalam suatu direktori
void show_files(const char* directory_path) {
    DIR* dir = opendir(directory_path);
    if (dir != NULL) {
        struct dirent* ent;
        int count = 0;

        // Loop through all the files in the directory
        while ((ent = readdir(dir)) != NULL) {
            // Skip "." and ".." entries
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
                continue;
            }

            // Print the index and name of each file
            printf("%d. %s\n", ++count, ent->d_name);
        }

        closedir(dir);
    }
    else {
        // Unable to open directory
        perror("Unable to open directory");
    }
}

// Fungsi untuk memilih file dari daftar yang ditampilkan
char* choose_file(const char* directory_path, int selected_file_index) {
    DIR* dir = opendir(directory_path);
    if (dir != NULL) {
        struct dirent* ent;
        int count = 0;

        // Reopen the directory to find the selected file
        while ((ent = readdir(dir)) != NULL) {
            // Skip "." and ".." entries
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
                continue;
            }

            if (++count == selected_file_index) {
                closedir(dir);
                return ent->d_name;
            }
        }

        closedir(dir);
    }
    else {
        // Unable to open directory
        perror("");
    }

    return NULL;
}

// Contoh penggunaan fungsi-fungsi di atas
void example_usage() {
    const char* directory_path = "D:/DAFNI/SEMESTER 2/PROYEK 2/PROYEK 2/SaveFile/SaveFile/Direktori";

    // Menampilkan daftar file dalam suatu direktori
    show_files(directory_path);

    // Memilih file dari daftar yang ditampilkan
    int selected_file_index;
    printf("Choose a file by entering its index: ");
    scanf("%d", &selected_file_index);

    // Mendapatkan nama file yang dipilih
    char* selected_file_name = choose_file(directory_path, selected_file_index);
    if (selected_file_name != NULL) {
        printf("You selected: %s\n", selected_file_name);
        // Do something with the selected file here
    }
}

// Fungsi utama (jika dibutuhkan, atau gunakan example_usage() untuk contoh penggunaan)
//int main() {
//    example_usage();
//     return 0;
//}
