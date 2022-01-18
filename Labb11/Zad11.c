#include "Funkcije.h"
#include "hash.c"


int main() {

	HashTab hashTab = NULL;

	hashTab = StvoriHashTab();

	ProcitajDatotekuDrzava(hashTab, "drzave.txt");

	Odaberi(hashTab);

	printf("\nPritisnite enter za izlaz iz programa ");
	fseek(stdin, 0, SEEK_END);
	getchar();
	return EXIT_SUCCESS;
}


int Odaberi(HashTab hashTab){
	PozicijaLista q = NULL;
	char tmp1[MAX];
	int tmp2;
	printf("Odaberi ime drzave koju zelis pretrazivati: ");
	scanf(" %s", tmp1);
	printf("Nadi sve gradove vece od x stanovnika: ");
	scanf("%d", &tmp2);
	q = NadiDrzavu(hashTab, tmp1);
	if(!q){
		printf("Zadana drzava ne postoji!");
		return EXIT_FAILURE;
	}
	NadiPopulacijeGradovaVeceOdX(q->gradovi, tmp2);
	return EXIT_SUCCESS;
}

int NadiPopulacijeGradovaVeceOdX(PozicijaStablo p, int populacijaX){
	if(p == NULL){
		return EXIT_SUCCESS;
	}

	NadiPopulacijeGradovaVeceOdX(p->lijevo, populacijaX);

	if(p->populacija > populacijaX){
		printf("%s %d, ", p->grad, p->populacija);
	}
	NadiPopulacijeGradovaVeceOdX(p->desno, populacijaX);

	return EXIT_SUCCESS;
}

PozicijaLista StvoriClanListe() {
	PozicijaLista q = malloc(sizeof(CvorListe));
	if (q == NULL) {
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	strcpy(q->drzava, "");
	q->gradovi = NULL;
	q->sljedeci = NULL;
	return q;
}

PozicijaStablo StvoriClanStabla(char* grad, int populacija) {
	PozicijaStablo q = malloc(sizeof(CvorStabla));
	if (q == NULL) {
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	strcpy(q->grad, grad);
	q->populacija = populacija;
	q->lijevo = NULL;
	q->desno = NULL;
	return q;
}

int InOrderPrintStablo(PozicijaStablo p){
	if(p == NULL){
		return EXIT_SUCCESS;
	}
	else{
		InOrderPrintStablo(p->lijevo);
		printf("%s %d, ", p->grad, p->populacija);
		InOrderPrintStablo(p->desno);
	}
	return EXIT_SUCCESS;
}

int ProcitajDatotekuDrzava(HashTab hashTab, char* imeDat){
	char imeDrzava[MAX] = "", imeGradoviDat[MAX] = "";

	FILE* dat = NULL;
	dat = fopen(imeDat, "r");
	if(!dat){
		printf("Greska pri otvaranju datoteke");
		return EXIT_FAILURE;
	}

	while(!feof(dat)){
		fscanf(dat, "%s %s", imeDrzava, imeGradoviDat);
		DodajDrzavaUHashTablicu(hashTab, imeDrzava, imeGradoviDat);
	}
	fclose(dat);
	return EXIT_SUCCESS;
}

int DodajDrzavaUListu(PozicijaLista headLista, char* drzava, char* imeGradoviDat) {
	PozicijaLista tmp = NULL;
	char tmp1[MAX], tmp2[MAX];

	tmp = StvoriClanListe();
	strcpy(tmp->drzava, drzava);

	tmp->gradovi = ProcitajDatotekuGradovi(tmp->gradovi, imeGradoviDat);

	//abecedno unošenje u listu, senzitivno na lowercase/uppercase
	strcpy(tmp1, drzava);
	
	while(headLista->sljedeci != NULL){
		strcpy(tmp2, headLista->sljedeci->drzava);
		if(strcmp(strupr(tmp1), strupr(tmp2)) > 0){
			headLista = headLista->sljedeci;
			continue;
		}
		break;
	}

	tmp->sljedeci = headLista->sljedeci;
	headLista->sljedeci = tmp;
}

PozicijaStablo ProcitajDatotekuGradovi(PozicijaStablo headStablo, char* imeDat){
	char gradIme[MAX] = "";
	int gradPopulacija = 0;
	FILE* dat = NULL;

	dat = fopen(imeDat, "r");
	if(!dat){
		printf("Greska pri otvaranju datoteke");
		return NULL;
	}

	while(!feof(dat)){
		fscanf(dat, "%s %d", gradIme, &gradPopulacija);
		headStablo = DodajGradUStablo(headStablo, gradIme, gradPopulacija);
	}
	fclose(dat);
	return headStablo;
}

PozicijaStablo DodajGradUStablo(PozicijaStablo p, char* grad, int populacija){
	if(p == NULL){
		p = StvoriClanStabla(grad, populacija);
	}
	else if(populacija == p->populacija){
		if(strcmp(grad, p->grad) < 0){
			p->lijevo = DodajGradUStablo(p->lijevo, grad, populacija);
		}
		if(strcmp(grad, p->grad) > 0){
			p->desno = DodajGradUStablo(p->desno, grad, populacija);
		}
	}
	else{
		if(populacija < p->populacija){
			p->lijevo = DodajGradUStablo(p->lijevo, grad, populacija);
		}
		if(populacija > p->populacija){
			p->desno = DodajGradUStablo(p->desno, grad, populacija);
		}
	}
	return p;
}

PozicijaLista NadiDrzavu(HashTab hashTab, char* drzava){
	int index = hashFunkcija(drzava);
	PozicijaLista headLista = hashTab->headLista[index];

	while(headLista->sljedeci != NULL){
		if(strcmp(drzava, headLista->sljedeci->drzava) == 0){
			return headLista->sljedeci;
		}
		else{
			headLista = headLista->sljedeci;
		}
	}
	return NULL;
}