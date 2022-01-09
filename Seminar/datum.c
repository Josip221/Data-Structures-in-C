#include "Funkcije.h"

Datum StvoriRandomDatum(){
	Datum dm = {.godina = 0, .mjesec = 0, .dan = 0};
	dm.godina = RandomBroj(2022, 2000);
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
	printf(" %d-%d-%d", dm.godina, dm.mjesec, dm.dan);
	return EXIT_SUCCESS;
}