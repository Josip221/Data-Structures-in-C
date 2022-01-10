#include "Funkcije.h"

PozicijaPoziv StvoriPoziv(){
	PozicijaPoziv tmp = malloc(sizeof(Poziv));
	if(tmp == NULL){
		printf("\nGreska pri alociranju memorije poziva!\n");
		return NULL;
	}
	tmp->id_poziv = 0;
	tmp->datum.godina = 0;
	tmp->datum.mjesec = 0;
	tmp->datum.dan = 0;
	tmp->trajanje_poziva = 0;
	tmp->kontakt = NULL;
	tmp->sljedeci = NULL;
	return tmp;
}

int ProcitajPozivDatoteku(PozicijaPoziv headPoziv, PozicijaKontakt headKontakt, char* imeDat){
	// FILE* dat = NULL;
	// PozicijaKontakt tmpKontakt = NULL;
	// char tmp1[MAX] = {0}, tmp2[MAX] = {0};
	// dat = fopen(imeDat, "w");
	// if(!dat){
	// 	printf("Greska pri otvaranju poziv datoteke");
	// 	return EXIT_FAILURE;
	// }
	// while(!feof(dat)){
	// 	fscanf("%s %s", tmp1, tmp2);
	// 	tmpKontakt = NadiKontaktPoBroju(headKontakt, tmp2);
	// 	DodajPozivUListu(headPoziv, headKontakt, tmpKontakt->pozivni_broj);
	// }
	// fclose(dat);
	// return EXIT_SUCCESS;
}

int DodajPozivUListu(PozicijaPoziv headPoziv, PozicijaKontakt headKontakt, char* pozivni_broj){
	int base_id = 1;
	PozicijaPoziv tmp = StvoriPoziv();
	PozicijaKontakt pozivniKontakt = NadiKontaktPoBroju(headKontakt, pozivni_broj);
	if(!pozivniKontakt){
		printf(" Nije moguce napraviti poziv probajte ponovno.\n");
		return EXIT_FAILURE;
	}

	tmp->datum = StvoriRandomDatum();
	tmp->id_poziv = base_id;
	tmp->trajanje_poziva = StvoriVrijemeTrajanjaPoziva();
	tmp->kontakt = pozivniKontakt;
	//sortiraj po datumu
	while(headPoziv->sljedeci != NULL){
		if(UsporediDatume(tmp->datum, headPoziv->sljedeci->datum)){
			break;
		}
		else{
			headPoziv = headPoziv->sljedeci;
		}
	}

	tmp->sljedeci = headPoziv->sljedeci;
	headPoziv->sljedeci = tmp;
	return EXIT_SUCCESS;
}

int PrintPozivLista(PozicijaPoziv headPoziv){
	printf("\nPovijest poziva: \n");
	if(headPoziv == NULL){
		printf("Lista poziva je treutno prazna!\n");
		return EXIT_SUCCESS;
	}
	while(headPoziv != NULL){
		printf("\t%s %s %s", headPoziv->kontakt->pozivni_broj, headPoziv->kontakt->ime, headPoziv->kontakt->prezime);
		PrintDatum(headPoziv->datum);
		if(headPoziv->trajanje_poziva < 60){
			printf(" %ds", headPoziv->trajanje_poziva);
		}
		else{
			printf(" %dmin %ds", headPoziv->trajanje_poziva / 60, headPoziv->trajanje_poziva % 60);
		}
		printf("\n");
		headPoziv = headPoziv->sljedeci;
	}
	MenuStop();
	return EXIT_SUCCESS;
}

int NajduljiPoziv();

int UkupnoVrijemePoziva();

int NadiPoziveUVremenskomRazdoblju();

int NadiPoziveOvisnoVremenuTrajanjaPoziva();

int KolikoPutaJeKontaktNazvan(PozicijaPoziv headPoziv, PozicijaKontakt kontakt){

}

PozicijaKontakt NajcesceKontaktirani(PozicijaPoziv headPoziv, char* pozivni_broj){

};