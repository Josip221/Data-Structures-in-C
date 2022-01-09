#include "Funkcije.h"

//todo napravi
int BrojIspravan(){
	return 1; //dovrsi stringove
}

int RandomBroj(int max, int min){
	int rez = (rand() % (max - min + 1)) + min;
	return rez;
}

int StvoriVrijemeTrajanjaPoziva(){
	int max = 1000, min = 10;
	int trajanje = RandomBroj(max, min);
	return trajanje;
}

int MenuStop(){
	printf("Odaberite bilo koju tipku za natrag na glavni menu: ");
	//fflush(stdin); bad
	fseek(stdin, 0, SEEK_END);
	getchar();
	system("cls");
	return EXIT_SUCCESS;
}

int PrintPhoneBookMenu(){
	printf("\n============================================================");
	printf("\n************************************************************\n");
	printf("\n\t\t\tPhonebook Menu\t\t\t\n\n");
	printf("\t\t1. Dodaj novi kontakt\n");
	printf("\t\t2. Napravi poziv\n");
	printf("\t\t3. Izmjeni postojeci kontakt\n");
	printf("\t\t4. Izbrisi kontakt\n");
	printf("\t\t5. Print svi kontakti\n");
	printf("\t\t6. Print svi pozivi\n");
	printf("\t\t7. Datoteka menu\n");
	printf("\t\t8. Statistika\n");
	printf("\t\t9. Izadi iz programa\n");
	printf("\n============================================================");
	printf("\n************************************************************\n");
	return EXIT_SUCCESS;
}