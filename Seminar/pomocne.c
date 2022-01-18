#include "Funkcije.h"

int BrojIspravan(char* testString){
	int i = 1, status = 0;
	char tmp[MAX_STRING_SIZE] = {0};

	strcpy(tmp, testString);
	char* token = strtok(tmp, "-");

	// XXX-XXX-XXXX 3-3-4
	for(i = 1; i < 4; i++){
		if(!token){
			break;
		}
		if(strlen(token) == 3 && (i == 1 || i == 2)){
			token = strtok(NULL, "-");
			if(StringBezSlova(token) == EXIT_SUCCESS){
				status++;
			}
		}
		else if(strlen(token) == 4 && i == 3){
			if(StringBezSlova(token) == EXIT_SUCCESS){
				status++;
			}
		}
	}
	if(status == 3){
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int StringBezSlova(char* testString){
	int i = 0;
	if(!testString){
		return EXIT_FAILURE;
	}
	for(i = 0; i < strlen(testString); i++){
		if(testString[i] < 48 || testString[i] > 57){
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

int RandomBroj(int max, int min){
	int rez = (rand() % (max - min + 1)) + min;
	return rez;
}

int OdstraniS(char* testString){
	int rez = 0;
	char *token = NULL;
	char tmp[MAX_STRING_SIZE] = {0};

	strcpy(tmp, testString);
	token = strtok(testString, "s");
	rez = atoi(token);
	return rez;
}

int StvoriVrijemeTrajanjaPoziva(){
	int max = 1000, min = 10;
	int trajanje = RandomBroj(max, min);
	return trajanje;
}

int MenuStop(){
	printf("\nPritisnite enter za natrag na glavni menu: ");
	//fflush(stdin); bad
	fseek(stdin, 0, SEEK_END);
	getchar();
	system("cls");
	return EXIT_SUCCESS;
}

int PrintVrijeme(int vrijemeSekunde){
	printf(" %dm %ds", vrijemeSekunde / 60,  vrijemeSekunde % 60);
	return EXIT_SUCCESS;
}

int PrintImePrezimeBroj(PozicijaKontakt kontakt){
	printf(" %s %s %s\n", kontakt->ime, kontakt->prezime, kontakt->pozivni_broj);
	return EXIT_SUCCESS;
}

int PrintPhoneBookMenu(){
	PrintBorder();
	printf("\n\t\t\tPhonebook Menu\t\t\t\n\n");
	printf("\t\t1. Dodaj novi kontakt\n");
	printf("\t\t2. Napravi poziv\n");
	printf("\t\t3. Izmjeni postojeci kontakt\n");
	printf("\t\t4. Izbrisi kontakt\n");
	printf("\t\t5. Print svi kontakti\n");
	printf("\t\t6. Print svi pozivi\n");
	printf("\t\t7. Datoteka menu\n");
	printf("\t\t8. Pretrazivanja\n");
	printf("\t\t9. Izadi iz programa\n");
	PrintBorder();
	return EXIT_SUCCESS;
}

int PrintDatotekaMenu(){
	PrintBorder();
	printf("\tDatoteka menu: \n");
	printf("\t\t1. Ucitaj kontakte\n");
	printf("\t\t2. Spremi kontakte\n");
	printf("\t\t3. Ucitaj pozive\n");
	printf("\t\t4. Spremi pozive\n");
	printf("\t\t5. Natrag na glavni menu\n");
	PrintBorder();
	return EXIT_SUCCESS;
}

int PrintBorder(){
	printf("\n============================================================");
	printf("\n************************************************************\n");
	return EXIT_SUCCESS;
}