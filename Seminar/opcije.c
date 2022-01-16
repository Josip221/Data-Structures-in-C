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

	if(headKontakt->sljedeci == NULL){
		printf("Nemoguce je napraviti poziv ako je snimljeno 0 kontakta");
		return EXIT_FAILURE;
	}

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

	if(headKontakt->sljedeci == NULL){
		printf("Nemoguce je napraviti izmjenu ako je snimljeno 0 kontakta");
		return EXIT_FAILURE;
	}

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

	if(headKontakt->sljedeci == NULL){
		printf("Nemoguce je napraviti brisanje ako je snimljeno 0 kontakta");
		return EXIT_FAILURE;
	}

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
		printf("Odaberite opciju: ");
		scanf(" %c", &ch);
		system("cls");
		switch(ch){
			case '1': 
				printf("Odabrano citanje kontakt datoteke. Upisite ime datoteke za procitati: ");
				scanf(" %s", tmp);
				ProcitajKontaktDatoteku(tmp, headKontakt);
				break;
			case '2': 
				if(headKontakt->sljedeci == NULL){
					printf("Nepostoje kontakti koji bi mogli biti snimljeni");
					break;
				}
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
				if(headPoziv->sljedeci == NULL){
					printf("Nepostoje pozivi koji bi mogli biti snimljeni");
					break;
				}
				printf("Odabrano spremanje kontakt datoteke. Upisite ime datoteke za spremiti: ");
				scanf(" %s", tmp);
				SpremiPozive(hashTab, tmp);
				break;
			case '5':
				isActive = 0;
				break;
			default: 
				printf("Pogresan unos probajte opet\n");
				break;
		}
	}
	return EXIT_SUCCESS;
}

int OpcijaStatistika(PozicijaKontakt headKontakt, HashTab hashTab, PozicijaLista headPoziv){
	int isActive = 1;
	Datum dm1 = {.godina = 0, .mjesec = 0, .dan = 0}, dm2 = {.godina = 0, .mjesec = 0, .dan = 0};

	char tmpString1[MAX_STRING_SIZE] = {0}, tmpString2[MAX_STRING_SIZE] = {0};
	char ch = '0';
	if(headPoziv->sljedeci == NULL){
		printf("Nemogu se obavljati pretrazivanja ako je obavljeno 0 poziva");
		return EXIT_FAILURE;
	}

	while(isActive){
		PrintBorder();
		printf("\tPretrazivanje menu:\n \t\t1. Najdulji poziv\n\t\t2. Ukupno vrijeme poziva\n\t\t3. Pozivi u vremenskom razdoblju\n");
		printf("\t\t4. Ucestalost poziva na odredene kontakte\n\t\t5. Natrag na glavni menu\n");
		PrintBorder();
		printf("Odaberite opciju: ");
		scanf(" %c", &ch);
		system("cls");
		switch(ch){
			case '1':
				NajduljiPoziv(headPoziv);
				break;
			case '2':
				UkupnoVrijemePoziva(headPoziv);
				break;
			case '3':
				printf("Unesi prvi datum: ");
				scanf(" %s", tmpString1);
				if(ProvjeriDatum(tmpString1) != EXIT_SUCCESS){
					printf("Krivo");
					break;
				}
				dm1 = PretvoriStringUDatum(tmpString1);
				printf("Unesi drugi datum: ");
				scanf(" %s", tmpString2);
				if(ProvjeriDatum(tmpString2) != EXIT_SUCCESS){
					printf("Krivo");
					break;
				}
				dm2 = PretvoriStringUDatum(tmpString2);
				NadiPoziveUVremenskomRazdoblju(headPoziv, dm1, dm2);
				break;
			case '4':
				ObavljeniPozivi(headPoziv, headKontakt);
				break;
			case '5':
				isActive = 0;
				break;
			default:
				printf("Pogresan unos probajte opet\n");
				break;
		}

	}
	return EXIT_SUCCESS;
}