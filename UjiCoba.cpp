#include <stdio.h>
#include <unistd.h>

// Fungsi untuk menampilkan menu dengan warna
void tampilkanMenu() {
    printf("\033[1;32m========== Program Saya ==========\n"); // Warna hijau terang
    printf("\033[1;33m1. Pilihan Pertama\n"); // Warna kuning terang
    printf("\033[1;34m2. Pilihan Kedua\n"); // Warna default
    printf("\033[1;31m3. Keluar\n"); // Warna merah terang
    printf("\033[0m==================================\n"); // Kembali ke warna default
    printf("Masukkan pilihan Anda: ");
}

int main() {
//    system("COLOR 40");
    int pilihan;

    do {
        // Menampilkan menu
        tampilkanMenu();
        // Membaca pilihan pengguna
        scanf("%d", &pilihan);

        // Memproses pilihan pengguna
        switch (pilihan) {
            case 1:
                printf("Anda memilih Pilihan Pertama.\n");
                // Tambahkan kode untuk pilihan pertama di sini
                break;
            case 2:
                printf("Anda memilih Pilihan Kedua.\n");
                // Tambahkan kode untuk pilihan kedua di sini
                break;
            case 3:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan pilih lagi.\n");
                break;
        }
    } while (pilihan != 3);

    return 0;
}

