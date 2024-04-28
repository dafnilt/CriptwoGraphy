#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definisi struktur data untuk simpul pohon biner
struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Fungsi untuk membuat simpul baru dalam pohon biner
struct TreeNode* createNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Fungsi untuk membebaskan memori yang dialokasikan untuk pohon biner
void freeTree(struct TreeNode *node) {
    if (node != NULL) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

// Fungsi untuk membangun pohon biner dari pesan
struct TreeNode* buildTreeFromMessage(const char *pesan) {
    struct TreeNode* root = createNode((int)pesan[0]);
    struct TreeNode* current = root;
    
    for (int i = 1; i < strlen(pesan); i++) {
        if (pesan[i] < current->value) {
            if (current->left == NULL)
                current->left = createNode((int)pesan[i]);
            current = current->left;
        } else {
            if (current->right == NULL)
                current->right = createNode((int)pesan[i]);
            current = current->right;
        }
    }
    return root;
}

// Fungsi rekursif untuk enkripsi pesan dengan pohon biner
void encryptMessageRecursively(const char *pesan, struct TreeNode *node, unsigned long long int cipher[], int *index) {
    if (node != NULL) {
        for (int i = 0; i < strlen(pesan); i++) {
            if ((int)pesan[i] == node->value) {
                cipher[(*index)++] = (unsigned long long int)node->value;
                break;
            }
        }
        encryptMessageRecursively(pesan, node->left, cipher, index);
        encryptMessageRecursively(pesan, node->right, cipher, index);
    }
}

// Fungsi untuk enkripsi pesan dengan pohon biner
void encryptMessage(const char *pesan, struct TreeNode *root, unsigned long long int cipher[], int *length) {
    *length = 0;
    encryptMessageRecursively(pesan, root, cipher, length);
}

// Fungsi rekursif untuk mendekripsi pesan dengan pohon biner
void decryptToStringRecursively(unsigned long long int cipher[], int length, struct TreeNode *node) {
    if (node != NULL) {
        for (int i = 0; i < length; i++) {
            if (cipher[i] == (unsigned long long int)node->value) {
                printf("%c", node->value);
                break;
            }
        }
        decryptToStringRecursively(cipher, length, node->left);
        decryptToStringRecursively(cipher, length, node->right);
    }
}

// Fungsi untuk mendekripsi pesan dengan pohon biner
void decryptToString(unsigned long long int cipher[], int length, struct TreeNode *root) {
    decryptToStringRecursively(cipher, length, root);
    printf("\n");

    // Membebaskan memori yang dialokasikan untuk pohon biner setelah dekripsi selesai
    freeTree(root);
}

int main() {
    // Pesan yang akan dienkripsi
    char pesan[100];
    printf("Masukkan pesan: ");
    fgets(pesan, sizeof(pesan), stdin);
    pesan[strcspn(pesan, "\n")] = 0; // Menghapus karakter newline dari pesan

    // Membangun pohon biner dari pesan
    struct TreeNode* root = buildTreeFromMessage(pesan);

    // Enkripsi pesan menggunakan pohon biner
    unsigned long long int cipher[100]; // Maksimal 100 karakter
    int length;
    encryptMessage(pesan, root, cipher, &length);

    // Menampilkan hasil enkripsi
    printf("Maka, ciphernya adalah ");
    for (int i = 0; i < length; i++) {
        printf("%llu", cipher[i]);
    }
    printf("\n");

    // Mendekripsi pesan menggunakan pohon biner
    printf("Hasil dekripsi: ");
    decryptToString(cipher, length, root);

    return 0;
}

