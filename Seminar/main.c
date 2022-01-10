#include "Funkcije.h"
#include "kontakt.c"
#include "poziv.c"
#include "pomocne.c"
#include "datum.c"

int main(int argc, char *argv[]){
	int isActive = 1;
	char ch = '0';

	srand(time(NULL));
	PozicijaKontakt headKontakt = NULL;
	PozicijaPoziv headPoziv = NULL;
	PozicijaPoziv headPozivSortirano = NULL;

	headKontakt = StvoriKontakt();
	headPoziv = StvoriPoziv();
	headPozivSortirano = StvoriPoziv();

	while(isActive){
		PrintPhoneBookMenu();
		printf("Odaberite opciju: ", ch);
		scanf(" %c", &ch);
		system("cls");
		switch(ch){
			case '1': 
				OpcijaDodajNoviKontakt(headKontakt);
				break;
			case '2': 
				OpcijaNapraviPoziv(headKontakt, headPoziv);
				break;
			case '3':
				OpcijaIzmjeniKontakt(headKontakt);
				break;
			case '4':
				OpcijaIzbrisiKontakt(headKontakt);
				break;
			case '5':
				PrintKontaktLista(headKontakt->sljedeci);
				break;
			case '6':
				PrintPozivLista(headPoziv->sljedeci);
				break;
			case '7':
				OpcijaDatoteka(headKontakt, headPoziv);
				break;
			case '8':
			//statistika
				break;
			case '9':
				printf("Izlazenje iz programa...");
				isActive = 0;
				break;
			default: 
				printf("Pogresan unos probajte opet\n");
		}
	}
	
	return EXIT_SUCCESS;
}

int OpcijaDodajNoviKontakt(PozicijaKontakt headKontakt){
	char tmp1[MAX] = {0}, tmp2[MAX] = {0}, tmp3[MAX] = {0};
	printf("Upisite ime i prezime novog kontakta: ");
	scanf(" %s %s", tmp1, tmp2);
	printf("Upisite pozivni broj kontakta u formatu XXX-XXX-XXXX: ");
	scanf(" %s", tmp3); //provjera
	if(DodajKontaktUListu(headKontakt, tmp3, tmp1, tmp2)){
		printf("Uspjesno dodan %s %s %s u kontakte.\n", tmp3, tmp1, tmp2);
	}
	return EXIT_SUCCESS;
}

int OpcijaNapraviPoziv(PozicijaKontakt headKontakt, PozicijaPoziv headPoziv){
	char tmp[MAX] = {0};
	printf("Upisi broj kontakta koji zelite nazvati: ");
	scanf(" %s", tmp); //provjera
	DodajPozivUListu(headPoziv, headKontakt, tmp);
	return EXIT_SUCCESS;
}

int OpcijaIzmjeniKontakt(PozicijaKontakt headKontakt){
	PozicijaKontakt tmpKontakt = NULL;
	char tmp[MAX] = {0};
	printf("Upisi pozivni broj kontakta koji zelite azurirati u formatu: XXX-XXX-XXXX: ");
	scanf(" %s", tmp);	//provjeri broj
	tmpKontakt = NadiKontaktPoBroju(headKontakt, tmp);
	if(tmpKontakt){
		AzurirajKontaktIzListe(headKontakt, tmpKontakt);
	}
	else{
		printf("Greska pri izmjeni kontakta. Probajte opet.\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int OpcijaIzbrisiKontakt(PozicijaKontakt headKontakt){
	PozicijaKontakt tmpKontakt = NULL;
	char tmp[MAX] = {0};
	printf("Upisi broj kontakta koji zelite izbrisati: ");
	scanf(" %s", tmp); //provjeri broj
	tmpKontakt = NadiKontaktPoBroju(headKontakt, tmp);
	if(tmpKontakt){
		printf("Uspjesno izbrisan kontakt: %s %s %s", tmpKontakt->ime, tmpKontakt->prezime, tmpKontakt->pozivni_broj);
		IzbrisiKontaktIzListe(tmpKontakt);
	}
	else{
		printf("Greska pri brisanju kontakta. Probajte opet.\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int OpcijaDatoteka(PozicijaKontakt headKontakt, PozicijaPoziv headPoziv){
	char ch = '0';
	char tmp[MAX] = {0};
	int isActive = 1;

	system("cls");
	while(isActive){
		PrintDatotekaMenu();
		scanf(" %c", &ch);
		system("cls");
		switch(ch){
			case '1': 
				printf("Odabrano citanje kontakt datoteke. Upisite ime datoteke: ");
				scanf(" %s", tmp);
				ProcitajKontaktDatoteku(tmp, headKontakt);
				break;
			case '2': 
				printf("Odabrano spremanje kontakt datoteke. Upisite ime datoteke: ");
				scanf(" %s", tmp);
				break;
			case '3':
				printf("Odabrano citanje poziv datoteke. Upisite ime datoteke: ");
				scanf(" %s", tmp);
				break;
			case '4':
				printf("Odabrano spremanje kontakt datoteke. Upisite ime datoteke: ");
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