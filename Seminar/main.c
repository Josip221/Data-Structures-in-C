#include "Funkcije.h"
#include "kontakt.c"
#include "poziv.c"
#include "pomocne.c"
#include "datum.c"
#include "opcije.c"
#include "pretrazivanja.c"
#include "oslobodiMemoriju.c"

int main(int argc, char *argv[]){
	srand(time(NULL));
	int isActive, i = 0, hasChanged = 0;
	char ch = '0';

	PozicijaKontakt headKontakt = NULL;
	HashTab hashTab = NULL;
	PozicijaLista headPoziv = NULL;

	headKontakt = StvoriKontakt();
	hashTab = SvoriHashTab();
	headPoziv = StvoriClanListe();

	// za tesiranje programa da nemoram svaki put upisivati kontakte i pozive
	// ProcitajKontaktDatoteku("kontakti.txt", headKontakt);
	// ProcitajPozivDatoteku(hashTab, headPoziv, headKontakt, "pozivi.txt");
	// HashTablicuUListu(hashTab, headPoziv);

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
				if(OpcijaNapraviPoziv(headKontakt, hashTab) == EXIT_SUCCESS){
					hasChanged = 1;
				}
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
				if(hasChanged){
					HashTablicuUListu(hashTab, headPoziv);
				}
				PrintPozivLista(headPoziv->sljedeci);
				hasChanged = 0;
				break;
			case '7':
				OpcijaDatoteka(headKontakt, hashTab, headPoziv);
				break;
			case '8':
				if(hasChanged){
					HashTablicuUListu(hashTab, headPoziv);
				}
				OpcijaStatistika(headKontakt, hashTab, headPoziv);
				break;
			case '9':
				printf("Izlazenje iz programa...");
				isActive = 0;
				break;
			default: 
				printf("Pogresan unos probajte opet\n");
		}
	}


	OslobodiKontakte(headKontakt);
	OslobodiPozivListu(headPoziv);
	OslobodiHashTablicu(hashTab);

	return EXIT_SUCCESS;
}