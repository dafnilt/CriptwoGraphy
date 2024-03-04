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
	std::uniform_int_distribution<unsigned int> range(2,n-1); //membuat range RNG baru
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
	//test dengan miller rabin primality test
	return (millerRabinTest(number,40));
}

//generate bil prima
uint64_t genPrime(uint64_t lowerBound, uint64_t upperBound){
	std::uniform_int_distribution<unsigned int> range(lowerBound, upperBound);
	uint64_t n;
	for (;;){//loop hingga menemukan bil prima
		n = range(rd);//randomize n
		if (isPrime(n)){//cek bil prima atau bukan
			return n;
		}
	}
}

uint64_t genPrivateKey(uint64_t prod, uint64_t totient){
	//deklarasi var
	uint64_t keyCandidate = 0;
	
	for (;;) {//loop hingga memenuhi syarat
		keyCandidate = genPrime(1, totient);//generate bil prima
		if (keyCandidate % prod != 0) {
			return keyCandidate;
		}
		printf("Hello\n");
	}
	
	return keyCandidate;
}

//euclidian algorithm untuk menghitung GCD(greatest common divisor)(FPB)
uint64_t euclidianAlg(uint64_t s, uint64_t l, uint64_t prevRemainder){
	uint64_t remainder=1; //deklarasi var
	
	//cek akhir program
	if (s == 0){
		return prevRemainder;//return remainder sebelum 0
	}
	
	//perhitungan
	prevRemainder = s;
	remainder = l % s;
	
	return (euclidianAlg(remainder, s, prevRemainder));//lakukan kembali perhitungan dengan s menjadi l dan remainder menjadi hingga s==0
}

//euclidian algorithm dengan validator, function ini yang dipanggil
uint64_t gcd(uint64_t s, uint64_t l){
	//validator
	if (s > l){//cek jiika s lebih besar daripada l
		printf("Parameter pertama harus lebih kecil daripada parameter kedua!\n");
		return 1;
	}
	if (s == 0){
		return l;
	}
	
	if ((isPrime(s)) || (isPrime(l))){// jika salah satu bil prima
		if (s != l){//jika s dan l beda
			return 1;
		}
		else{//jika s dan l sama
			return l;
		}
	}
	
	//return hasil euclidianAlg
	return (euclidianAlg(s, l, 1));

}

//uint64_t genPublicKey(uint64_t privateKey, uint64_t totient){//wip
//	uint64_t publicKey;
//	
//	return publicKey;
//}