#include "Funkcije.h"

Datum StvoriRandomDatum(){
	Datum dm = {.godina = 0, .mjesec = 0, .dan = 0};
	dm.godina = RandomBroj(2022, 2010);
	dm.mjesec = RandomBroj(12, 1);
	dm.dan = RandomBroj(30, 1);
	return dm;
}

int UsporediDatume(Datum dm1, Datum dm2){
	int rezultat = dm1.godina - dm2.godina;

	if(rezultat == 0){
		rezultat = dm1.mjesec - dm2.mjesec;
		if(rezultat == 0){
			rezultat = dm1.dan - dm2.dan;
		}
	}
	return rezultat;
}

int PrintDatum(Datum dm){
	printf(" %d-%d-%d", dm.dan, dm.mjesec, dm.godina);
	return EXIT_SUCCESS;
}

int ProvjeriDatum(char* tmpDatum){
	Datum dm = {.dan = 0, .godina = 0, .mjesec = 0};
	char tmpString[MAX_STRING_SIZE] = {0};
	char* token = NULL;
	int i = 1;
	strcpy(tmpString, tmpDatum);

	token = strtok(tmpString, "-");

	for(i = 1; i < 4; i++){
		if(i == 1){
			dm.dan = atoi(token);
			token = strtok(NULL, "-");
		}
		else if(i == 2){
			dm.mjesec = atoi(token);
			token = strtok(NULL, "-");
		}
		else if(i == 3){
			dm.godina = atoi(token);
		}
	}

	if(dm.godina >= 2000 && dm.godina <= 2022){
		if(dm.mjesec <= 12 && dm.mjesec >= 1){
			if(dm.dan >= 1 && dm.dan <= 30){
				return EXIT_SUCCESS;
			}
		}
	}
	return EXIT_FAILURE;
}

Datum PretvoriStringUDatum(char* string){
	Datum dm = {.dan = 0, .godina = 0, .mjesec = 0};
	char tmpString[MAX_STRING_SIZE] = {0};
	char* token = NULL;
	int i = 1;
	strcpy(tmpString, string);

	token = strtok(tmpString, "-");

	for(i = 1; i < 4; i++){
		if(i == 1){
			dm.dan = atoi(token);
			token = strtok(NULL, "-");
		}
		else if(i == 2){
			dm.mjesec = atoi(token);
			token = strtok(NULL, "-");
		}
		else if(i == 3){
			dm.godina = atoi(token);
		}
	}
	return dm;
}