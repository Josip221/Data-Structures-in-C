#include "Funkcije.h"
// jos ovo dovrsiti i gotov

int OslobodiKontakte(PozicijaKontakt headKontakt){
	PozicijaKontakt tmp = NULL;
	while(headKontakt->sljedeci != NULL){
		tmp = headKontakt->sljedeci;
		if(tmp->sljedeci){
			tmp->sljedeci->prethodni = headKontakt;
		}
		headKontakt->sljedeci = tmp->sljedeci;
		free(tmp);
	}
	return EXIT_SUCCESS;
}

int OslobodiPozivListu(PozicijaLista headLista){
	PozicijaLista tmp = NULL;
	while(headLista->sljedeci != NULL){
		tmp = headLista->sljedeci;
		headLista->sljedeci = tmp->sljedeci;
		free(tmp);
	}
	return EXIT_SUCCESS;
}

int OslobodiHashTablicu(HashTab hashTab){
	int i = 0;

	for(i = 0; i < MAX_HASH_TABLE_SIZE; i++){
		OslobodiStablo(hashTab->headPoziv[i]);
	}
	free(hashTab);
}

int OslobodiStablo(PozicijaStablo p){
	if(p != NULL){
		OslobodiStablo(p->lijevo);
		OslobodiStablo(p->desno);
		free(p);
	}
}