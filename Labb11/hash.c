#include "Funkcije.h"

int hashFunkcija(char* imeDrzave){
	int rez = 0;
	for(int i = 0; i < strlen(imeDrzave) || i < 5; i++){
		rez += imeDrzave[i];
	}
	return rez % MAX_HASH_TABLE_SIZE;
}

HashTab StvoriHashTab(){
	HashTab hash = NULL;
	int i = 0;

	hash = (HashTab) malloc(sizeof(HashT));
	if(hash == NULL){
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	hash->headLista = (PozicijaLista*) malloc(sizeof(PozicijaLista) * MAX_HASH_TABLE_SIZE);
	if(hash->headLista == NULL){
		printf("Greska pri alociranju memorije");
		return NULL;
	}

	for(i = 0; i < MAX_HASH_TABLE_SIZE; i++){
		hash->headLista[i] = StvoriClanListe();	
	}
	return hash;
}

int DodajDrzavaUHashTablicu(HashTab hashTab, char* imeDrzava, char* imeGradoviDat){
	int  index = 0;
	index = hashFunkcija(imeDrzava);

	DodajDrzavaUListu(hashTab->headLista[index], imeDrzava, imeGradoviDat);
}

