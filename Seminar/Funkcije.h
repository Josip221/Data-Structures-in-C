#ifndef FUNKCIJE_H
#define FUNKCIJE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

struct _Kontakt;
typedef struct _Kontakt* PozicijaKontakt;
typedef struct _Kontakt{
	char pozivni_broj[MAX];
	char ime[MAX];
	char prezime[MAX];
	PozicijaKontakt prethodni;
	PozicijaKontakt sljedeci;
} Kontakt;

typedef struct _Datum {
	int godina;
	int mjesec;
	int dan;
} Datum;

struct _Poziv;
typedef struct _Poziv* PozicijaPoziv;
typedef struct _Poziv{
	int id_poziv;
	int trajanje_poziva;
	Datum datum;
	PozicijaKontakt kontakt;
	PozicijaPoziv sljedeci;
} Poziv;

//Opcije
int OpcijaDodajNoviKontakt(PozicijaKontakt);
int OpcijaNapraviPoziv(PozicijaKontakt, PozicijaPoziv);
int OpcijaIzmjeniKontakt(PozicijaKontakt);
int OpcijaIzbrisiKontakt(PozicijaKontakt);

//Kontakt funkcije
PozicijaKontakt StvoriKontakt();
PozicijaKontakt NadiKontaktPoBroju(PozicijaKontakt, char*);
int DodajKontaktUListu(PozicijaKontakt, char*, char*, char*);
int IzbrisiKontaktIzListe(PozicijaKontakt);
//int IzbrisiSveKontakte(PozicijaKontakt);
int AzurirajKontaktIzListe(PozicijaKontakt, PozicijaKontakt);
int ProcitajKontaktDatoteku(char *, PozicijaKontakt);
int SpremiKontaktDatoteku(char *, PozicijaKontakt);
int PrintKontaktLista(PozicijaKontakt);
int ProvjeriDaliPostojiVecBroj(char* , PozicijaKontakt);


//Poziv funkcije
PozicijaPoziv StvoriPoziv();
int NapraviPoziv(PozicijaPoziv, PozicijaKontakt);
int DodajPozivUListu(PozicijaPoziv, PozicijaKontakt, char*);
int ProcitajPozivDatoteku(PozicijaPoziv, char*);
int SpremiPozivDatoteku(PozicijaPoziv);
int ProcitajPozivDatoteku(PozicijaPoziv, char*);
int PrintPozivLista(PozicijaPoziv);


//Pomocne funkcije
int PrintPhoneBookMenu();
int BrojIspravan();
int StvoriVrijemeTrajanjaPoziva();
int RandomBroj(int, int);
int MenuStop():

//Datum funkcije
Datum StvoriRandomDatum();
int UsporediDatume(Datum, Datum);
int PrintDatum(Datum);


//Hash 
#endif