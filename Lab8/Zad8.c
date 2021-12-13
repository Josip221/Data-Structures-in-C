#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _CvorStabla;
typedef struct _CvorStabla *Stablo;
typedef struct _CvorStabla {
	int broj;
	Stablo Lijevo;
	Stablo Desno;
} CvorStabla;

Stablo StvoriStablo(int);
Stablo Unos(Stablo, int);
int Ispis(Stablo);




int main(){
	Stablo korijen = NULL;
	korijen = Unos(korijen, 5);
	korijen = Unos(korijen, 10);
	korijen = Unos(korijen, 1);
	korijen = Unos(korijen, 9);
	korijen = Unos(korijen, 12);
	korijen = Unos(korijen, 7);
	Ispis(korijen, 0);


	return 0;
}


Stablo StvoriStablo(int broj){
	Stablo q = malloc(sizeof(CvorStabla));
	if(!q){
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	q->broj = broj;
	q->Lijevo = NULL;
	q->Desno = NULL;
	return q;
}

Stablo Unos(Stablo p, int broj){
	if(p == NULL){
		p = StvoriStablo(broj);
	}
	else{
		if(broj > p->broj){
			p->Desno = Unos(p->Desno, broj);
		}
		if(broj < p->broj){
			p->Lijevo = Unos(p->Lijevo, broj);
		}
	}
	return p;
}


int InOrder(Stablo korijen){
	int i;
	if(korijen == NULL){
		return 0;
	}
	else{

		InOrder(korijen->Lijevo);
		printf("%d\n", korijen->broj);
		InOrder(korijen->Desno);
	}
	return 0;
}

int PostOrderPrint(Stablo korijen){
	if(korijen == NULL){
		return 0;
	}
	else{

		InOrder(korijen->Lijevo);
		InOrder(korijen->Desno);
		printf("%d\n", korijen->broj);
	}
	return 0;
}
