#include "Funkcije.h"
// jos ovo dovrsiti i gotov

int OslobodiKontakte(PozicijaKontakt headKontakt){
	PozicijaKontakt tmp = NULL;
	while(headKontakt != NULL){
		tmp = headKontakt;
		tmp->sljedeci->prethodni = tmp->prethodni;
		tmp->prethodni->sljedeci = tmp->sljedeci;
		free(tmp);
		headKontakt = headKontakt->sljedeci;
	}
	return EXIT_SUCCESS;
}

//int OslobodiPozivList(PozicijaKontakt);