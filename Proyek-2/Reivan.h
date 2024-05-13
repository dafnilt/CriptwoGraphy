#pragma once
#ifndef reivan_h
#define reivan_h

#include <stdlib.h>
#include <stdio.h>
#include <random>
#include <stdint.h>
#include "header.h"


#define MAXrng 50000
#define username(X) (X)->username
#define nextUser(X) (X)->nextUser
#define follow(X) (X)->follow
#define nextFollow(X) (X)->nextFollow



// Fungsi untuk melakukan pemangkatan dengan eksponensiasi cepat
uint64_t modExpo(uint64_t base, uint64_t power, uint64_t divisor);

// Fungsi untuk menghitung fungsi phi Euler
uint64_t phi(uint64_t prime1, uint64_t prime2);

// Fungsi untuk melakukan uji keprimaan Miller-Rabin
bool millerRabinTest(uint64_t n, uint64_t i);

// Fungsi untuk menguji apakah suatu bilangan prima
bool isPrime(uint64_t number);

// Fungsi untuk menghasilkan bilangan prima dalam rentang tertentu
uint64_t genPrime(uint64_t lowerBound, uint64_t upperBound);

// Fungsi untuk menghasilkan kunci privat
uint64_t genPrivateKey(uint64_t totient);

//function untuk mencari modular multiplicative inverse menggunakan extended euclidian alg
//dan menghitung GCD(greatest common divisor)(FPB) menggunakan euclidian alg
uint64_t euclidianAlg(uint64_t s, uint64_t l, int64_t prevRemainder, int64_t* t1, int64_t* t2);

//function euclidianAlg dengan validator dan tambahan program jika hasil t1 negatif 
uint64_t modInverse(uint64_t s, uint64_t l);

//function yang mengenerate private key, public key, dan product (perkalian 2 bil prima)
RSAkey genRSAkeys();

//procedure dekripsi file yang terenkripsi dan print isinya ke layar
void fileDecrypt(LoginResult info);

//procedure untuk membuat graph jika graph belum pernah dibuat
void createGraph();

//function yang mereturn address bertipe followLs dengan username yang ditentukan
fAddress createNodeFollow(char info[100]);

//function yang mereturn address bertipe userLs dengan username yang ditentukan
uAddress createNodeUser(char info[100]);

//procedure yang akan menginsert user yang difollow ke list follow user yang ditentukan
void insertFollow(char fUsername[100], char uUsername[100], uAddress head);

//procedure yang akan menginsert user ke list user
void insertUser(char username[100], uAddress head);

//procedure untuk membuat graph dari file sata graph yang sudah tersimpan
void loadGraph(uAddress head);

//procedure yang menyimpan isi graph ke file .txt
void saveGraph(uAddress head);







#endif