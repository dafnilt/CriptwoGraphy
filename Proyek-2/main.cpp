#include<stdio.h>
#include"header.h"


int main(){
	int menu;
	puts("\t\t\t\t\t\t Cryptwography ");
	puts("");
	puts("");
	puts("1.Login\n2.Register\n3.Exit");
	scanf("%d", &menu);
	while (menu != 3) {

		switch (menu) {
		case 1:
			login();
			break;
		}
	case 2:
		registrasi();
		break;
	case 3:
		

	}
}
