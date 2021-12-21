#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN 10
#define MAX 90

struct _CvorStabla;
typedef struct _CvorStabla *Stablo;
typedef struct _CvorStabla {
	int broj;
	Stablo lijevo;
	Stablo desno;
} CvorStabla;

struct _CvorListe;
typedef struct _CvorListe *Pozicija;
typedef struct _CvorListe {
	int broj;
	Pozicija sljedeci;
} CvorListe;

Stablo StvoriStablo(int);
int InOrderPrint();
int InOrderPrintUListu(Pozicija, Stablo);
Stablo Insert(int, Stablo);
int Replace(Stablo);
int RandomStablo(Stablo);
int NadiRandomBroj(int, int);
int UpisiUDatoteku(Stablo, char*);

Pozicija StvoriListu();
int DodajNaKrajListe(int, Pozicija);
int IzbrisiListu(Pozicija);

int main(){
	srand(time(NULL));
	int duljina = 0, i = 0, num = 0;
	int niz[] = {2, 5, 7, 8, 11, 1, 4, 2, 3, 7}; //zadano u zadatku
	Stablo korijen = NULL;

	duljina = sizeof(niz) / sizeof(int);
	for(i = 0; i < duljina; i++){
	 	korijen = Insert(niz[i], korijen);
 	}

	printf("Originalno stablo: ");
	InOrderPrint(korijen);
	printf("\n");

	UpisiUDatoteku(korijen, "ispis.txt");

	printf("Sumirano stablo: ");
	Replace(korijen);
	InOrderPrint(korijen);
	printf("\n");

	UpisiUDatoteku(korijen, "ispis.txt");

	printf("Random stablo: ");
	RandomStablo(korijen);
	InOrderPrint(korijen);

	UpisiUDatoteku(korijen, "ispis.txt");

	return EXIT_SUCCESS;
}

int UpisiUDatoteku(Stablo p, char* imeDat){
	Pozicija head = NULL;
	head = StvoriListu();

	InOrderPrintUListu(head, p);


	FILE* dat = NULL;
	dat = fopen(imeDat, "a"); // append mode ne briše datoteku pri otvaranju
	if(!dat){
		printf("Greska pri otvaranju datoteke");
		return EXIT_FAILURE;
	}

	while(head->sljedeci != NULL){
		head = head->sljedeci;
		fprintf(dat, "%d ", head->broj);
	}
	fprintf(dat, "\n");
	fclose(dat);
	IzbrisiListu(head);
	return 0;
}

int InOrderPrintUListu(Pozicija head, Stablo p){
	if(p == NULL){
		return EXIT_SUCCESS;
	}
	else{

		InOrderPrintUListu(head, p->lijevo);
		DodajNaKrajListe(p->broj, head);
		InOrderPrintUListu(head, p->desno);
	}
	return EXIT_SUCCESS;
}

int DodajNaKrajListe(int broj, Pozicija head){
	Pozicija q = NULL;
	q = StvoriListu();

	while(head->sljedeci != NULL){
		head = head->sljedeci;
	}

	q->broj = broj;
	q->sljedeci = head->sljedeci;
	head->sljedeci = q;
	return EXIT_SUCCESS;
}

int IzbrisiListu(Pozicija head){
	Pozicija tmp = NULL;
	while(head->sljedeci){
		tmp = head->sljedeci;
		head->sljedeci = tmp->sljedeci;
		free(tmp);
	}
	return EXIT_SUCCESS;
}

Pozicija StvoriListu(){
	Pozicija q = malloc(sizeof(CvorListe));
	if(!q){
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	q->broj = 0;
	q->sljedeci = NULL;
	return q;
}

int RandomStablo(Stablo p){
	if(p == NULL){
		return 0;
	}
	p->broj = NadiRandomBroj(MIN, MAX);
	if(p->lijevo){
		RandomStablo(p->lijevo);
	}
	if(p->desno){
		RandomStablo(p->desno);
	}
}

int NadiRandomBroj(int min, int max){
	int r = (rand() % (max - min + 1)) + min;
	return r;
}

int Replace(Stablo p){
	int tmp = 0;
	if(p == NULL){
		return 0;
	}
	tmp = p->broj;
	p->broj = Replace(p->lijevo) + Replace(p->desno);
	return p->broj + tmp;
}

Stablo StvoriStablo(int broj){
	Stablo q = malloc(sizeof(CvorStabla));
	if(!q){
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	q->broj = broj;
	q->lijevo = NULL;
	q->desno = NULL;
	return q;
};

Stablo Insert(int broj, Stablo p){
	if(p == NULL){
		p = StvoriStablo(broj);
	}
	else{
		if(broj == p->broj){
			p->lijevo = Insert(broj, p->lijevo);
		}
		if(broj < p->broj){
			p->desno = Insert(broj, p->desno);
		}
		if(broj > p->broj){
			p->lijevo = Insert(broj, p->lijevo);
		}
	}
	return p;
}

int InOrderPrint(Stablo p){
	if(p == NULL){
		return EXIT_SUCCESS;
	}
	else{

		InOrderPrint(p->lijevo);
		printf("%d\t", p->broj);
		InOrderPrint(p->desno);
	}
	return EXIT_SUCCESS;
}