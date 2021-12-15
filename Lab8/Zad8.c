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
int InOrderPrint(Stablo);
int PostOrderPrint(Stablo);
int PreOrderPrint(Stablo);


//Stog na First in First out principu
struct _StogElement;
typedef struct _StogElement *Pozicija;
typedef struct _StogElement{
	Pozicija sljedeci;
	Stablo cvor;
} StogElement;

int Push(Stablo, Pozicija);
int Pop(Pozicija);
Pozicija StvoriStogElement();
Stablo NadiZadnjiNaStogu(Pozicija);
int LevelOrderPrint(Stablo, Pozicija);

int main(){
	char ch = '0';
	int isActive = 1, broj = 0;
	Pozicija stogHead = NULL;
	Stablo korijen = NULL;
	
	stogHead = StvoriStogElement();

	korijen = Unos(korijen, 5);
	korijen = Unos(korijen, 10);
	korijen = Unos(korijen, 2);
	korijen = Unos(korijen, 9);
	korijen = Unos(korijen, 3);
	korijen = Unos(korijen, 12);
	korijen = Unos(korijen, 1);

	// Stablo bi trebalo izgledati ovako
	// 				  5
	// 			2			10
	// 		1		3	9		12
	while(isActive){
		printf("\nOdaberi operaciju binarnog stabla:\n");
		printf("1 - unos novog elementa u stablo\n");
		printf("2 - ispis inorder stabla\n");
		printf("3 - ispis postorder stabla\n");
		printf("4 - ispis preorder stabla\n");
		printf("5 - ispis levelorder stabla\n");
		printf("6 - trazenje elementa stabla\n");
		printf("7 - brisanje elementa iz stabla\n");
		printf("8 - kraj\n");
		scanf(" %c", &ch);
		switch(ch){
			case '1':
				printf("\nUnesite broj koji zelite unijeti");
				scanf("%d", &broj);
				korijen = Unos(korijen, broj);
				break;
			case '2':
			printf("\nInOrder: \n");
				InOrderPrint(korijen);
				break;
			case '3':
			printf("\nPostOrder: \n");
				PostOrderPrint(korijen);
				break;
			case '4':
			printf("\nPreOrder: \n");
				PreOrderPrint(korijen);
				break;
			case '5':
			printf("\nLevelOrder: \n");
				LevelOrderPrint(korijen, stogHead);
				break;
			case '6':

				break;
			case '7':
				break;
			case '8':
				printf("\nZavrsetak programa");
				isActive = 0;
				break;
			default:
				printf("\nKrivi unos probajte ponovno");
				break;
		}
	}
	return EXIT_SUCCESS;
}

int Push(Stablo cvor, Pozicija stogHead){
	Pozicija q = StvoriStogElement();
	q->cvor = cvor;

	q->sljedeci = stogHead->sljedeci;
	stogHead->sljedeci = q;
}


int Pop(Pozicija stogHead){
	//FIFO
	Pozicija prev, curr = NULL;
	prev = StvoriStogElement();
	curr = StvoriStogElement();

	prev = stogHead;
	curr = prev->sljedeci;
	//pronadi prezadnji
	while (curr->sljedeci != NULL) {
		prev = curr;
		curr = curr->sljedeci;
	}
	
	prev->sljedeci = curr->sljedeci;
	printf("%d\n", curr->cvor->broj);
	free(curr);
}

Pozicija StvoriStogElement(){
	Pozicija q = malloc(sizeof(StogElement));
	if(!q){
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	q->sljedeci = NULL;
	q->cvor = NULL;
	return q;
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


int InOrderPrint(Stablo korijen){
	if(korijen == NULL){
		return EXIT_SUCCESS;
	}
	else{

		InOrderPrint(korijen->Lijevo);
		printf("%d\n", korijen->broj);
		InOrderPrint(korijen->Desno);
	}
	return EXIT_SUCCESS;
}

int PostOrderPrint(Stablo korijen){
	if(korijen == NULL){
		return EXIT_SUCCESS;
	}
	else{

		PostOrderPrint(korijen->Lijevo);
		PostOrderPrint(korijen->Desno);
		printf("%d\n", korijen->broj);
	}
	return EXIT_SUCCESS;
}

int PreOrderPrint(Stablo korijen){
	if(korijen == NULL){
		return EXIT_SUCCESS;
	}
	else{

		printf("%d\n", korijen->broj);
		PreOrderPrint(korijen->Lijevo);
		PreOrderPrint(korijen->Desno);
	}
	return EXIT_SUCCESS;
}

int LevelOrderPrint(Stablo korijen, Pozicija stogHead){
	Stablo trenutni = NULL;
	if(korijen == NULL){
		return EXIT_SUCCESS;
	}
	Push(korijen, stogHead);
	while(stogHead->sljedeci != NULL){
		trenutni = NadiZadnjiNaStogu(stogHead);
		if(trenutni->Lijevo != NULL){
			Push(trenutni->Lijevo, stogHead);
		}
		if(trenutni->Desno != NULL){
			Push(trenutni->Desno, stogHead);
		}
		Pop(stogHead);
	}
}

Stablo NadiZadnjiNaStogu(Pozicija stogHead){
	while (stogHead->sljedeci != NULL) {
		stogHead = stogHead->sljedeci;
	}
	return stogHead->cvor;
}