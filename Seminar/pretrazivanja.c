#include "Funkcije.h"

int NajduljiPoziv(PozicijaLista headLista){
	PozicijaLista najduljiPoziv = NULL;
	najduljiPoziv = StvoriClanListe();
	int najdulji = 0;
	while(headLista->sljedeci != NULL){
		if(najdulji < headLista->sljedeci->poziv->trajanje_poziva){
			najdulji = headLista->sljedeci->poziv->trajanje_poziva;
			najduljiPoziv = headLista->sljedeci;
		}
		headLista = headLista->sljedeci;
	}
	printf("Najdulji poziv: ");
	PrintDatum(najduljiPoziv->poziv->datum);
	printf(" %dm %ds ", najduljiPoziv->poziv->trajanje_poziva / 60, najduljiPoziv->poziv->trajanje_poziva % 60);
	printf("%s %s %s", najduljiPoziv->poziv->kontakt->ime, najduljiPoziv->poziv->kontakt->prezime, najduljiPoziv->poziv->kontakt->pozivni_broj);
	return EXIT_SUCCESS;
}

int UkupnoVrijemePoziva(PozicijaLista headLista){
	int ukupnoVrijeme = 0;
	while(headLista->sljedeci != NULL){
		ukupnoVrijeme += headLista->sljedeci->poziv->trajanje_poziva;
		headLista = headLista->sljedeci;
	}
	printf("Ukupno vrijeme svih poziva: %dm %ds", ukupnoVrijeme / 60, ukupnoVrijeme % 60);
	return EXIT_SUCCESS;;
}

int NadiPoziveUVremenskomRazdoblju(PozicijaLista headLista, Datum dm1, Datum dm2){
	Datum dmTmp = {.dan = 0, .godina = 0, .mjesec = 0};
	PozicijaStablo pozivTmp = NULL;

	printf("Pozivi u razdoblju od ");
	PrintDatum(dm1);
	printf(" do ");
	PrintDatum(dm2);
	printf(": \n");
	while(headLista->sljedeci != NULL){
		dmTmp = headLista->sljedeci->poziv->datum;
		pozivTmp = headLista->sljedeci->poziv;
		if(UsporediDatume(dmTmp, dm1) > 0 && UsporediDatume(dmTmp, dm2) < 0){
			PrintDatum(dmTmp);
			printf(" %dm %ds", pozivTmp->trajanje_poziva / 60, pozivTmp->trajanje_poziva % 60);
			printf(" %s %s %s\n", pozivTmp->kontakt->ime, pozivTmp->kontakt->prezime, pozivTmp->kontakt->pozivni_broj);
		}
		headLista = headLista->sljedeci;
	}
	return EXIT_SUCCESS;
}

int ObavljeniPozivi(PozicijaLista headPoziv, PozicijaKontakt headKontakt){
	int brojKontakta = 0, i = 0, krajni_broj_poziva = 0;
	char krajni_pozivni_broj[MAX_STRING_SIZE] = {0};
	BrojPoziva* brojeviPoziva = NULL;
	PozicijaKontakt headKontaktTmp = NULL;
	PozicijaKontakt krajni_kontakt = NULL;
	headKontaktTmp = StvoriKontakt();

	headKontaktTmp = headKontakt;
	while(headKontakt->sljedeci != NULL){
		brojKontakta++;
		headKontakt = headKontakt->sljedeci;
	}

	brojeviPoziva = (BrojPoziva*) malloc(brojKontakta * sizeof(BrojPoziva));
	if(!brojeviPoziva){
		printf("Greska pri alociranju memorije");
		return EXIT_SUCCESS;
	}

	while(headKontaktTmp->sljedeci != NULL){
		strcpy(brojeviPoziva[i].pozivni_broj, headKontaktTmp->sljedeci->pozivni_broj);

		brojeviPoziva[i].broj_poziva = KolikoPutaJeKontaktNazvan(brojeviPoziva[i].pozivni_broj, headPoziv);
		printf("%s %s nazvan %d puta\n", headKontaktTmp->sljedeci->ime, headKontaktTmp->sljedeci->prezime, brojeviPoziva[i].broj_poziva);
	
		headKontaktTmp = headKontaktTmp->sljedeci;
		i++;
	}
	return EXIT_SUCCESS;
}

int KolikoPutaJeKontaktNazvan(char* pozivni_broj, PozicijaLista headPoziv){
	int brojac = 0;
	while(headPoziv->sljedeci != NULL){
		if(strcmp(pozivni_broj, headPoziv->sljedeci->poziv->kontakt->pozivni_broj) == 0){
			brojac++;
		}
		headPoziv = headPoziv->sljedeci;
	}
	return brojac;
}