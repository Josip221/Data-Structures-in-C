#include "Funkcije.h"
#include<stdio.h>
#include<stdlib.h>


int IzbrisiNakon(Position prev){
	Position zaIzbris = NULL;
	zaIzbris = prev->next;
	prev->next = zaIzbris->next;
	free(zaIzbris);
};

int OslobodiMemoriju(Position p){
	Position temp = p;
	while(temp->next){
		IzbrisiNakon(temp);
	};
};

int DodajClanNaKraj(int baza, int exp, Position p){
	Position q = StvoriCvor();
	q->next = NULL;
	while(p->next != NULL){
		p = p->next;
	};
	q->baza = baza;
	q->exp = exp;
	q->next = p->next;
	p->next = q;
};

int DodajClanSortirano(int baza, int exp, Position p){
	Position q = StvoriCvor();
	q->next = NULL;
	while(p->next != NULL && (p->next->exp > exp)){
		p = p->next;
	};
	q->baza = baza;
	q->exp = exp;
	q->next = p->next;
	p->next = q;
};


int ProcitajDatoteku(char * imeDat, char* buff, Position p){
	int  duljinaRedak1 = 0, duljinaRedak2 = 0, baze[MAX], exponenti[MAX];
	int offset = 0, temp = 0, i = 0;
	FILE* fp = NULL;
	fp = fopen(imeDat, "r");
	if(fp == NULL){
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	};

	fgets(buff, MAX, fp);
	while(sscanf(buff, "%d%n",&temp, &offset) == 1){
		buff += offset;
		baze[duljinaRedak1] = temp;
		duljinaRedak1++;
	};
	offset = 0;
	temp = 0;
	fgets(buff, MAX, fp);
	while(sscanf(buff, "%d%n",&temp, &offset) == 1){
		buff += offset;
		exponenti[duljinaRedak2] = temp;
		duljinaRedak2++;
	};

	if(duljinaRedak1 != duljinaRedak2){
		printf("Greska - polinom je krivo zadan.\n");
		return -2;
	};

	for(i = 0; i < duljinaRedak1; i++){
		DodajClanSortirano(baze[i], exponenti[i], p);
	};
	fclose(fp);
};

Position StvoriCvor(){
	Position q = (Position)malloc(sizeof(Poly));
	if(q == NULL){
		printf("Greska pri alociranju memorije");
		return NULL;
	};
	return q;
};

int Ispis(Position poly){
	while(poly != NULL){
		printf("+ %dx^%d", poly->baza, poly->exp);
		poly = poly->next;
	};
	printf("\n");
	return 1;
};

int ZbrojiPolinome(Position pol1, Position pol2, Position pol_zbr){
	while(!(pol1 == NULL && pol2 == NULL)){	
		if(pol1 == NULL){
			if (pol2->baza != 0){
				DodajClanNaKraj(pol2->baza, pol2->exp, pol_zbr);
			};
			pol2 = pol2->next;
		}
		else if(pol2 == NULL){
			if (pol1->baza != 0){
				DodajClanNaKraj(pol1->baza, pol1->exp, pol_zbr);
			};
			pol1 = pol1->next;
		}
		else if (pol1->exp == pol2->exp){
			if ((pol1->baza + pol2->baza) != 0){ 
				DodajClanNaKraj(pol1->baza + pol2->baza, pol1->exp, pol_zbr);
			};
			pol1 = pol1->next; 
			pol2 = pol2->next;	
		}
		else if(pol1->exp > pol2->exp){		
			if (pol2->baza != 0){
				DodajClanNaKraj(pol2->baza, pol2->exp, pol_zbr);		
			};
			pol2 = pol2->next;
		}
		else if(pol1->exp < pol2->exp){
			if (pol1->baza != 0){
				DodajClanNaKraj(pol1->baza, pol1->exp, pol_zbr);
			};
			pol1 = pol1->next;
		};
	};
	
};

int PomnoziPolinome(Position pol1, Position pol2, Position pol_umnoz){
	Position pol2_poc = pol2, tmp = NULL;
	while (pol1 != NULL)
	{	
		while(pol2 != NULL){
			tmp = StvoriCvor();
			tmp->next = NULL;
			tmp->baza = pol1->baza * pol2->baza;
			tmp->exp = pol1->exp + pol2->exp;
			ZbrojiPolinome(pol_umnoz->next, tmp, pol_umnoz);
			pol2 = pol2->next;
		}	
		pol1 = pol1->next;
		pol2 = pol2_poc;
	};
};