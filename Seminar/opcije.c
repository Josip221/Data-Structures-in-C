#include "Funkcije.h"

int OpcijaDodajNoviKontakt(PozicijaKontakt headKontakt){
	char tmp1[MAX_STRING_SIZE] = {0}, tmp2[MAX_STRING_SIZE] = {0}, tmp3[MAX_STRING_SIZE] = {0};
	printf("Upisite ime i prezime novog kontakta: ");
	scanf(" %s %s", tmp1, tmp2);
	printf("Upisite pozivni broj kontakta u formatu XXX-XXX-XXXX: ");
	scanf(" %s", tmp3);
	if(BrojIspravan(tmp3) != EXIT_SUCCESS){
		printf("Ne ispravno unesen pozivni broj, treba biti u formatu: XXX-XXX-XXXX. Probajte ponovno\n ");
		return EXIT_FAILURE;
	}
	if(DodajKontaktUListu(headKontakt, tmp3, tmp1, tmp2) == EXIT_SUCCESS){
		printf("Uspjesno dodan %s %s %s u kontakte.\n", tmp3, tmp1, tmp2);
	}
	else{
		printf("\nKontakt nije dodan, probajte ponovno.\n");
	}
	return EXIT_SUCCESS;
}

int OpcijaNapraviPoziv(PozicijaKontakt headKontakt, HashTab hashTab){
	char tmpPoziv[MAX_STRING_SIZE] = {0};
	PozicijaKontakt tmpKontakt = NULL;
	PozicijaStablo PozivKontakt = NULL;
	printf("Upisi broj kontakta koji zelite nazvati: ");
	scanf(" %s", tmpPoziv); 
	if(BrojIspravan(tmpPoziv) != EXIT_SUCCESS){
		printf("Ne ispravno unesen pozivni broj, treba biti u formatu: XXX-XXX-XXXX. Probajte ponovno\n ");
		return EXIT_FAILURE;
	}
	tmpKontakt = NadiKontaktPoBroju(headKontakt, tmpPoziv);
	if(tmpKontakt){
		DodajUHashTablicu(hashTab, StvoriCvorStabla(tmpKontakt));
	}
	else{
		printf("Poziv nije napravljen, probajte ponovno");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int OpcijaIzmjeniKontakt(PozicijaKontakt headKontakt){
	PozicijaKontakt tmpKontakt = NULL;
	char tmp[MAX_STRING_SIZE] = {0};
	printf("Upisi pozivni broj kontakta koji zelite azurirati u formatu: XXX-XXX-XXXX: ");
	scanf(" %s", tmp);
	if(BrojIspravan(tmp) != EXIT_SUCCESS){
		printf("Ne ispravno unesen pozivni broj, treba biti u formatu: XXX-XXX-XXXX. Probajte ponovno\n");
		return EXIT_FAILURE;
	}
	tmpKontakt = NadiKontaktPoBroju(headKontakt, tmp);
	if(tmpKontakt){
		AzurirajKontaktIzListe(headKontakt, tmpKontakt);
	}
	else{
		printf("Greska pri izmjeni kontakta, probajte ponovno\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int OpcijaIzbrisiKontakt(PozicijaKontakt headKontakt){
	PozicijaKontakt tmpKontakt = NULL;
	char tmp[MAX_STRING_SIZE] = {0};
	printf("Upisi broj kontakta koji zelite izbrisati: ");
	scanf(" %s", tmp);
	if(BrojIspravan(tmp) != EXIT_SUCCESS){
		printf("Ne ispravno unesen pozivni broj, treba biti u formatu: XXX-XXX-XXXX. Probajte ponovno\n");
		return EXIT_FAILURE;
	}
	tmpKontakt = NadiKontaktPoBroju(headKontakt, tmp);
	if(tmpKontakt){
		printf("Uspjesno izbrisan kontakt: %s %s %s", tmpKontakt->ime, tmpKontakt->prezime, tmpKontakt->pozivni_broj);
		IzbrisiKontaktIzListe(tmpKontakt);
	}
	else{
		printf("Greska pri brisanju kontakta. Probajte opet\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int OpcijaDatoteka(PozicijaKontakt headKontakt, HashTab hashTab, PozicijaLista headPoziv){
	char ch = '0';
	char tmp[MAX_STRING_SIZE] = {0};
	int isActive = 1;

	system("cls");
	while(isActive){
		PrintDatotekaMenu();
		scanf(" %c", &ch);
		system("cls");
		switch(ch){
			case '1': 
				printf("Odabrano citanje kontakt datoteke. Upisite ime datoteke za procitati: ");
				scanf(" %s", tmp);
				ProcitajKontaktDatoteku(tmp, headKontakt->sljedeci);
				break;
			case '2': 
				printf("Odabrano spremanje kontakt datoteke. Upisite ime datoteke za spremiti: ");
				scanf(" %s", tmp);
				SpremiKontakte(headKontakt, tmp);
				break;
			case '3':
				printf("Odabrano citanje poziv datoteke. Upisite ime datoteke za procitati: ");
				scanf(" %s", tmp);
				ProcitajPozivDatoteku(hashTab, headPoziv, headKontakt, tmp);
				HashTablicuUListu(hashTab, headPoziv);
				break;
			case '4':
				printf("Odabrano spremanje kontakt datoteke. Upisite ime datoteke za spremiti: ");
				scanf(" %s", tmp);
				break;
			case '5':
				isActive = 0;
				break;
			default: 
				printf("Krivi unos probatje ponovno\n");
				break;
		}
	}
	return EXIT_SUCCESS;
}

int OpcijaStatistika(PozicijaKontakt headKontakt, HashTab hashTab, PozicijaLista headPoziv){

}