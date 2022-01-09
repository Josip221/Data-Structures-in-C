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

	ProcitajKontaktDatoteku("kontakti.txt", headKontakt);

	while(isActive){
		PrintPhoneBookMenu();
		printf("Odaberite opciju: ", ch);
		scanf(" %c", &ch);
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
			//datoteka menu za snimanje i citanje
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
	DodajKontaktUListu(headKontakt, tmp3, tmp1, tmp2);
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