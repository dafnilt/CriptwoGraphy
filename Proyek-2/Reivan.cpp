#pragma warning(disable : 4996)
#include <stdlib.h>
#include <stdio.h>
#include <random>
#include <stdint.h>
#include "header.h"


//untuk RNG
std::random_device rd;

//Fungsi untuk menghitung modular exponentation
uint64_t modExpo(uint64_t base, uint64_t power, uint64_t divisor){
	uint64_t result = 1;
	//loop hingga power = 0
	while (power > 0){
		if (power & 1){//jika power ganjil(jika bit paling kanan power 1)
			result = (result * base) % divisor;
		}
		base = base * base % divisor;
		power>>=1;//bit shift left untuk melihat bit paling kanan power
	}
	return (result);
}
//menghitung fungsi phi euler
uint64_t phi(uint64_t prime1, uint64_t prime2){
	return ((prime1-1)*(prime2-1));
}

//1 iterasi miller rabin test
bool singleTest(uint64_t a,uint64_t n){
	uint64_t p,exp = n-1;
	int i=0,j=0;
	while (exp % 2 == 0){
		exp = exp / 2;
		j++;
	}
	p = modExpo(a,exp,n);
	if ((p==n-1)){//jika hasil modulus exponentation a^exp %n = n-1 (-1)
		return true;
	}
	while (i<j-1){//loop hingga j
		p = modExpo(p,2,n);
		if ((p==n-1)){//jika hasil modulus exponentation p^2 %n = n-1 (-1)
			return true;
		}
		i++;
	}
	return false;
}

//miller rabin primality test dengan i kali iterasi
bool millerRabinTest(uint64_t n, uint64_t i){
	int k = 0;
	uint64_t max = n - 1;
	if (max <= 2) {
		return false;
	}
	std::uniform_int_distribution<unsigned long long int> range(2,max); //membuat range RNG baru
	while (k < i){// loop hingga i kali
		uint64_t a = range(rd); //randomize a baru
		if (!singleTest(a,n)){//lakukan 1 iterasi miller rabin test
			return false;//bukan bil prima
		}
		k++;
	}
	return true;//kemungkinan besar bilangan prima
}

//cek bil prima atau bukan
bool isPrime(uint64_t number){
	//dibagi dengan 100 bil prima pertama
	int i=0,firstFewPrime[]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541};
	while (i<100){
		if (number % firstFewPrime[i] == 0){
			return false;
		}
		else{
			i++;
		}
	}
	//printf("%I64u\n", number);
	
	//test dengan miller rabin primality test
	return (millerRabinTest(number,40));
}

//generate bil prima
uint64_t genPrime(uint64_t lowerBound, uint64_t upperBound){
	std::uniform_int_distribution<unsigned long long int> range(lowerBound, upperBound);
	uint64_t n;
	for (;;){//loop hingga menemukan bil prima
		n = range(rd);//randomize n
		if (isPrime(n)){//cek bil prima atau bukan
			return n;
		}
	}
}

//function untuk mengenerate private key
uint64_t genPrivateKey(uint64_t totient) {
	//deklarasi var
	uint64_t keyCandidate = genPrime(1, totient - 1);

	while (keyCandidate % totient == 0) {//loop hingga memenuhi syarat
		keyCandidate = genPrime(1, totient - 1);//generate bil prima yang lebih kecil dari totient
	}

	return keyCandidate;
}

//function untuk mencari modular multiplicative inverse menggunakan extended euclidian alg
//dan menghitung GCD(greatest common divisor)(FPB) menggunakan euclidian alg
uint64_t euclidianAlg(uint64_t s, uint64_t l, int64_t prevRemainder, int64_t* t1, int64_t* t2) {
	uint64_t remainder = 1; //deklarasi var
	int64_t prevT2;

	//cek akhir program
	if (s == 0) {
		return prevRemainder;//return remainder sebelum 0
	}

	//perhitungan extended euclidian alg
	prevT2 = *t2;
	*t2 = *t1 - ((l / s) * *t2);
	*t1 = prevT2;

	//perhitungan euclidian alg
	prevRemainder = s;
	remainder = l % s;

	return (euclidianAlg(remainder, s, prevRemainder, *&t1, *&t2));//lakukan kembali perhitungan dengan s menjadi l dan remainder menjadi hingga s==0
}

//function euclidianAlg dengan validator dan tambahan program jika hasil t1 negatif 
uint64_t modInverse(uint64_t s, uint64_t l) {
	//deklarasi var
	uint64_t res;
	int64_t t1 = 0, t2 = 1;

	//validator
	if (s > l) {//cek jiika s lebih besar daripada l
		printf("Parameter pertama harus lebih kecil daripada parameter kedua!\n");
		return 1;
	}

	//memanggil euclidianAlg
	res = (euclidianAlg(s, l, -1, &t1, &t2));

	//jika t1 negatif
	if (t1 < 0) {
		t1 += l;
	}

	//return t1
	return t1;
}

//function yang mengenerate private key, public key, dan product (perkalian 2 bil prima)
RSAkey genRSAkeys() {
	//deklarasi var
	uint64_t p, q, totient;
	RSAkey keys;

	//generate 2 bil prima random
	p = genPrime(1, MAXrng);
	q = genPrime(1, MAXrng);

	//menghitung totient
	totient = phi(p, q);

	//menghitung perkalian p dan q
	keys.product = p * q;

	//generate private key
	keys.privateKey = genPrivateKey(totient);

	//menghitung public key
	keys.publicKey = modInverse(keys.privateKey, totient);

	//retutn struct
	return keys;
}

//Procedure untuk membaca file yang terenkripsi dan menampilkan hasil dekripsi ke layar
void fileDecrypt(LoginResult info) {
	char path[256];
	sprintf(path, "user/%s", info.username);
	char filenames[100][256];
	int file_count;

	//list file di direktori user/[username]
	printf("Daftar file dalam direktori user/%s:\n", info.username);
	listFiles(path, filenames, &file_count);

	//cek jika tidak ada file di dalam direktori
	if (file_count == 0) {
		printf("Tidak ada file dalam direktori.\n");
		return;
	}

	for (int i = 0; i < file_count; i++) {
		printf("%d. %s\n", i + 1, filenames[i]);
	}

	//Input file yang ingin di tampilkan
	printf("\nMasukkan indeks file yang ingin Anda tampilkan: ");
	int index;
	scanf("%d", &index);
	getchar();

	if (index >= 1 && index <= file_count) {//jika indeks valid
		char selectedFilename[256];
		strcpy(selectedFilename, filenames[index - 1]);
		printf("Anda memilih file: %s\n", selectedFilename);
		recordHistorydekrip(info.username, selectedFilename);
		char filepath[256];
		snprintf(filepath, sizeof(filepath), "%s/%s", path, selectedFilename);

		FILE* file = fopen(filepath, "r");
		if (file == NULL) {
			printf("Gagal membuka file.");
			return;
		}

		//mencari tahu panjang file
		int i = 0;
		uint64_t chiper[256];
		while (!feof(file)) {
			fscanf(file, "%I64u", &chiper[i]);
			i++;
		}

		printf("\nIsi dari file yang anda pilih adalah:\n");
		decryptToString(chiper, i-1, info.key.publicKey, info.key.product);//dekripsi isi file
		printf("\n");
	}
}
