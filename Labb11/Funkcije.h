#ifndef FUNKCIJE_H
#define FUNKCIJE_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 30
#define MAX_HASH_TABLE_SIZE 11

struct _CvorStabla;
typedef struct _CvorStabla* PozicijaStablo;
typedef struct _CvorStabla {
	char grad[MAX];
	int populacija;
	PozicijaStablo lijevo;
	PozicijaStablo desno;
} CvorStabla;

struct _CvorListe;
typedef struct _CvorListe* PozicijaLista;
typedef struct _CvorListe {
	char drzava[MAX];
	PozicijaStablo gradovi;
	PozicijaLista sljedeci;
} CvorListe;

struct _HashT;
typedef struct _HashT* HashTab;
typedef struct _HashT{
	PozicijaLista* headLista;
} HashT;

PozicijaLista StvoriClanListe();
PozicijaLista NadiDrzavu(HashTab, char*);
PozicijaStablo StvoriClanStabla();

int DodajDrzavaUHashTablicu(HashTab, char*, char*);
int ProcitajDatotekuDrzava(HashTab, char*);
int DodajDrzavaUListu(PozicijaLista , char* , char*);
PozicijaStablo DodajGradUStablo(PozicijaStablo, char*, int);
PozicijaStablo ProcitajDatotekuGradovi(PozicijaStablo, char*);
int PrintDrzavaGradovi(PozicijaLista);
int InOrderPrintStablo(PozicijaStablo);

int Odaberi(HashTab);
int NadiPopulacijeGradovaVeceOdX(PozicijaStablo, int);
HashTab StvoriHashTab();

#endif