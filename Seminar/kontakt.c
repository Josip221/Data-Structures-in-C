#include "Funkcije.h"

PozicijaKontakt StvoriKontakt(){
	PozicijaKontakt tmp = malloc(sizeof(Kontakt));
	if(tmp == NULL){
		printf("Greska pri alociranju memorije!\n");
		return NULL;
	}
	strcpy(tmp->ime, "");
	strcpy(tmp->prezime, "");
	strcpy(tmp->pozivni_broj, "");
	tmp->prethodni = NULL;
	tmp->sljedeci = NULL;
	return tmp;
}

int ProcitajKontaktDatoteku(char *imeDat, PozicijaKontakt headKontakt) {
	FILE *dat = NULL;
	char tmpBroj[MAX] = {0};
	char tmpIme[MAX] = {0}, tmpPrezime[MAX] = {0};
	dat = fopen(imeDat, "r");
	if(!dat){
		printf("Greska pri otvaranju datoteke.");
		return EXIT_FAILURE;
	}
	while(!feof(dat)){
		fscanf(dat, "%s %s %s", tmpIme, tmpPrezime, tmpBroj);
		DodajKontaktUListu(headKontakt, tmpBroj, tmpIme, tmpPrezime);
	}
	fclose(dat);
	return EXIT_SUCCESS;
}

int SpremiKontaktDatoteku(char *imeDat, PozicijaKontakt headKontakt){
	FILE *dat = NULL;
	dat = fopen(imeDat, "w");
	if(!dat){
		printf("Greska pri otvaranju datoteke.");
		return EXIT_FAILURE;
	}
	while(headKontakt->sljedeci != NULL){
		fprintf(dat, "%s %s %s", headKontakt->ime, headKontakt->prezime, headKontakt->pozivni_broj);
		headKontakt = headKontakt->sljedeci;
	}
	fclose(dat);
	return EXIT_SUCCESS;
}

int PrintKontaktLista(PozicijaKontakt headKontakt){
	system("cls");
	char ch = '0', ch1;
	int isActive = 0;
	if(headKontakt == NULL){
		printf("Lista kontakata je trenutno prazna!\n");
		return EXIT_SUCCESS;
	}
	while(headKontakt != NULL){
		if(toupper(ch) < toupper(headKontakt->ime[0])){
			ch = headKontakt->ime[0];
			printf("------------------------------------\n");
			printf("%c: ", ch);
		}
		printf("\t%s %s %s\n", headKontakt->ime, headKontakt->prezime, headKontakt->pozivni_broj);
		headKontakt = headKontakt->sljedeci;
	}
	MenuStop();
	return EXIT_SUCCESS;
};

int DodajKontaktUListu(PozicijaKontakt headKontakt, char* pozivni_broj, char* ime, char* prezime){
	PozicijaKontakt noviKontakt = NULL;
	noviKontakt = StvoriKontakt();
	char tmpIme1[MAX] = {0}, tmpIme2[MAX] = {0};
	char tmpPrezime1[MAX] = {0}, tmpPrezime2[MAX] = {0};

	if(BrojIspravan()){
		strcpy(noviKontakt->pozivni_broj, pozivni_broj);
	}
	else{
		printf("Ne ispravno unešen pozivni broj!");
		return EXIT_FAILURE;
	}
	strcpy(noviKontakt->ime, ime);
	strcpy(noviKontakt->prezime, prezime);
	strcpy(tmpIme2, ime);
	strcpy(tmpPrezime2, prezime);
	if(ProvjeriDaliPostojiVecBroj(noviKontakt->pozivni_broj, headKontakt->sljedeci)){
		printf("Broj vec postoji, probajte ponovno");
		return EXIT_FAILURE;
	}

	//abecedno sortirani lowercase/uppercase unos
	while(headKontakt->sljedeci != NULL){
		strcpy(tmpIme1, headKontakt->sljedeci->ime);
		strcpy(tmpPrezime1, headKontakt->sljedeci->prezime);
		if(strcmp(strupr(tmpIme2), strupr(tmpIme1)) > 0){
			headKontakt = headKontakt->sljedeci;
		} 
		else{
			if(strcmp(tmpIme2, tmpIme1) == 0){
				if(strcmp(strupr(tmpPrezime2), strupr(tmpPrezime1)) > 0){
					headKontakt = headKontakt->sljedeci;
					break;
				}
			}
			headKontakt->sljedeci->prethodni = noviKontakt;
			break;
		}
	}
	noviKontakt->sljedeci = headKontakt->sljedeci;
	noviKontakt->prethodni = headKontakt;
	headKontakt->sljedeci = noviKontakt;
	return EXIT_SUCCESS;
}

int ProvjeriDaliPostojiVecBroj(char* pozivni_broj, PozicijaKontakt headKontakt){ //napravi hash + bst za ovo nekako...
	//ne smiju biti dva kontakta s istim pozivnim brojem
	while(headKontakt != NULL){
		if(strcmp(pozivni_broj, headKontakt->pozivni_broj) == 0){
			return EXIT_FAILURE;
		}
		else{
			headKontakt = headKontakt->sljedeci;
		}
	}
	return EXIT_SUCCESS;
}

int IzbrisiKontaktIzListe(PozicijaKontakt kontakt){
	kontakt->prethodni->sljedeci = kontakt->sljedeci;
	kontakt->sljedeci->prethodni = kontakt->prethodni;
	free(kontakt);
	return EXIT_SUCCESS;
}

PozicijaKontakt NadiKontaktPoBroju(PozicijaKontakt headKontakt, char* pozivni_broj){
	while(headKontakt->sljedeci != NULL){
		if(strcmp(pozivni_broj, headKontakt->pozivni_broj) == 0){
			return headKontakt;
		}
		else {
			headKontakt = headKontakt->sljedeci;
		}
	}
	printf("Nije pronaden trazeni kontakt. ");
	return NULL;
}

int AzurirajKontaktIzListe(PozicijaKontakt headKontakt, PozicijaKontakt kontakt){
	char ch = '0';
	char novo[MAX] = {0};
	char staroIme[MAX] = {0}, staroPrezime[MAX] = {0}, pozivni_broj[MAX] = {0};
	int isActive = 1;

	strcpy(staroIme, kontakt->ime);
	strcpy(staroPrezime, kontakt->prezime);
	strcpy(pozivni_broj, kontakt->pozivni_broj);
	
	//izbrisi kontakt sa starim imenom i istim brojem
	IzbrisiKontaktIzListe(kontakt);
	while(isActive){
		printf("Azuriraj:\n\t 1. Ime\n\t2. Prezime\n"); 
		scanf(" %c", &ch);
		switch(ch){
			case '1':
				printf("Novo ime: ");
				scanf(" %s", &novo);
				DodajKontaktUListu(headKontakt, pozivni_broj, novo, staroPrezime);
				isActive = 0;
				break;
			case '2':
				printf("Novo prezime: ");
				scanf(" %s", &novo);
				DodajKontaktUListu(headKontakt, pozivni_broj, staroIme, novo);
				isActive = 0;
				break;
			default:
				printf("Pogresan odabir probajte ponovno\n");
				break;
		}
	}
	return EXIT_SUCCESS;
}